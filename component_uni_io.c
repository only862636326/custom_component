/**
 ***************************************************************************************************
 * @file        component_uni_io.c
 * @author      wsn
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
*2025/12/09 uni_io
- 改为UniIO_Drv_OPEN 改为UniIO_Drv_GetByName， 更符合实际
*
 ***************************************************************************************************
 **/

#include <stdio.h>
#include <stdarg.h>
#include "component_uni_io.h"
#include <string.h>
#if CUST_COMP_UNI_IO

pType_COMP_uni_io_t s_drv_list[MAX_IO_DRV_NUM] = {NULL};

uint32_t UniIO_Drv_Register(pType_COMP_uni_io_t p_drv)
{
    int i;
    // 检查输入参数
    if (p_drv == NULL)
    {
        return IO_ERR_INVALID_ID;
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        // 名称匹配
        if (strcmp(s_drv_list[i]->name, p_drv->name) == 0)
        {
            // 如果有重复的名称，直接返回
            return IO_ERR_INVALID_ID;
        }
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        // 找到第一个空位置
        if (s_drv_list[i] == NULL)
        {
            s_drv_list[i] = p_drv;
            return IO_ERR_NONE;
        }
    }
    return IO_ERR_INVALID_ID;
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

pType_COMP_uni_io_t UniIO_Drv_GetByName(const char *name)
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


static int drv_read(uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout)
{
    pins_channel_type_t val = PINS_DRV_ReadPins((GPIO_Type*) addr);
    val >>= len;
    return val & 0x01;
}

static int drv_write(uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout)
{
    PINS_DRV_WritePin((GPIO_Type*) addr, len, (int) dat);
    return 0;
}
static int drv_init(void *p)
{    
    return 0;    
}


UNI_IO_DEFINE_DRV(drv_gpio, 13);

#endif

#endif
