#ifndef __COMPONENT_CONFIG_H__
#define __COMPONENT_CONFIG_H__

#define CUST_COMP_CMD 1
#define CUST_COMP_EVT 1
#define CUST_COMP_LOG 1
#define CUST_COMP_FSM 1
#define CUST_COMP_UNI_IO 1

#define COMP_CMD_MAX_NUM 10

// IO驱动最大数量
#define MAX_IO_DRV_NUM 10
#define CUST_COMP_UNI_IO_ASYNC 0
#define CUST_COMP_UNI_IO_PRINT 0

#define COMP_EVT_MAX_NUM 10
#define COMP_EVT_MAX_CALL 50
#define COMP_EVT_Async 0
#define COMP_EVT_MAX_BUF 20 // for async event
#define COMP_EVT_NAME_LEN 16 // for async event

#define CUST_COMP_FSM_ROOT 1

#define STRINGIFY_HELPER(x) #x			 // 内层：实际字符串化
#define STRINGIFY(x) STRINGIFY_HELPER(x) // 外层：触发参数展开


// for user
#define EVT_NONE 0


#endif


