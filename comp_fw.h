
#include <stdio.h>
#include <stdint.h>
#include "component_include.h"

#ifndef __COMP_FW__
#define __COMP_FW__

#if CUST_COMP_LOG
#endif

typedef struct Type_Comp_FW
{
#if CUST_COMP_UNI_IO
    pType_COMP_uni_io_t (*UniIO_Drv_Get)(int id);
    pType_COMP_uni_io_t (*UniIO_Drv_Open)(const char *name);
    void (*UniIO_Drv_Register)(pType_COMP_uni_io_t p_drv);
#endif

#if CUST_COMP_EVT
    void (*HopeEvtSubsribe)(int32_t id, void (*call)(void *));
    void (*HopeEvtRegsterCall)(int32_t id, void (*call)(void *));
    void (*HopeEvtTirgger)(int32_t id, void *p);
#endif

#if CUST_COMP_CMD
    int (*HopeCMDSend)(int32_t id, void *p);
    void (*HopeCMDRigster)(int32_t id, void *p);
#endif

#if CUST_COMP_FSM
    pType_hope_fsm_t (*HopeFsm_Get)(int sta_id);
    void (*HopeFSM_Tick)(pType_hope_fsm_t, int);
    void (*HopeFSM_Updata)(pType_hope_fsm_t);
    void (*HopeFSM_ChangeById)(pType_hope_fsm_t, int);
    void (*HopeFsm_Init)(pType_hope_fsm_t);
    void (*HopeFsm_StaAdd)(pType_hope_fsm_t prt, pType_hope_fsm_t p);
    void (*HopeFSM_ChangeVal)(pType_hope_fsm_t, int);
#endif

} Type_Comp_FW, *pType_Comp_FW;

#ifdef __cplusplus
extern "C"
{
#endif

    extern Type_Comp_FW TOP_FW;

#ifdef __cplusplus
} // extern "C"

#endif

#endif
