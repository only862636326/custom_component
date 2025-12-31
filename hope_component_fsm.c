/**
 ***************************************************************************************************
 * @file        hope_component_fsm.c
 * @author      wsn
 * @version     v0.0.0
 * @date        2024.11.02
 * @brief       使用C实现的简单状态机
 *              fsm functon
 * @license     MIT
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
 *     25/12/06  添加优先级，每个状态机可设置一个优先级，默认0
 *               添加HopeFsm_GetByName, 可根据名称获取状态机
 *               - updata 只更新node结点，避免父节点、子节点都更新
 *
 ***************************************************************************************************
 **/

#include "hope_component_fsm.h"
#include "component_log.h"
#include <stdio.h>
#include <string.h>

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

    if (p_fsm->pnode->UpdataCall != NULL)
    {
        p_fsm->pnode->UpdataCall(p_fsm->pnode);
    }

    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->pnode->UpdataCall != NULL)
        {
            p_fsm->sta_list[i]->pnode->UpdataCall(p_fsm->sta_list[i]->pnode);
        }
    }
}

/// @brief 更新当前节点及它的当前子节点
/// @param p_fsm 状态机指针
/// @note 此函数会依次调用当前状态机和其活动子状态机的更新回调函数
void HopeFSM_Updata(pType_hope_fsm_t p_fsm)
{
    if (p_fsm->pnode != NULL)
    {
        // 调用活动子节点的更新回调函数
        CALL_IF_NOT_NULL(p_fsm->pnode->UpdataCall, p_fsm->pnode);
        // HopeFSM_Updata(p_fsm->pnode);
    }
}

// 状态机验证
pType_hope_fsm_t HopeFsm_ValidateState(pType_hope_fsm_t p_fsm, int state_id)
{
    int i;
    if (p_fsm->sta_id == state_id)
    {
        return p_fsm; // 状态有效
    }
    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->sta_id == state_id)
        {
            return p_fsm->sta_list[i]; // 状态有效
        }
    }
    return NULL; // 状态无效
}

/// @brief 根据状态ID切换状态机的状态
/// @param p_fsm 状态机指针
/// @param id 目标状态ID
void HopeFSM_ChangeById(pType_hope_fsm_t p_fsm, int id)
{
    int i;
    pType_hope_fsm_t p_node = NULL;
    // 如果目标状态与当前状态相同，则直接返回
    if (p_fsm->current_sta_id == id)
    {
        return;
    }

    COMP_LOG_DEBUG("HopeFSMChangeById -- pre: %d, next: %d", p_fsm->current_sta_id, id);

    // 验证目标状态ID是否有效
    p_node = HopeFsm_ValidateState(p_fsm, id);
    if (p_node == NULL)
    {
        COMP_LOG_DEBUG("Error: Invalid state ID %d", id);
        return;
    }

    // 如果当前存在活动子状态，则执行退出回调并清空活动子状态
    if (p_fsm->pnode != NULL)
    {
        COMP_LOG_DEBUG("         Exit Sta %d", p_fsm->current_sta_id);
        CALL_IF_NOT_NULL(p_fsm->pnode->ExitCall, p_fsm->pnode);
        p_fsm->pnode = NULL;
    }

    p_fsm->pnode = p_node;
    p_fsm->current_sta_id = id; // 更新状态值

    COMP_LOG_DEBUG("         Enter Sta %d", p_fsm->current_sta_id);
    CALL_IF_NOT_NULL(p_node->EnterCall, p_node);
}

/// @brief 添加一个子状态机
/// @param prt 父状态机
/// @param p 子状态机
void HopeFsm_StaAdd(pType_hope_fsm_t prt, pType_hope_fsm_t p)
{
    int i, j;
    // 检查输入参数是否有效
    if (prt == NULL || p == NULL)
    {
        COMP_LOG_DEBUG("Error: prt or p is NULL");
        return;
    }
    if (prt->sta_list == NULL)
    {
        COMP_LOG_DEBUG("Error: prt->sta_list is NULL");
        return;
    }

    // 设置父子关系
    p->prt = prt;

    // 如果状态机列表已满，则不添加
    if (prt->sta_list_len >= prt->sta_list_max)
    {
        return;
    }

    // 根据 prioritization 添加到合适位置（高优先级在前）
    for (i = 0; i < prt->sta_list_len; i++)
    {
        // 找到第一个优先级低于待插入状态机的位置
        if (prt->sta_list[i]->prioritization < p->prioritization)
        {
            break;
        }
    }

    // 将后面的元素后移，为新元素腾出空间
    for (j = prt->sta_list_len; j > i; j--)
    {
        prt->sta_list[j] = prt->sta_list[j - 1];
    }

    // 在正确位置插入新状态机
    prt->sta_list[i] = p;
    prt->sta_list_len++;
}

void HopeFsm_Init(pType_hope_fsm_t p)
{
    int i;
    COMP_LOG_DEBUG("HopeFsm_Init %s", p->name);
    if (p->InitCall != NULL)
    {
        p->InitCall(p);
    }
    for (i = 0; i < p->sta_list_len; i++)
    {
        if (p->sta_list[i] != NULL)
        {
            HopeFsm_Init(p->sta_list[i]);
        }
    }
}

pType_hope_fsm_t HopeFsm_Get(pType_hope_fsm_t prt, int sta_id)
{
    int i;
    pType_hope_fsm_t p_fsm = prt;
#if HOPE_FSM_ROOT
    if (p_fsm == NULL)
    {
        p_fsm = &g_hope_fsm_root;
    }
#endif
    if (p_fsm == NULL)
    {
        
        return NULL;
    }
    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (p_fsm->sta_list[i]->sta_id == sta_id)
        {
            return p_fsm->sta_list[i];
        }
    }
    return NULL;
}

pType_hope_fsm_t HopeFsm_GetByName(pType_hope_fsm_t prt, const char *name)
{
    int i;
    pType_hope_fsm_t p_fsm = prt;

#if HOPE_FSM_ROOT
    if (p_fsm == NULL)
    {
        p_fsm = &g_hope_fsm_root;
    }
#endif
    if (p_fsm == NULL)
    {
        return NULL;
    }
    for (i = 0; i < p_fsm->sta_list_len; i++)
    {
        if (strcmp(p_fsm->sta_list[i]->name, name) == 0)
        {
            return p_fsm->sta_list[i];
        }
    }
    return NULL;
}

void HopeFSM_ChangeVal(pType_hope_fsm_t p, int val)
{
    ;
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

#if 1
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
#endif // end test main

#endif // end test

#endif
