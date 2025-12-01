#ifndef __COMPONENT_INCLUDE_H__
#define __COMPONENT_INCLUDE_H__

#define CUST_COMP_CMD 0
#define CUST_COMP_EVT 0
#define CUST_COMP_LOG 0
#define CUST_COMP_FSM 0
#define CUST_COMP_UNI_IO 1

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