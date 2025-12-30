
#ifndef __COMPONENT_EVT_H__
#define __COMPONENT_EVT_H__

#include <stdint.h>
#include "component_config.h"

#if CUST_COMP_EVT

#define EVT_UDP_REV_MSG 2
#define EVT_U2__REV_MSG 3

#define EVT_UART0_TX_DONE 4
#define EVT_UART0_RX_DONE 5

#define COMP_EVT_MAX_NUM 10
#define COMP_EVT_MAX_CALL 5

#define COMP_EVT_Async 1
#define COMP_EVT_MAX_BUF 20 // for async event

#define HopeEvtRegster(x, p) HopeEvtRegsterCall(x, p)

// typedef void (*Type_Call_fun)(void *);

typedef struct Type_hope_evt_t
{
    int32_t event_id;
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

    extern void HopeEvtRegsterNoCall(int32_t id);
    extern void HopeEvtTirgger(int32_t id, void *p);
    extern void HopeEvtTirggerFast(int32_t idx, void *p);
    int32_t HopeEvtGetIdx(int id);
    
#if COMP_EVT_Async
    extern void HopeEvtTask(void *p);
    extern void HopeEvtTirggerAsync(int32_t id, void *p);
#endif


    extern void HopeEvtSubsribe(int32_t id, void (*call)(void *));
    extern void HopeEvtRegsterCall(int32_t id, void (*call)(void *));
    
    extern void HopeEvtSubsribeAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *));
    extern void HopeEvtRegsterAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *));

#ifdef __cplusplus
} // extern c
#endif


#endif

#endif
