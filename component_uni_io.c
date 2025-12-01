/**
 ***************************************************************************************************
 * @file        component_uni_io.c
 * @author      wsn
 * @version     V1.0
 * @date        2024.11.22
 * @brief       使用 统一读写接口
 *              fsm functon
 *
 * @license     wsn
 ***************************************************************************************************
 *
 *
 * v2025/12/01
 *      1. uni_io中删除 debug功能
 *      2. 添加 dev name 功能, 注册时仅判断name, 不判断id，可通过name打开驱动
 *
 *
 ***************************************************************************************************
 **/

#include <stdio.h>
#include <stdarg.h>
#include "component_uni_io.h"
#include <string.h>
#if CUST_COMP_UNI_IO

static int32_t null_fun(uint32_t a, int32_t b, char *c) {return 0;}

pType_COMP_uni_io_t s_drv_list[MAX_IO_DRV_NUM] = {NULL};
void UniIO_Drv_Register(pType_COMP_uni_io_t p_drv)
{
    int i;
    // 检查输入参数
    if (p_drv == NULL)
    {
        return;
    }    

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        // 名称匹配
        if (strcmp(s_drv_list[i]->name, p_drv->name) == 0)
        {
            // 如果有重复的名称，直接返回
            return;
        }
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        // 找到第一个空位置
        if (s_drv_list[i] == NULL)
        {
            s_drv_list[i] = p_drv;
            return;
        }
    }    
}

pType_COMP_uni_io_t UniIO_Drv_Get(int id)
{
    int i;
    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        if (s_drv_list[i] == NULL)
        {
            continue;
        }
        if (s_drv_list[i]->id == id)
        {
            return s_drv_list[i];
        }
    }
    return NULL;
}

pType_COMP_uni_io_t UniIO_Drv_Open(const char *name)
{
    int i;

    // 检查输入参数
    if (name == NULL)
    {
        return NULL;
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        if (s_drv_list[i] == NULL)
        {
            continue;
        }
        if (strcmp(s_drv_list[i]->name, name) == 0)
        {
            return s_drv_list[i];
        }
    }
    return NULL;
}



#if 0




#endif


#endif


















