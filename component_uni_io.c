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
*2026/02/05 main uni_io
- 添加 fw OpenWriteClose, OpenReadClose, 函数
 ***************************************************************************************************
 **/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "component_uni_io.h"
#include "component_log.h"

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
            // 如果有重复的名称，直接返回错误
            COMP_LOG_FW("uni io drv name %s already registered", p_drv->name);
            return IO_ERR_INVALID_ID;
        }
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        // 找到第一个空位置
        if (s_drv_list[i] == NULL)
        {
            s_drv_list[i] = p_drv;
            COMP_LOG_FW("register uni io drv :%s, id %d", p_drv->name, p_drv->id);
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
    COMP_LOG_FW("uni io drv name :%s: not found", name);
    return NULL;
}

int UniIO_Drv_O_W_C(const char *drv_name,const char *file_name,uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout)
{
    pType_COMP_uni_io_t p_drv = UniIO_Drv_GetByName(drv_name);
    if (p_drv == NULL)
    {
    	COMP_LOG_WARN("uni io drv name :%s: not found", drv_name);
        return IO_ERR_INVALID_ID;
    }
    if (file_name != NULL && p_drv->open != NULL)
    {
        if (p_drv->open((void *)file_name) != 0)
        {
        	COMP_LOG_WARN("uni io file name :%s: open failed", file_name);
            return IO_ERR_INVALID_ID;
        }
    }
    if(p_drv->write != NULL)
    {
         if( p_drv->write(addr, dat, len, timeout) != 0)
         {
        	 COMP_LOG_WARN("uni io drv name :%s: write failed", drv_name);
            return IO_ERR_INVALID_ID;
         }
    }
    
    if(p_drv->close != NULL)
    {
        if (p_drv->close(NULL) != 0)
        {
        	COMP_LOG_WARN("uni io drv name :%s: close failed", drv_name);
            return IO_ERR_INVALID_ID;
        }
    }
    COMP_LOG_FW("uni io drv name :%s: write success", drv_name);
    return IO_ERR_NONE;
}

int UniIO_Drv_O_R_C(const char *drv_name,const char *file_name,uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout)
{
    pType_COMP_uni_io_t p_drv = UniIO_Drv_GetByName(drv_name);
    if (p_drv == NULL)
    {
    	COMP_LOG_WARN("uni io drv name :%s: not found", drv_name);
        return IO_ERR_INVALID_ID;
    }
    if (file_name != NULL && p_drv->open != NULL)
    {
        if (p_drv->open((void *)file_name) != 0)
        {
        	COMP_LOG_WARN("uni io file name :%s: open failed", file_name);
            return IO_ERR_INVALID_ID;
        }
    }
    if(p_drv->read != NULL)
    {
         if( p_drv->read(addr, dat, len, timeout) != 0)
         {
        	 COMP_LOG_WARN("uni io drv name :%s: read failed", drv_name);
            return IO_ERR_INVALID_ID;
         }
    }
    
    if(p_drv->close != NULL)
    {
        if (p_drv->close(NULL) != 0)
        {
        	COMP_LOG_WARN("uni io drv name :%s: close failed", drv_name);
            return IO_ERR_INVALID_ID;
        }
    }
    COMP_LOG_FW("uni io drv name :%s: read success", drv_name);
    return IO_ERR_NONE;
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
