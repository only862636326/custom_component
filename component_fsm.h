#ifndef __HOPE_COMPONENT_FSM__
#define __HOPE_COMPONENT_FSM__

#include <stdint.h>
#include "component_config.h"

#if CUST_COMP_FSM


#define CALL_IF_NOT_NULL(func, param) do { if((func) != NULL) (func)(param); } while(0)


#define Default_HopeFsm {  \
    .name = "fsm",         \
    .prioritization = 0,   \
    .tick = 0,             \
    .sta_list_len = -1,    \
    .sta_list_max = -1,    \
    .prt = NULL,           \
    .pnode = NULL,         \
    .sta_list = NULL,      \
    .p = NULL,             \
    .ExitCall = NULL,      \
    .EnterCall = NULL,     \
    .UpdataCall = NULL,    \
    .ValCHangeCall = NULL, \
    .InitCall = NULL}

/// @brief 定义一个有限状态机实例
/// @param name 状态机变量名
/// @param prioritization 状态机优先级 (0:低, 1:高)
/// @param sta_list_len 状态列表初始长度
/// @param sta_list_max 状态列表最大长度
/// @note 使用示例: HOPE_FSM_DEFINE(my_fsm, 1, 0, 10); 创建一个名为my_fsm的高优先级状态机
#define HOPE_FSM_DEFINE(_name, _prio, _len, _max) \
    Type_hope_fsm_t _name = {                     \
        .name = STRINGIFY(_name),                 \
        .prioritization = _prio,                  \
        .tick = 0,                                \
        .sta_id = 0,                              \
        .sta_list_len = _len,                     \
        .sta_list_max = _max,                     \
        .prt = NULL,                              \
        .pnode = NULL,                            \
        .sta_list = NULL,                         \
        .p = NULL,                                \
        .ExitCall = NULL,                         \
        .EnterCall = NULL,                        \
        .UpdataCall = NULL,                       \
        .ValCHangeCall = NULL,                    \
        .InitCall = NULL}

typedef struct Type_hope_fsm_t
{
    /* data */
    char* name;
    int tick;
    int prioritization; // 0: low, 1: high
    int sta_id;         // for sta name
    int current_sta_id; // for prt,  current node sta
                        // for node, sta val
    int sta_list_len; // only for prt
    int sta_list_max; // only for prt

    struct Type_hope_fsm_t *prt;
    struct Type_hope_fsm_t *pnode; // active node
    struct Type_hope_fsm_t **sta_list; // only for prt
    void *p;

    void (*ExitCall)(struct Type_hope_fsm_t *);
    void (*EnterCall)(struct Type_hope_fsm_t *);
    void (*UpdataCall)(struct Type_hope_fsm_t *);
    void (*ValCHangeCall)(struct Type_hope_fsm_t *);
    void (*InitCall)(struct Type_hope_fsm_t *);

} Type_hope_fsmprt_t, Type_hope_fsm_t, *pType_hope_fsm_t;

typedef struct Type_hope_fsmmini_t
{
    int id;
    int val;
    void *p;
    struct Type_hope_fsmmini_t *prt;
    struct Type_hope_fsmmini_t *pnode;
    struct Type_hope_fsmmini_t **sta_list;
    void (*UpdataCall)(struct Type_hope_fsmmini_t *);
} Type_hope_fsmmini_t, pType_hope_fsmmini_t;

// 仅更新一个fsm
#define HopeFSM_Updata_pfsm(p_fsm)     \
    do                                 \
    {                                  \
        if (p_fsm->UpdataCall != NULL) \
            p_fsm->UpdataCall(p_fsm)   \
    } while (0)

#ifdef __cplusplus
extern "C"
{
#endif
    extern Type_hope_fsm_t g_hope_fsm_root;
    extern const Type_hope_fsm_t NULL_HOPE_FSM;
    pType_hope_fsm_t HopeFsm_Get(pType_hope_fsm_t prt, int sta_id);
    pType_hope_fsm_t HopeFsm_GetByName(pType_hope_fsm_t prt, const char *name);

    void HopeFSM_Tick(pType_hope_fsm_t, int);
    void HopeFSM_Updata(pType_hope_fsm_t);
    void HopeFSM_ChangeById(pType_hope_fsm_t, int);
    void HopeFSM_ChangeByName(pType_hope_fsm_t, const char *name);
    void HopeFsm_Init(pType_hope_fsm_t);
    void HopeFsm_StaAdd(pType_hope_fsm_t prt, pType_hope_fsm_t p);
    void HopeFSM_ChangeVal(pType_hope_fsm_t, int);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#endif



// Type_hope_fsm_t _fsm_send = {
// 	.name = "fsm_send",
// 	.prioritization = 0,
// 	.tick = 0,
// 	.sta_id = 0,
// 	.val = 0,
// 	.sta_list_len = 0,
// 	.sta_list_max = U0_FSM_MAX,
// 	.prt = NULL,
// 	.pnode = NULL,
// 	.sta_list = fsm_list,
// 	.p = NULL,
// 	.p1 = NULL,
// 	.ExitCall = NULL,
// 	.EnterCall = NULL,
// 	.UpdataCall = send_updata,
// 	.ValCHangeCall = NULL,
// 	.InitCall = NULL};











