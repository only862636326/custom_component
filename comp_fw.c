#include "comp_fw.h"

#if CUST_COMP_LOG
#endif

Type_Comp_FW TOP_FW = {

#if CUST_COMP_UNI_IO
    .UniIO_Drv_Get = UniIO_Drv_Get,
    .UniIO_Drv_GetByName = UniIO_Drv_GetByName,
    .UniIO_Drv_Register = UniIO_Drv_Register,
    .UniIO_Drv_O_R_C = UniIO_Drv_O_R_C,
    .UniIO_Drv_O_W_C = UniIO_Drv_O_W_C,
#endif

#if CUST_COMP_EVT
    .HopeEvtRegsterCall = HopeEvtRegsterCall,
    .HopeEvtSubsribe = HopeEvtSubsribe,
    .HopeEvtTirgger = HopeEvtTirgger,
    .HopeEvtRegsterNoCall = HopeEvtRegsterNoCall,
    .HopeEvtGet = HopeEvtGet,
    .HopeEvtTirggerFast = HopeEvtTirggerFast,
#endif

#if CUST_COMP_CMD
    .HopeCMDSendName = HopeCMDSendName,
    .HopeCMDSendIdx = HopeCMDSendIdx,
    .HopeCMDSendFast = HopeCMDSendFast,
    .HopeCMDRigster = HopeCMDRigster,
    .HopeCMDGet = HopeCMDGet,
#endif

#if CUST_COMP_FSM
#if CUST_COMP_FSM_ROOT
	.pfsm_root = &g_hope_fsm_root,
#endif
    .HopeFsm_Get = HopeFsm_Get,
    .HopeFsm_GetByName = HopeFsm_GetByName,
    .HopeFSM_Tick = HopeFSM_Tick,
    .HopeFSM_Updata = HopeFSM_Updata,
    .HopeFSM_ChangeById = HopeFSM_ChangeById,
    .HopeFsm_Init = HopeFsm_Init,
    .HopeFsm_StaAdd = HopeFsm_StaAdd,
    .HopeFSM_ChangeVal = HopeFSM_ChangeVal,
    .HopeFSM_ChangeByName = HopeFSM_ChangeByName,
#endif
};


