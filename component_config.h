#ifndef __COMPONENT_CONFIG_H__
#define __COMPONENT_CONFIG_H__

#define CUST_COMP_CMD 1
#define CUST_COMP_EVT 1
#define CUST_COMP_LOG 1
#define CUST_COMP_FSM 1
#define CUST_COMP_FSM2 0
#define CUST_COMP_UNI_IO 1

#define COMP_CMD_MAX_NUM 10

#define MAX_IO_DRV_NUM 10
#define CUST_COMP_UNI_IO_ASYNC 0
#define CUST_COMP_UNI_IO_PRINT 0

#define COMP_EVT_MAX_NUM 10
#define COMP_EVT_MAX_CALL 50
#define COMP_EVT_Async 0
#define COMP_EVT_MAX_BUF 20 // for async event
#define COMP_EVT_NAME_LEN 16 // for async event

#define CUST_COMP_FSM_ROOT 1

#define STRINGIFY_HELPER(x) #x			 //
#define STRINGIFY(x) STRINGIFY_HELPER(x) //

#define EVT_NONE 0


#endif


