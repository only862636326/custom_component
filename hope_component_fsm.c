/**
 ***************************************************************************************************
 * @file        hope_component_fsm.c
 * @author      wsn
 * @version     V1.0
 * @date        2024.11.02
 * @brief       使用C实现的简单状态机
 *              fsm functon
 *
 * @license     wsn
 ***************************************************************************************************
 * @attention
 *
 * 版本说明
 *
 * 修改说明
 *     24/11/20 v1.1.0 修改子节点 index(int)  为指针, 并删除node_index (int)
 *     24/12/05 v1.1.1 添加一个空状态机的变量
 *     24/12/14 v1.1.2 添加一个全局ROOTfms, 可添加10个node
 *                     prt 拥有一个自己的状态ID，可触发 enter call, exit call
 *                     不可更改到同一状态
 *
 ***************************************************************************************************
 **/

#include "hope_component_fsm.h"
#include "component_log.h"
#include <stdio.h>

#if CUST_COMP_FSM

const Type_hope_fsm_t NULL_HOPE_FSM = Default_HopeFsm;

#if HOPE_FSM_ROOT
static pType_hope_fsm_t sta_plist[10];
Type_hope_fsm_t g_hope_fsm_root = {
    .sta_list_len = 0,
    .sta_id = -1,
    .sta_list = sta_plist,
    .sta_list_max = 10,
    .UpdataCall = NULL,
};
#endif

void HopeFSM_Tick(pType_hope_fsm_t p_fsm, int t)
{
    p_fsm->tick += t;

    if (p_fsm->pnode != NULL && p_fsm != p_fsm->pnode)
        p_fsm->pnode->tick += t;
}

/// @brief
/// @param p_fsm
/// @param t
void HopeFSM_MulTick(pType_hope_fsm_t p_fsm, int t)
{
    int i;
    p_fsm->tick += t;
    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i] != NULL)
        {
            p_fsm->sta_list[i]->tick += t;
        }
    }
}

/// @brief
/// @param p_fsm
void HopeFSM_MulUpdata(pType_hope_fsm_t p_fsm)
{
    int i;

    if (p_fsm->UpdataCall != NULL)
    {
        p_fsm->UpdataCall(p_fsm);
    }

    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->UpdataCall != NULL)
        {
            p_fsm->sta_list[i]->UpdataCall(p_fsm->sta_list[i]);
        }
    }
}

/// @brief 更新当前节点及它的当前子节点
/// @param p_fsm
void HopeFSM_Updata(pType_hope_fsm_t p_fsm)
{
    if (p_fsm->UpdataCall != NULL)
    {
        p_fsm->UpdataCall(p_fsm);
    }

    if (p_fsm->pnode != NULL && p_fsm != p_fsm->pnode)
    {
        if (p_fsm->pnode->UpdataCall != NULL)
        {
            p_fsm->pnode->UpdataCall(p_fsm->pnode);
        }
        // HopeFSM_Updata(p_fsm->pnode);
    }
}

// 状态机验证
int HopeFsm_ValidateState(pType_hope_fsm_t p_fsm, int state_id)
{
    if (p_fsm->sta_id == state_id)
    {
        return 1; // 状态有效
    }
    for (int i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->sta_id == state_id)
        {
            return 1; // 状态有效
        }
    }
    return 0; // 状态无效
}

void HopeFSM_ChangeById(pType_hope_fsm_t p_fsm, int id)
{
    int i;
    if (p_fsm->val == id)
    {
        return;
    }
    
    COMP_LOG_DEBUG("HopeFSMChangeById -- pre: %d, next: %d", p_fsm->sta_id, id);
    if (p_fsm->val == id)
    {
        return;
    }

    if (!HopeFsm_ValidateState(p_fsm, id))
    {
        COMP_LOG_DEBUG("Error: Invalid state ID %d", id);
        return;
    }

    if (p_fsm->pnode != NULL)
    {
        if (p_fsm->pnode->ExitCall != NULL)
        {
            p_fsm->pnode->ExitCall(p_fsm->pnode);
            COMP_LOG_DEBUG("         Exit Sta %d", p_fsm->val);
        }
        p_fsm->pnode = NULL;
    }

    if (p_fsm->sta_id == id)
    {
        p_fsm->pnode = p_fsm;
        p_fsm->val = id;
        if (p_fsm->pnode->EnterCall != NULL)
        {
            p_fsm->pnode->EnterCall(p_fsm->pnode);
            COMP_LOG_DEBUG("         Enter Sta %d", id);
        }
        return;
    }

    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->sta_id == id)
        {
            p_fsm->pnode = p_fsm->sta_list[i];
            p_fsm->val = id;

            if (p_fsm->pnode->EnterCall != NULL)
            {
                p_fsm->pnode->EnterCall(p_fsm->pnode);
                COMP_LOG_DEBUG("         Enter Sta %d", id);
            }
            break;
        }
    }
}

void HopeFsm_StaAdd(pType_hope_fsm_t prt, pType_hope_fsm_t p)
{
    p->prt = prt;
    if (prt->sta_list_len < prt->sta_list_max)
    {
        prt->sta_list[prt->sta_list_len++] = p;
        if (p->InitCall != NULL)
        {
            p->InitCall(p);
        }
    }
}

void HopeFsm_Init(pType_hope_fsm_t p)
{
    // p->name = NULL;
    // p->tick = 0;
    // p->sta_id = 0;
    // // p->cur_sta = 0;
    // p->val = 0;

    // p->sta_list_max = -1;
    // p->sta_list_len = 0;

    // p->sta_list = NULL;
    // p->prt = NULL;
    // p->p = NULL;
    // p->p1 = NULL;
    // p->pnode = NULL;

    // p->EnterCall = NULL;
    // p->ExitCall = NULL;
    // p->UpdataCall = NULL;
    // p->ValCHangeCall = NULL;

    if (p->InitCall != NULL)
    {
        p->InitCall(p);
    }
}

pType_hope_fsm_t HopeFsm_Get(int sta_id)
{
#if HOPE_FSM_ROOT
    int i;
    pType_hope_fsm_t p_fsm = &g_hope_fsm_root;
    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->sta_id == sta_id)
        {
            return p_fsm->sta_list[i];
        }
    }
#endif
    return NULL;
}

void HopeFSM_ChangeVal(pType_hope_fsm_t p, int val)
{
    if (p->val != val)
    {
        p->val = val;
        if (p->ValCHangeCall != NULL)
        {
            p->ValCHangeCall(p);
        }
    }
}

#if 0
void EnterSta(pType_hope_fsm_t p)
{
    p->tick = 0;
    printf("EnterSta ");
    printf("%d\n", p->sta_id);
}
void ExitSta(pType_hope_fsm_t p)
{
    printf("ExitSta ");
    printf("%d\n", p->sta_id);
    if (p->sta_id == 5)
    {
        p->prt->tick = 0;
    }
}
void UpdataSta(pType_hope_fsm_t p)
{
    printf("UpdataSta ");
    printf("%d, %d\n", p->sta_id, p->tick);
}

void ValChange(pType_hope_fsm_t p)
{
    printf("ValChange ");
    printf("%d \n", p->val);
}

#if 0
Type_hope_fsm_t sta_list[10];

int main()
{
    int i;

    // HopeFsm_Init(&g_hope_fsm_root);

    g_hope_fsm_root.ValCHangeCall = ValChange;
    g_hope_fsm_root.EnterCall = EnterSta;
    g_hope_fsm_root.ExitCall = ExitSta;

    g_hope_fsm_root.UpdataCall = NULL;

    for (i = 0; i < 10; i++)
    {
        sta_list[i].InitCall = NULL;
        HopeFsm_Init(sta_list + i);
        sta_list[i].sta_id = i;

        sta_list[i].EnterCall = EnterSta;
        sta_list[i].UpdataCall = UpdataSta;
        sta_list[i].ExitCall = ExitSta;
        sta_list[i].ValCHangeCall = ValChange;

        HopeFsm_StaAdd(&g_hope_fsm_root, sta_list + i);
    }
    HopeFSM_ChangeById(&g_hope_fsm_root, 4);
    HopeFSM_Updata(&g_hope_fsm_root);
    for (i = 0; i < 10; i++)
    {
        HopeFSM_Tick(&g_hope_fsm_root, 10);
        HopeFSM_Updata(&g_hope_fsm_root);

        HopeFSM_Tick(&g_hope_fsm_root, 10);

        HopeFSM_Updata(&g_hope_fsm_root);

        HopeFSM_ChangeById(&g_hope_fsm_root, i);
        // printf("%d", i);
    }

    HopeFSM_ChangeById(&g_hope_fsm_root, 2);
    HopeFSM_ChangeById(&g_hope_fsm_root, 3);
    HopeFSM_ChangeById(&g_hope_fsm_root, -1);
    HopeFSM_Updata(&g_hope_fsm_root);
    HopeFSM_ChangeById(&g_hope_fsm_root, 3);

    return 0;
}
#endif

#endif

#endif