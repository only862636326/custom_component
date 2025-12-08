#ifndef __COMPONENT_INCLUDE_H__
#define __COMPONENT_INCLUDE_H__


#include "component_config.h"

#ifndef CUST_COMP_LOG
#define CUST_COMP_LOG 0
#endif

#ifndef CUST_COMP_CMD
#define CUST_COMP_CMD 0
#endif

#ifndef CUST_COMP_EVT
#define CUST_COMP_EVT 1
#endif

#ifndef CUST_COMP_FSM
#define CUST_COMP_FSM 0
#endif

#ifndef CUST_COMP_UNI_IO
#define CUST_COMP_UNI_IO 1
#endif

#define STRINGIFY(x) STRINGIFY_HELPER(x) // 外层：触发参数展开
#define STRINGIFY_HELPER(x) #x			 // 内层：实际字符串化

#include "component_log.h"
#include "component_evt.h"
#include "hope_component_fsm.h"
#include "component_uni_io.h"
#include "component_cmd.h"

#define loop_skip_time(i)         \
    static uint32_t _count_i = 0; \
    if (_count_i++ < i)           \
    {                             \
        return;                   \
    }                             \
    _count_i = 0;
    

#endif


