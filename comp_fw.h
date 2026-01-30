
#ifndef __COMP_FW__
#define __COMP_FW__

#include <stdio.h>
#include <stdint.h>
#include "component_log.h"
#include "component_evt.h"
#include "component_fsm.h"
#include "component_uni_io.h"
#include "component_cmd.h"
#include "component_config.h"

#if CUST_COMP_LOG
#endif

#define Top_FW TOP_FW

typedef struct Type_Comp_FW
{
#if CUST_COMP_UNI_IO
    pType_COMP_uni_io_t (*UniIO_Drv_Get)(int);
    pType_COMP_uni_io_t (*UniIO_Drv_GetByName)(const char *);
    uint32_t (*UniIO_Drv_Register)(pType_COMP_uni_io_t);
#endif

#if CUST_COMP_EVT
    int32_t (*HopeEvtSubsribe)(const char *name, void (*call)(void *));
    int32_t (*HopeEvtRegsterCall)(const char *name, void (*call)(void *));
    int32_t (*HopeEvtTirgger)(const char *name, void *p);
    int32_t (*HopeEvtRegsterNoCall)(const char *name);
    pType_hope_evt_t (*HopeEvtGet)(const char *name);
    int32_t (*HopeEvtTirggerFast)(int32_t idx, void *p);
#endif

#if CUST_COMP_CMD
    int (*HopeCMDSendName)(const char *name, void *p);
    int (*HopeCMDSendIdx)(int32_t idx, void *p);
    int (*HopeCMDSendFast)(int32_t idx, void *p);
    int (*HopeCMDRigster)(pType_hope_cmd_t pcmd);
    pType_hope_cmd_t (*HopeCMDGet)(const char *name);
#endif

#if CUST_COMP_FSM
    pType_hope_fsm_t pfsm_root;
    pType_hope_fsm_t (*HopeFsm_Get)(pType_hope_fsm_t, int);
    pType_hope_fsm_t (*HopeFsm_GetByName)(pType_hope_fsm_t, const char *);
    void (*HopeFSM_Tick)(pType_hope_fsm_t, int);
    void (*HopeFSM_Updata)(pType_hope_fsm_t);
    void (*HopeFSM_ChangeById)(pType_hope_fsm_t, int);
    void (*HopeFsm_Init)(pType_hope_fsm_t);
    void (*HopeFsm_StaAdd)(pType_hope_fsm_t, pType_hope_fsm_t);
    void (*HopeFSM_ChangeVal)(pType_hope_fsm_t, int);
    void (*HopeFSM_ChangeByName)(pType_hope_fsm_t, const char *);
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
