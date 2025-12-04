#include "comp_fw.h"

#if CUST_COMP_LOG
#endif

Type_Comp_FW TOP_FW = {

#if CUST_COMP_LOG
    .mulfun_print = &mulfun_print,
#endif

#if CUST_COMP_UNI_IO
    .UniIO_Drv_Get = UniIO_Drv_Get,
    .UniIO_Drv_Open = UniIO_Drv_Open,
    .UniIO_Drv_Register = UniIO_Drv_Register,
#endif

#if CUST_COMP_EVT
    .HopeEvtRegsterCall = HopeEvtRegsterCall,
    .HopeEvtSubsribe = HopeEvtSubsribe,
    .HopeEvtTirgger = HopeEvtTirgger,
#endif

#if CUST_COMP_CMD
    .HopeCMDSend = HopeCMDSend,
    .HopeCMDRigster = HopeCMDRigster,
#endif

#if CUST_COMP_FSM
    .HopeFsm_Get = HopeFsm_Get,
    .HopeFSM_Tick = HopeFSM_Tick,
    .HopeFSM_Updata = HopeFSM_Updata,
    .HopeFSM_ChangeById = HopeFSM_ChangeById,
    .HopeFsm_Init = HopeFsm_Init,
    .HopeFsm_StaAdd = HopeFsm_StaAdd,
    .HopeFSM_ChangeVal = HopeFSM_ChangeVal,
#endif
};


