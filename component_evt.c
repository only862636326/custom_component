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

#if CUST_COMP_EVT

static Type_hope_evt_t evt_list[COMP_EVT_MAX_NUM];

#if COMP_EVT_Async
static Type_hope_evt_trg_t evt_circle_buf[COMP_EVT_MAX_BUF];
int evt_circle_head = 0;
int evt_circle__end = 0;
#endif

/// @brief 事件注册
/// @param id
void HopeEvtRegsterNoCall(int32_t id)
{
    int i;
    i = 0;
    if (id != 0)
    {
        for (i = 0; i < COMP_EVT_MAX_NUM; i++)
        {
            if (evt_list[i].event_id == id) // evt aready in list
            {
                COMP_LOG_INFO("Event aready exist %d", id);
                return;
            }
            if (evt_list[i].event_id == 0) // find empty evt
            {
                evt_list[i].event_id = id;
                COMP_LOG_INFO("HopeEvtRegster First OK: %d", id);
                return;
            }
        }
    }
    // add evt fail
    COMP_LOG_ERROR("Event list full");
    return;
}

/// @brief 事件订阅
/// @param id
/// @param p
void HopeEvtSubsribe(int32_t id, void (*call)(void *))
{
    HopeEvtSubsribeAsync(id, call, NULL);
}

void HopeEvtSubsribeAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *))
{
    int i;
    pType_hope_evt_t p = NULL;

    if (call == NULL)
        return;

    for (i = 0; i < COMP_EVT_MAX_NUM; i++)
    {
        // find event
        if (evt_list[i].event_id == id)
        {
            p = &evt_list[i];
        }
    }

    if (p == NULL)
    {
        //
        COMP_LOG_WARN("HopeEvtSubsribe evt empty %d", id);
        return;
    }

    for (i = 0; i < COMP_EVT_MAX_CALL; i++)
    {
        if (p->call[i] == NULL) // call is not null
        {
            p->call[i] = call;
#if COMP_EVT_Async
            if (finish_call != NULL)
                p->finish_call[i] = finish_call;
#endif
            COMP_LOG_INFO("HopeEvtSubsribe OK: %d", id);
            break;
        }
        if (p->call[i] == call) // call hava add
        {
            COMP_LOG_WARN("HopeEvtSubsribe call exsit: %d", id);
            break;
        }
    }
}

// 获取事件idx 
int32_t HopeEvtGetIdx(int id)
{
    int i;
    i = 0;
    for(i = 0; i < COMP_EVT_MAX_NUM; i++)
    {
        if(evt_list[i].event_id == id)
        {
            return i;
        }
    }
    return -1;
}

void HopeEvtTirggerFast(int32_t idx, void *var)
{
    pType_hope_evt_t p = &evt_list[idx];
    int i;
    i = 0;
    if (p == NULL)
    {
        COMP_LOG_WARN("HopeEvtTirggerFast evt empty : %d", idx);
        return;
    }
    for(i = 0; i < COMP_EVT_MAX_CALL; i++)
    {
        if (p->call[i] == NULL) // call is not null
        {
            break;
        }
        else
        {
            p->call[i](var);
        }
    }
}

/// @brief 事件触发
/// @param id
/// @param p
void HopeEvtTirgger(int32_t id, void *var)
{
    pType_hope_evt_t p = NULL;
    int i;
    for (i = 0; i < COMP_EVT_MAX_NUM; i++)
    {
        if (evt_list[i].event_id == id) // find evt
        {
            p = &evt_list[i];
        }
    }

    if (p == NULL)
    {
        COMP_LOG_WARN("HoepEvtTirgger evt empty : %d", id);
        return;
    }

    for (i = 0; i < COMP_EVT_MAX_CALL; i++)
    {
        // call is not null, call fun
        // call is null, break
        if (p->call[i] == NULL)
        {
            break;
        }
        else
        {
            // COMP_LOG_INFO("tirgger evt");
            p->call[i](var);
        }
#if COMP_EVT_Async
        if (p->finish_call[i] == NULL)
        {
            break;
        }
        else
        {
            // COMP_LOG_INFO("tirgger evt");
            p->finish_call[i](var);
        }
#endif
    }
}

/// @brief
/// @param id
/// @param call
void HopeEvtRegsterCall(int32_t id, void (*call)(void *))
{
    HopeEvtRegsterNoCall(id);
    if (call != NULL)
        HopeEvtSubsribe(id, call);
}

void HopeEvtRegsterAsync(int32_t id, void (*call)(void *), void (*finish_call)(void *))
{
    HopeEvtRegsterNoCall(id);
    if (call != NULL)
        HopeEvtSubsribeAsync(id, call, finish_call);
}

#if COMP_EVT_Async

/// @brief
/// @param id
/// @param p
void HopeEvtTirggerAsync(int32_t id, void *p)
{
    int x;
    x = (evt_circle_head + 1) % COMP_EVT_MAX_BUF;
    // printf("%d %d\n", x, evt_circle_head);
    if (x == evt_circle_head)
    {
        COMP_LOG_WARN("HopeEvtTirggerAsync buff full : %d", id);
        return;
    }
    else
    {
        evt_circle_head++;
        evt_circle_head %= COMP_EVT_MAX_BUF;

        evt_circle_buf[evt_circle_head].event_id = id;
        evt_circle_buf[evt_circle_head].p = p;
    }
}

/// @brief
/// @param p
void HopeEvtTask(void *p)
{
    while (evt_circle__end != evt_circle_head)
    {
        evt_circle__end++;
        evt_circle__end %= COMP_EVT_MAX_BUF;
        HopeEvtTirgger(evt_circle_buf[evt_circle__end].event_id, evt_circle_buf[evt_circle__end].p);
        // delay (10);
    }
}

#endif

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

    HopeEvtTirggerAsync(1, 0x01);
    HopeEvtTirggerAsync(1, 0x02);
    HopeEvtTirggerAsync(2, 0x03);
    HopeEvtTirggerAsync(2, 0x04);
    HopeEvtTirggerAsync(2, 0x05);
    HopeEvtTirggerAsync(2, 0x06);
    HopeEvtTirggerAsync(2, 0x07);
    HopeEvtTirggerAsync(2, 0x08);
    HopeEvtTirggerAsync(2, 0x09);
    HopeEvtTirggerAsync(2, 0x0A);
    HopeEvtTirggerAsync(2, 0x0B);
    HopeEvtTirggerAsync(3, 0x0C);

    HopeEvtTask(NULL);

    return 0;
}

#endif

#endif
