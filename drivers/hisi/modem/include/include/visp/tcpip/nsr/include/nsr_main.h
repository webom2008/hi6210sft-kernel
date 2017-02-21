#ifndef NSR_MAIN_INCLUDED
#define NSR_MAIN_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*默认堆栈定义*/
#if (VOS_OS_VER == VOS_LINUX)
#define  LINUX_DEFAULTSTACKSIZE 1024*1024*8
#else
#define  LINUX_DEFAULTSTACKSIZE 1024*16
#endif

/*NSR消息队列长度*/
#define NSR_QUEUE_LEN_DEFAULT  (1024*8)

#define VRP_TASK_NSR_NAME "NSR"
#define VRP_TASK_NSR_MODE 0

/*任务队列是否有效*/
#define NSR_IS_VALID_QUEUE(ulQueueID)   (ulQueueID != 0)

ULONG NSR_Init(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
