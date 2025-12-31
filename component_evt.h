
#ifndef __COMPONENT_EVT_H__
#define __COMPONENT_EVT_H__

#include <stdint.h>
#include "component_config.h"

#if CUST_COMP_EVT

#define HopeEvtRegster(x, p) HopeEvtRegsterCall(x, p)

// typedef void (*Type_Call_fun)(void *);

typedef struct Type_hope_evt_t
{
    int32_t event_id;
    char *name;
    void (*call[COMP_EVT_MAX_CALL])(void *);
#if COMP_EVT_Async
    void (*finish_call[COMP_EVT_MAX_CALL])(void *); //
#endif
} Type_hope_evt_t, *pType_hope_evt_t;

#if COMP_EVT_Async
typedef struct Type_hope_evt_trg_t
{
    int32_t event_id;
    void *p;
} Type_hope_evt_trg_t, *pType_hope_evt_trg_t;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    // extern void HopeEvtRegster(int32_t id);
    
    extern void HopeEvtRegsterCall(int32_t id, void (*call)(void *));
    extern void HopeEvtRegsterNoCall(int32_t id);
    extern void HopeEvtTirgger(int32_t id, void *p);
    extern void HopeEvtTirggerFast(int32_t idx, void *p);
    extern int32_t HopeEvtGetIdx(int32_t id);
    
    #if COMP_EVT_Async
    extern void HopeEvtTask(void *p);
    extern void HopeEvtTirggerAsync(int32_t id, void *p);
    extern void HopeEvtRegsterAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *));
    #endif
    
    extern void HopeEvtSubsribe(int32_t id, void (*call)(void *));
    extern void HopeEvtSubsribeAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *));

#ifdef __cplusplus
} // extern c
#endif


#endif

#endif
