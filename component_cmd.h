
#ifndef __COMPONENT_CMD_H__
#define __COMPONENT_CMD_H__

#include <stdint.h>
#include "component_log.h"
#include "component_include.h"

#if CUST_COMP_CMD

#define COMP_CMD_MAX_NUM 10
// #define COMP_CMD_MAX_CALL 5

typedef struct Type_hope_cmd_t
{
    int32_t id;
    int (*call)(void *);
} Type_hope_cmd_t, *pType_hope_cmd_t;

#ifdef __cplusplus
extern "C"
{
#endif

    extern int HopeCMDSend(int32_t id, void *p);
    extern void HopeCMDRigster(int32_t id, void *p);

    extern void HopeEvtSubsribe(int32_t id, void (*call)(void *));
    extern void HopeEvtRegsterCall(int32_t id, void (*call)(void *));

#ifdef __cplusplus
} // extern c
#endif
#endif

#endif
