
#ifndef __COMPONENT_EVT_H__
#define __COMPONENT_EVT_H__

#include <stdint.h>
#include "component_config.h"

#if CUST_COMP_EVT

#define HopeEvtRegster(x, p) HopeEvtRegsterCall(x, p)

// typedef void (*Type_Call_fun)(void *);

typedef struct Type_evn_call_list_t
{
    void (*call)(void *);
    struct Type_evn_call_list_t *next_call;
} Type_evn_call_list_t, *pType_evn_call_list_t;

typedef struct Type_hope_evt_t
{
    int32_t event_id;
    char name[COMP_EVT_NAME_LEN];
    pType_evn_call_list_t call_list;
} Type_hope_evt_t, *pType_hope_evt_t;

#ifdef __cplusplus
extern "C"
{
#endif

    // extern void HopeEvtRegster(int32_t id);
    
    extern int32_t HopeEvtRegsterCall(const char *name, void (*call)(void *));
    extern int32_t HopeEvtRegsterNoCall(const char *name);
    extern int32_t HopeEvtSubsribe(const char *name, void (*call)(void *));

    extern int32_t HopeEvtTirgger(const char *name, void *p);
    extern int32_t HopeEvtTirggerFast(int32_t idx, void *p);
    extern pType_hope_evt_t HopeEvtGet(const char *name);
    

#ifdef __cplusplus
} // extern c
#endif


#endif

#endif
