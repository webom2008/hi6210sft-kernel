#ifndef __HW_COUNTRY_CODE_4343_H__
#define __HW_COUNTRY_CODE_4343_H__

#include <wl_iw.h>

/* Customized Locale table : OPTIONAL feature */
const struct cntry_locales_custom hw_translate_custom_table[] = {
/* Table should be filled out based on custom platform regulatory requirement */
    /* Table should be filled out based
    on custom platform regulatory requirement */
    {"",   "XZ", 0},  /* Universal if Country code is unknown or empty */
    {"IR", "CN", 0},  // add by huawei
    {"CU", "CN", 0},  // add by huawei
    {"KP", "CN", 0},   // add by huawei
    {"PK", "CN", 0},  // add by huawei
    {"SD", "CN", 0},  //add by huawei
    {"SY", "CN", 0},    //add by huawei
    {"AE", "AE", 1},
    {"AR", "AR", 1},
    {"AT", "AT", 1},
    {"AU", "AU", 2},
    {"BE", "BE", 1},
    {"BG", "BG", 1},
    {"BN", "BN", 1},
    {"CA", "CA", 2},
    {"CH", "CH", 1},
    {"CY", "CY", 1},
    {"CZ", "CZ", 1},
    {"DE", "DE", 3},
    {"DK", "DK", 1},
    {"EE", "EE", 1},
    {"ES", "ES", 1},
    {"FI", "FI", 1},
    {"FR", "FR", 1},
    {"GB", "GB", 1},
    {"GR", "GR", 1},
    {"HR", "HR", 1},
    {"HU", "HU", 1},
    {"IE", "IE", 1},
    {"IS", "IS", 1},
    {"IT", "IT", 1},
    {"JP", "JP", 0}, // Modified by huawei
    {"KR", "KR", 4}, // Modified by huawei
    {"KW", "KW", 1},
    {"LI", "LI", 1},
    {"LT", "LT", 1},
    {"LU", "LU", 1},
    {"LV", "LV", 1},
    {"MA", "MA", 1},
    {"MT", "MT", 1},
    {"MX", "MX", 1},
    {"NL", "NL", 1},
    {"NO", "NO", 1},
    {"PL", "PL", 1},
    {"PT", "PT", 1},
    {"PY", "PY", 1},
    {"RO", "RO", 1},
    {"RU", "RU", 5},
    {"SE", "SE", 1},
    {"SG", "SG", 0}, // Modified by huawei
    {"SI", "SI", 1},
    {"SK", "SK", 1},
    {"TR", "TR", 7},
    {"TW", "TW", 2},
    {"US", "US", 0}, // Modified by huawei
};

#endif