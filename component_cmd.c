/**
 ***************************************************************************************************
 * @file        component_evt.c
 * @author      wsn
 * @version     v0.0.0
 * @date        2024.11.27
 * @brief       使用C实现的简易命令管理
 *
 *
 * @license     wsn
 ***************************************************************************************************
 * @attention
 *  命令与evt不同的是, 它仅有一个回调函数, 回调函数有返回参数
 *
 *
 *
 * 版本说明
 *
 * 修改说明
 *     24/11/28 v1.0.0
 *
 ***************************************************************************************************
 **/

#include "component_cmd.h"
#if CUST_COMP_CMD

static Type_hope_cmd_t cmd_list[COMP_CMD_MAX_NUM];

/// @brief
/// @param id
/// @param p
void HopeCMDRigster(int32_t id, void *p)
{
    int i;
    if(id == 0)
    {
        COMP_LOG_WARN("HoepCMDRigster CMD id '0' is not allow ");
        return;
    }

    for (i = 0; i < COMP_CMD_MAX_NUM; i++)
    {
        if (cmd_list[i].id == id) // evt aready in list
        {
            COMP_LOG_INFO("HoepCMDRev CMD aready exist %d", id);
            return;
        }
        if (cmd_list[i].id == 0) // find empty evt
        {
            cmd_list[i].id = id;
            cmd_list[i].call = p;
            COMP_LOG_INFO("HoepCMDRev OK: %d", id);
            return;
        }
    }

    // add evt fail
    COMP_LOG_ERROR("HoepCMDRev list full");
}

/// @brief
/// @param id
/// @param p
/// @return
int HopeCMDSend(int32_t id, void *p)
{
    int i;
    if(id == 0)
    {
        COMP_LOG_WARN("HoepCMDSend CMD empty : %d", id);
        return 0;
    }

    for (i = 0; i < COMP_CMD_MAX_NUM; i++)
    {
        // find event
        if (cmd_list[i].id == id)
        {
            if (cmd_list[i].call(p) != NULL)
                return cmd_list[i].call(p);
        }
    }
    COMP_LOG_WARN("HoepCMDSend CMD empty : %d", id);
    return 0;
}

int HopeCMDSendIdx(int32_t idx, void *p)
{
    if (idx < 0 || idx >= COMP_CMD_MAX_NUM)
    {
        COMP_LOG_ERROR("HopeCMDSendIdx idx error: %d", idx);
        return 0;
    }

    if (cmd_list[idx].id == 0)
    {
        COMP_LOG_WARN("HoepCMDSendIdx CMD empty idx: %d", idx);
        return 0;
    }
    if (cmd_list[idx].call(p) == NULL)
    {
        COMP_LOG_WARN("HoepCMDSendIdx CMD call NULL idx: %d", idx);
        return 0;
    }
    return cmd_list[idx].call(p);
}

#endif
