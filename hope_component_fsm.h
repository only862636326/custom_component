#ifndef __HOPE_COMPONENT_FSM__
#define __HOPE_COMPONENT_FSM__

#include <stdint.h>
#include "component_include.h"

#if CUST_COMP_FSM

#define HOPE_FSM_ROOT 1

#define Default_HopeFsm {  \
    .name = NULL,          \
    .tick = 0,             \
    .val = 0,              \
    .sta_list_len = -1,    \
    .sta_list_max = -1,    \
    .prt = NULL,           \
    .pnode = NULL,         \
    .sta_list = NULL,      \
    .p = NULL,             \
    .p1 = NULL,            \
    .ExitCall = NULL,      \
    .EnterCall = NULL,     \
    .UpdataCall = NULL,    \
    .ValCHangeCall = NULL, \
    .InitCall = NULL}

typedef struct Type_hope_fsm_t
{
    /* data */
    char *name;
    int tick;
    int sta_id; // for sta name
    int val;    // for prt,  current node sta
                // for node, sta val

    int sta_list_len; // only for prt
    int sta_list_max; // only for prt

    struct Type_hope_fsm_t *prt;
    struct Type_hope_fsm_t *pnode;
    struct Type_hope_fsm_t **sta_list; // only for prt
    void *p;
    void *p1;

    // void (*EnterCall_1)(Type_hope_fsm_t *, void *p);
    // void (*ExitCall_1)(Type_hope_fsm_t *, void *p);
    // void (*UpdataCall_1)(Type_hope_fsm_t *, void *p);

    void (*ExitCall)(struct Type_hope_fsm_t *);
    void (*EnterCall)(struct Type_hope_fsm_t *);
    void (*UpdataCall)(struct Type_hope_fsm_t *);
    void (*ValCHangeCall)(struct Type_hope_fsm_t *);
    void (*InitCall)(struct Type_hope_fsm_t *);

} Type_hope_fsm_t, *pType_hope_fsm_t;

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
    pType_hope_fsm_t HopeFsm_Get(int sta_id);

    void HopeFSM_Tick(pType_hope_fsm_t, int);
    void HopeFSM_Updata(pType_hope_fsm_t);
    void HopeFSM_ChangeById(pType_hope_fsm_t, int);
    void HopeFsm_Init(pType_hope_fsm_t);
    void HopeFsm_StaAdd(pType_hope_fsm_t prt, pType_hope_fsm_t p);
    void HopeFSM_ChangeVal(pType_hope_fsm_t, int);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#endif
