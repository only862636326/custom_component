
#ifndef __COMPONENT_CMD_H__
#define __COMPONENT_CMD_H__

#include <stdint.h>
#include "component_log.h"
#include "component_config.h"


#if CUST_COMP_CMD


typedef struct Type_hope_cmd_t
{
    char* name;
    int32_t id;
    int (*call)(void *);
//    struct Type_hope_cmd_t* next;
} Type_hope_cmd_t, *pType_hope_cmd_t;

#ifdef __cplusplus
extern "C"
{
#endif

    extern int HopeCMDSendName(const char *name, void *p);
    extern int HopeCMDSendIdx(int32_t idx, void *p);
    extern int HopeCMDSendFast(int32_t idx, void *p);
    extern int HopeCMDRigster(pType_hope_cmd_t pcmd);
    extern pType_hope_cmd_t HopeCMDGet(const char *name);

#ifdef __cplusplus
} // extern c
#endif
#endif

#endif
