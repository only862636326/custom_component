/**
 ***************************************************************************************************
 * @file        component_evt.c
 * @author      wsn
 * @version     v0.0.0
 * @date        2024.11.22
 * @brief       使用C实现的简易事件管理
 *              fsm functon
 *
 * @license     MIT
 ***************************************************************************************************
 * @attention
 *  使用数数组，
 *  最大事件数，最大回调函数
 *  都有限制
 *
 *  回调函数立即运行，注意不要堵塞正常功能
 *
 *  事件注册 extern void HopeEvtRegster(uint32_t id);
 *  事件订阅 extern void HopeEvtSubsribe(uint32_t id, void (*call)(void *));
 *  事件触发 extern void HoepEvtTirgger(uint32_t id, void *p);
 *
 *
 *
 * 版本说明
 *
 * 修改说明
 *     24/11/22 v1.0.0
 *     24/11/27 v1.1.0 添加注册时自带回调函数的函数
 *     24/11/27 v1.2.0 添加异步事件功能
 *
 *     25/11/20 v1.3.0 添加可通过idx快速触发事件
 *
 ***************************************************************************************************
 **/

#include "component_evt.h"
#include "component_log.h"
#include <stdio.h>
#include <string.h>

#if CUST_COMP_EVT

static Type_hope_evt_t evt_list[COMP_EVT_MAX_NUM];
static Type_evn_call_list_t evt_call_list[COMP_EVT_MAX_CALL];

/// @brief 事件注册
/// @param name
/// @return 事件ID
int32_t HopeEvtRegsterNoCall(const char *name)
{
    int i;
    i = 0;
    if (name != NULL)
    {
        for (i = 1; i < COMP_EVT_MAX_NUM; i++)
        {
            if (evt_list[i].event_id != 0 && strcmp(evt_list[i].name, name) == 0) // evt aready in list
            {
                COMP_LOG_FW("Event aready exist %s", name);
                return evt_list[i].event_id;
            }

            if (evt_list[i].event_id == 0) // find empty evt
            {
                evt_list[i].event_id = i;
                strncpy(evt_list[i].name, name, COMP_EVT_NAME_LEN - 1);
                evt_list[i].name[COMP_EVT_NAME_LEN - 1] = '\0';
                evt_list[i].call_list = NULL;
                COMP_LOG_FW("HopeEvtRegster First OK: %s", name);
                return evt_list[i].event_id;
            }
        }
    }
    // add evt fail
    COMP_LOG_ERROR("Event list full");
    return 0;
}

/// @brief 事件订阅
/// @param name
/// @param call
/// @return 0 成功 -1 失败
int32_t HopeEvtSubsribe(const char *name, void (*call)(void *))
{
    int i;
    pType_hope_evt_t p = NULL;

    if (call == NULL || name == NULL)
        return -1;

    for (i = 1; i < COMP_EVT_MAX_NUM; i++)
    {
        // find event
        if (evt_list[i].event_id != 0 && strcmp(evt_list[i].name, name) == 0)
        {
            p = &evt_list[i];
            break;
        }
    }

    if (p == NULL)
    {
        //
        COMP_LOG_WARN("HopeEvtSubsribe evt empty %s", name);
        return -1;
    }

    // Check if call already exists in the list
    pType_evn_call_list_t current = p->call_list;
    while (current != NULL)
    {
        if (current->call == call)
        {
            COMP_LOG_WARN("HopeEvtSubsribe call exsit: %s", name);
            return -1;
        }
        current = current->next_call;
    }

    // Find an empty slot in the static call list
    for (i = 1; i < COMP_EVT_MAX_CALL; i++)
    {
        if (evt_call_list[i].call == NULL)
        {
            evt_call_list[i].call = call;
            evt_call_list[i].next_call = p->call_list;
            p->call_list = &evt_call_list[i];
            COMP_LOG_FW("HopeEvtSubsribe OK: %s", name);
            return 0;
        }
    }
    // No empty slot found
    COMP_LOG_ERROR("Call list full");
    return -1;
}

// 获取事件idx 
pType_hope_evt_t HopeEvtGet(const char *name)
{
    int i;
    i = 0;
    for(i = 1; i < COMP_EVT_MAX_NUM; i++)
    {
        if(evt_list[i].event_id != 0 && strcmp(evt_list[i].name, name) == 0)
        {
            return &evt_list[i];
        }
    }
    return NULL;
}

int32_t HopeEvtTirggerFast(int32_t idx, void *var)
{
    pType_hope_evt_t p = &evt_list[idx];
    if (p->event_id == EVT_NONE)
    {
        COMP_LOG_WARN("HopeEvtTirggerFast evt empty : %d", idx);
        return -1;
    }
    // Traverse the static call list
    pType_evn_call_list_t current = p->call_list;
    while (current != NULL)
    {
        current->call(var);
        current = current->next_call;
    }
    return 0;
}

/// @brief 事件触发
/// @param name
/// @param p
int32_t HopeEvtTirgger(const char *name, void *var)
{
    pType_hope_evt_t p = NULL;
    int i;
    for (i = 1; i < COMP_EVT_MAX_NUM; i++)
    {
        if (evt_list[i].event_id != 0 && strcmp(evt_list[i].name, name) == 0) // find evt
        {
            COMP_LOG_FW("HopeEvtTirgger evt : %s", name);
            p = &evt_list[i];
            break;
        }
    }

    if (p == NULL)
    {
        COMP_LOG_WARN("HoepEvtTirgger evt empty : %s", name);
        return -1;
    }

    // Traverse the static call list
    pType_evn_call_list_t current = p->call_list;
    while (current != NULL)
    {
        current->call(var);
        current = current->next_call;
    }
    return 0;
}

/// @brief
/// @param name
/// @param call
/// @return 事件ID
int32_t HopeEvtRegsterCall(const char *name, void (*call)(void *))
{
    int32_t id = HopeEvtRegsterNoCall(name);
    if (call != NULL)
        HopeEvtSubsribe(name, call);
    return id;
}

#if 0
// demo
void evt_call(void *p)
{
    printf("call vet : %d\n", p);
}

int main(int argc, char const *argv[])
{
    /* code */
    printf("HELLO\n");
    HopeEvtRegster(1, evt_call);
    HopeEvtRegster(2, evt_call);

    HopeEvtTirggerName("event1", (void *)0x01);
    HopeEvtTirggerName("event1", (void *)0x02);
    HopeEvtTirggerName("event2", (void *)0x03);
    HopeEvtTirggerName("event2", (void *)0x04);
    HopeEvtTirggerName("event2", (void *)0x05);

    return 0;
}

#endif

#endif
