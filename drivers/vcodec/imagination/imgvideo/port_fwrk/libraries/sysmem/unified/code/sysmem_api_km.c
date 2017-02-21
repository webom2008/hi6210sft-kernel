/*!
 *****************************************************************************
 *
 * @file       sysmem_api_km.c
 *
 * This file contains kernel mode implementation of the
 * System Memory Kernel Mode API, for devices with a unified memory model.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 *
 * The contents of this file are subject to the MIT license as set out below.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the terms of the
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above.
 *
 * If you wish to allow use of your version of this file only under the terms
 * of GPL, and not to allow others to use your version of this file under the
 * terms of the MIT license, indicate your decision by deleting the provisions
 * above and replace them with the notice and other provisions required by GPL
 * as set out in the file called �GPLHEADER� included in this distribution. If
 * you do not delete the provisions above, a recipient may use your version of
 * this file under the terms of either the MIT license or GPL.
 *
 * This License is also included in this distribution in the file called
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include "img_defs.h"
#include "sysmem_api_km.h"
#include "sysmem_utils.h"
#include "sysdev_utils1.h"
#include "sysbrg_utils.h"
#include "sysos_api_km.h"
#include "report_api.h"
#include <asm/io.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/vmalloc.h>
#include <linux/dma-mapping.h>
#include <asm/cacheflush.h>

#ifdef CONFIG_ARM
    #include <linux/highmem.h>
    #include <asm/cacheflush.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
#include <asm/barrier.h>
#endif
#endif

/*!
******************************************************************************

 @Function                SYSMEMKM_Initialise

******************************************************************************/
static IMG_RESULT Initialise(
    SYSMEM_Heap *  heap
)
{
    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSMEMKM_Deinitialise

******************************************************************************/
static IMG_VOID Deinitialise(
    SYSMEM_Heap *  heap
)
{
}

/*!
******************************************************************************

 @Function                SYSMEMKM_AllocPages

******************************************************************************/
static IMG_RESULT AllocPages(
    SYSMEM_Heap *     heap,
    IMG_UINT32        ui32Size,
    SYSMEMU_sPages *  psPages,
    SYS_eMemAttrib    eMemAttrib
)
{
    IMG_UINT32 Res;
    unsigned numPages, pg_i, pgrm_i;
    struct page **pages;
    IMG_UINT64 *      pCpuPhysAddrs;
    size_t            physAddrArrSize;

    //eMemAttrib = SYS_MEMATTRIB_CACHED;
    //printk("===AllocPages===1====\n");
    numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    pages = IMG_BIGORSMALL_ALLOC(numPages*(sizeof *pages));
    if (!pages) {
        Res = IMG_ERROR_OUT_OF_MEMORY;
        goto errPagesTableAlloc;
    }
    //printk("===AllocPages===2====\n");
    // Memory for physical addresses
    physAddrArrSize = sizeof(*pCpuPhysAddrs) * numPages;
    pCpuPhysAddrs = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
    if (!pCpuPhysAddrs) {
        Res = IMG_ERROR_OUT_OF_MEMORY;
        goto errPhysAddrsAlloc;
    }
    //printk("===AllocPages===3====\n");
	//printk("=====numPages = %d===\n",numPages);
    for (pg_i = 0; pg_i < numPages; ++pg_i) {
        pages[pg_i] = alloc_page(GFP_KERNEL);
        if (!pages[pg_i]) {
            Res = IMG_ERROR_OUT_OF_MEMORY;
            goto errPageAlloc;
        }
        // Invalidate the region ( whether it's cached or not )
        //printk("====pages[pg_i] %p,  PAGE_SIZE  %d",pages[pg_i],PAGE_SIZE);

		//dump_stack();
		//pCpuPhysAddrs[pg_i] = dma_map_page(NULL, pages[pg_i], 0, PAGE_SIZE, DMA_FROM_DEVICE);
		pCpuPhysAddrs[pg_i] = page_to_phys(pages[pg_i]);

	}


    // Set pointer to physical address in structure
    psPages->ppaPhysAddr = pCpuPhysAddrs;
    flush_cache_all();
    Res = SYSBRGU_CreateMappableRegion(psPages->ppaPhysAddr[0], ui32Size, eMemAttrib,
                                       IMG_TRUE, psPages, &psPages->hRegHandle);
    DEBUG_REPORT(REPORT_MODULE_SYSMEM, "%s (unified) region of size %u phys 0x%llx",
                 __FUNCTION__, ui32Size, psPages->ppaPhysAddr[0]);
    IMG_ASSERT(Res == IMG_SUCCESS);
    if (Res != IMG_SUCCESS)
    {
        goto errCreateMapRegion;
    }
    //printk("===AllocPages===5====\n");

    IMG_BIGORSMALL_FREE(numPages*sizeof(*pages), pages);

    return IMG_SUCCESS;

errCreateMapRegion:
errKernelMap:
errPageAlloc:
    for (pgrm_i = 0; pgrm_i < pg_i; ++pgrm_i) {
        __free_pages(pages[pgrm_i], 0);
    }
    IMG_BIGORSMALL_FREE(numPages * sizeof(*pCpuPhysAddrs), pCpuPhysAddrs);
errPhysAddrsAlloc:
    IMG_BIGORSMALL_FREE(numPages * sizeof(*pages), pages);
errPagesTableAlloc:
errHandleAlloc:
    return Res;
}


/*!
******************************************************************************

 @Function              SYSMEMKM_ImportExternalPages

******************************************************************************/
IMG_RESULT ImportExternalPages(
    SYSMEM_Heap *     heap,
    IMG_UINT32        ui32Size,
    SYSMEMU_sPages *  psPages,
    SYS_eMemAttrib    eMemAttrib,
    IMG_VOID *        pvCpuKmAddr,
    IMG_PHYSADDR *    ppaPhyAddrs
)
{
    size_t  numPages = (ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;
    size_t  physAddrArrSize = sizeof *(psPages->ppaPhysAddr) * numPages;
    size_t  phy_i;

#if defined CONFIG_X86
    IMG_ASSERT(pvCpuKmAddr != IMG_NULL);
#endif

    psPages->bMappingOnly = IMG_TRUE;
    psPages->bImported = IMG_TRUE;
    psPages->pvCpuKmAddr = pvCpuKmAddr;
    //psPages->pvImplData = pvCpuKmAddr;


    psPages->ppaPhysAddr = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
    IMG_ASSERT(IMG_NULL != psPages->ppaPhysAddr);
    if (IMG_NULL == psPages->ppaPhysAddr)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }
    for (phy_i = 0; phy_i < numPages; ++phy_i)
        psPages->ppaPhysAddr[phy_i] = ppaPhyAddrs[phy_i];
    /* No SYSBRGU_sMappableReg - SYSBRGU_CreateMappableRegion not called. */
    psPages->hRegHandle = NULL;

    return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function                SYSMEMKM_ImportPages

******************************************************************************/
static IMG_RESULT ImportPages(
    SYSMEM_Heap *  heap,
    IMG_UINT32     ui32Size,
    IMG_HANDLE     hExtImportHandle,
    IMG_HANDLE *   phPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hExtImportHandle;
    SYSMEMU_sPages *  psNewPages;

    /**** In this implementation we are importing buffers that we have allocated. */
    /* Allocate a new memory structure...*/
    psNewPages = IMG_MALLOC(sizeof(*psNewPages));
    IMG_ASSERT(psNewPages != IMG_NULL);
    if (psNewPages == IMG_NULL)
    {
        return IMG_ERROR_OUT_OF_MEMORY;
    }

    /* Take a copy of the original page allocation. */
    *psNewPages = *psPages;

    /* Set imported. */
    psNewPages->bImported    = IMG_TRUE;
    psNewPages->bMappingOnly = IMG_FALSE;

    *phPagesHandle = psNewPages;
    return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function                SYSMEMKM_GetCpuKmAddr

******************************************************************************/
static IMG_RESULT GetCpuKmAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID **    ppvCpuKmAddr,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;


    if(psPages->pvCpuKmAddr == IMG_NULL)
    {
        IMG_UINT32 numPages;
        pgprot_t pageProt;
        unsigned pg_i;
        struct page **pages;

        pageProt = PAGE_KERNEL;
        numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
        /* Write combined implies non-cached in Linux x86. If we additionally call
           pgprot_noncached, we will not have write combining, just non-cached. */
        if ((psPages->eMemAttrib & SYS_MEMATTRIB_WRITECOMBINE) != 0)
        {
            pageProt = pgprot_writecombine(pageProt);
        }
#if defined(CONFIG_X86)
        else
#endif
#endif
        /* If uncached...*/
        if ((psPages->eMemAttrib & SYS_MEMATTRIB_UNCACHED) != 0)
        {
            pageProt = pgprot_noncached(pageProt);
        }

        pages = IMG_BIGORSMALL_ALLOC(numPages*(sizeof *pages));
        IMG_ASSERT(IMG_NULL != pages);
        if(IMG_NULL == pages)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }
        for (pg_i = 0; pg_i < numPages; ++pg_i) {
            pages[pg_i] = pfn_to_page(psPages->ppaPhysAddr[pg_i] >> PAGE_SHIFT);
        }

        psPages->pvCpuKmAddr = vmap(pages, numPages, VM_MAP, pageProt);

        IMG_BIGORSMALL_FREE(numPages*sizeof(*pages), pages);

    }

    *ppvCpuKmAddr = psPages->pvCpuKmAddr;

    /* Return success...*/
    return IMG_SUCCESS;
}


/*!
******************************************************************************
 @Function                SYSMEMKM_FreePages

******************************************************************************/
static IMG_VOID FreePages(
    SYSMEM_Heap *  heap,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;
    size_t            numPages;

    numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    /* If mapping then free on the copy of the page structure. */
    /* This will happen by sysmemutils function */
    if (psPages->bImported)
    {
        if(psPages->bMappingOnly && (IMG_NULL != psPages->ppaPhysAddr))
        {
            IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
            psPages->ppaPhysAddr = IMG_NULL;
        }
        return;
    }

    IMG_ASSERT((!psPages->bMappingOnly));            /* Mapping is not supported via this implementation of the SYSMEM API. */

    /* Removed this from the list of mappable regions...*/
    SYSBRGU_DestroyMappableRegion(psPages->hRegHandle);

    /* Free pages and mapping if present */
    {
        unsigned pg_i;
        struct page **pages;


        pages = IMG_BIGORSMALL_ALLOC(numPages*(sizeof *pages));
        IMG_ASSERT(IMG_NULL != pages);
        if(IMG_NULL == pages)
        {
            return;
        }

        for (pg_i = 0; pg_i < numPages; ++pg_i) {
            pages[pg_i] = pfn_to_page(psPages->ppaPhysAddr[pg_i] >> PAGE_SHIFT);
			//dma_unmap_page(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, DMA_FROM_DEVICE);//wx modifyed
        }

        if (psPages->pvCpuKmAddr)
        {
            vunmap(psPages->pvCpuKmAddr);
        }

        for (pg_i = 0; pg_i < numPages; ++pg_i) {
            __free_pages(pages[pg_i], 0);
        }
        IMG_BIGORSMALL_FREE(numPages*sizeof(*pages), pages);

    }
    IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
}

static IMG_VOID *CpuPAddrToCpuKmAddr(
        SYSMEM_Heap *heap, IMG_PHYSADDR paCpuPAddr
)
{
    IMG_ASSERT(!"SYSDEVU1_CpuPAddrToCpuKmAddr not implemented");
    return NULL;
}

static IMG_PHYSADDR CpuKmAddrToCpuPAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID *     pvCpuKmAddr
)
{
    IMG_PHYSADDR ret = 0;

    if(virt_addr_valid(pvCpuKmAddr))
    {
        /* direct mapping of kernel addresses.
         * this works for kmalloc.
         */
        ret = virt_to_phys(pvCpuKmAddr);
    }
    else
    {
        /* walk the page table.
         * Works for ioremap, vmalloc, and kmalloc(GPF_DMA),
          but not, for some reason, kmalloc(GPF_KERNEL)
         */
        struct page * pg = vmalloc_to_page(pvCpuKmAddr);
        if(pg) {
            ret = page_to_phys(pg);
        }
        else {
            IMG_ASSERT(!"vmalloc_to_page failure");
        }
    }

    return ret;
}

#define updateMemoryHelper(func, dir) { \
\
	for (pg_i = 0; pg_i < numPages; ++pg_i) { \
			func(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, dir); \
	}\
}

static IMG_VOID UpdateMemory(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{
	SYSMEMU_sPages *  psPages = hPagesHandle;
	size_t numPages;
	int pg_i;

	if (psPages->eMemAttrib & SYS_MEMATTRIB_UNCACHED) {
		if(dir == CPU_TO_DEV) {
#ifdef CONFIG_ARM
			/* ARM Cortex write buffer needs to be synchronised before device can access it */
			dmb();
#endif
		}
		return;
	}

	numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    switch(dir)
    {
    case CPU_TO_DEV:
    	// End of CPU access -> start of DEV access
    	updateMemoryHelper(dma_sync_single_for_device, DMA_TO_DEVICE);
    	//dma_sync_single_for_device(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, DMA_TO_DEVICE);
#ifdef CONFIG_ARM
    /* ARM Cortex write buffer needs to be synchronised before device can access it */
        dmb();
#endif
        break;
    case DEV_TO_CPU:
    	// End of DEV access -> start of CPU access
    	updateMemoryHelper(dma_sync_single_for_cpu, DMA_FROM_DEVICE);
    	//dma_sync_single_for_cpu(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, DMA_FROM_DEVICE);
        break;
    default:
        break;
    }

}

typedef void (*maint)(struct device *dev, dma_addr_t addr, size_t size, enum dma_data_direction dir);

static inline void updateMemoryRegionHelper(SYSMEMU_sPages *psPages, maint func, SYSMEM_UpdateDirection dir, IMG_UINT32 offset, IMG_UINT32 size) {
	IMG_UINT32 pg_offset = offset & ~PAGE_MASK;
	IMG_UINT32 pg_i = offset >> PAGE_SHIFT;
	IMG_UINT32 remaining_size = size;
	IMG_UINT32 tmp_size;

	remaining_size -= tmp_size = min(PAGE_SIZE - pg_offset, size);
	func(NULL, psPages->ppaPhysAddr[pg_i] + pg_offset, tmp_size, dir);

	while(remaining_size) {
		tmp_size = min(PAGE_SIZE, remaining_size);
		func(NULL, psPages->ppaPhysAddr[pg_i], tmp_size, dir);
		remaining_size -= tmp_size;
		pg_i++;
	}
}

static IMG_VOID UpdateMemoryRegion(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir,
    IMG_UINT32 offset, IMG_UINT32 size
)
{
	SYSMEMU_sPages *  psPages = hPagesHandle;
	size_t numPages;

	if (psPages->eMemAttrib & SYS_MEMATTRIB_UNCACHED) {
		if(dir == CPU_TO_DEV) {
#ifdef CONFIG_ARM
			/* ARM Cortex write buffer needs to be synchronised before device can access it */
			dmb();
#endif
		}
		return;
	}

	numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    switch(dir)
    {
    case CPU_TO_DEV:
    	// End of CPU access -> start of DEV access
    	updateMemoryRegionHelper(psPages, dma_sync_single_for_device, DMA_TO_DEVICE, offset, size);
    	//dma_sync_single_for_device(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, DMA_TO_DEVICE);
#ifdef CONFIG_ARM
    /* ARM Cortex write buffer needs to be synchronised before device can access it */
        dmb();
#endif
        break;
    case DEV_TO_CPU:
    	// End of DEV access -> start of CPU access
    	updateMemoryRegionHelper(psPages, dma_sync_single_for_cpu, DMA_FROM_DEVICE, offset, size);
    	//dma_sync_single_for_cpu(NULL, psPages->ppaPhysAddr[pg_i], PAGE_SIZE, DMA_FROM_DEVICE);
        break;
    default:
        break;
    }
}

static SYSMEM_Ops unified_ops = {
        .Initialise = Initialise,
        .Deinitialise = Deinitialise,

        .AllocatePages = AllocPages,
        .FreePages = FreePages,

        .GetCpuKmAddr = GetCpuKmAddr,
        .CpuKmAddrToCpuPAddr = CpuKmAddrToCpuPAddr,
        .CpuPAddrToCpuKmAddr = CpuPAddrToCpuKmAddr,

        .ImportExternalPages = ImportExternalPages,
        .ImportPages = ImportPages,

        .UpdateMemory = UpdateMemory,
        .UpdateMemoryRegion = UpdateMemoryRegion
};

IMG_RESULT SYSMEMKM_AddSystemMemory(
    SYS_eMemPool *  peMemPool
)
{
    IMG_RESULT ui32Result;
    SYS_eMemPool memPool;

	ui32Result = SYSMEMU_AddMemoryHeap(&unified_ops, IMG_TRUE, IMG_NULL, &memPool);
	IMG_ASSERT(IMG_SUCCESS == ui32Result);
	if (IMG_SUCCESS != ui32Result)
	{
		return ui32Result;
	}

    *peMemPool = memPool;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddSystemMemory)
