#ifndef __COMPONENT_CONFIG_H__
#define __COMPONENT_CONFIG_H__

#define CUST_COMP_CMD 0
#define CUST_COMP_EVT 1
#define CUST_COMP_LOG 1
#define CUST_COMP_FSM 1
#define CUST_COMP_UNI_IO 1

#define STRINGIFY(x) STRINGIFY_HELPER(x) // 外层：触发参数展开
#define STRINGIFY_HELPER(x) #x			 // 内层：实际字符串化







#endif


