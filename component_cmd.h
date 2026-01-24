
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
} Type_hope_cmd_t, *pType_hope_cmd_t;

#ifdef __cplusplus
extern "C"
{
#endif

    extern int HopeCMDSendName(const char *name);
    extern int HopeCMDSendIdx(int32_t idx);
    extern int HopeCMDSendFast(int32_t idx);
    extern int HopeCMDRigster(pType_hope_cmd_t pcmd);
    extern pType_hope_cmd_t HopeCMDGet(const char *name);

#ifdef __cplusplus
} // extern c
#endif
#endif

#endif
