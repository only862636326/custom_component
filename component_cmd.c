/**
 ***************************************************************************************************
 * @file        component_cmd.c
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
#include <string.h>


#if CUST_COMP_CMD

static pType_hope_cmd_t cmd_list[COMP_CMD_MAX_NUM];

/// @brief
/// @param pcmd
int HopeCMDRigster(pType_hope_cmd_t pcmd)
{
    int i;
    if (pcmd == NULL)
    {
        COMP_LOG_WARN("HopeCMDRigster pcmd is NULL");
        return -1;
    }

    for (i = 1; i < COMP_CMD_MAX_NUM; i++)
    {
        if (cmd_list[i] == NULL)
        {
            cmd_list[i] = pcmd;
            pcmd->id = i;
            COMP_LOG_FW("HopeCMDRigster OK: %d %s", pcmd->id, pcmd->name ? pcmd->name : "");
            return i;
        }
    }

    COMP_LOG_ERROR("HopeCMDRigster list full");
    return -1;
}

/// @brief
/// @param name
/// @return
int HopeCMDSendName(const char *name)
{
    int i;
    if (name == NULL)
    {
        COMP_LOG_WARN("HopeCMDSendName name is NULL");
        return -1;
    }

    for (i = 0; i < COMP_CMD_MAX_NUM; i++)
    {
        if (cmd_list[i] != NULL && cmd_list[i]->name != NULL && strcmp(cmd_list[i]->name, name) == 0)
        {
            if (cmd_list[i]->call != NULL)
            {
                COMP_LOG_FW("HopeCMDSendName call OK: %s", name);
                return cmd_list[i]->call(NULL);
            }
            else
            {
                COMP_LOG_WARN("HopeCMDSendName call is NULL: %s", name);
                return -1;
            }
        }
    }
    COMP_LOG_WARN("HopeCMDSendName CMD not found: %s", name);
    return -1;
}

int HopeCMDSendIdx(int32_t idx)
{
    if (idx < 0 || idx >= COMP_CMD_MAX_NUM)
    {
        COMP_LOG_ERROR("HopeCMDSendIdx idx error: %d", idx);
        return -1;
    }

    if (cmd_list[idx] == NULL)
    {
        COMP_LOG_WARN("HopeCMDSendIdx CMD empty idx: %d", idx);
        return -1;
    }
    if (cmd_list[idx]->call == NULL)
    {
        COMP_LOG_WARN("HopeCMDSendIdx CMD call NULL idx: %d", idx);
        return -1;
    }
    return cmd_list[idx]->call(NULL);
}

int HopeCMDSendFast(int32_t idx)
{
    return cmd_list[idx]->call(NULL);
}

pType_hope_cmd_t HopeCMDGet(const char *name)
{
    int i;
    if (name == NULL)
    {
        COMP_LOG_WARN("HopeCMDGet name is NULL");
        return NULL;
    }
    for(i = 0; i < COMP_CMD_MAX_NUM;i++)
    {
        if (cmd_list[i] != NULL && cmd_list[i]->name != NULL && strcmp(cmd_list[i]->name, name) == 0)
        {
            return cmd_list[i];
        }
    }
    COMP_LOG_WARN("HopeCMDGet CMD not found: %s", name);
    return NULL;
}


#endif
