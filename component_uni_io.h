#ifndef __COMPONET_UNIIO_H__
#define __COMPONET_UNIIO_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "component_include.h"
#if CUST_COMP_UNI_IO

#ifdef __cplusplus
extern "C"
{
#endif

// IO驱动最大数量
#define MAX_IO_DRV_NUM 10

// 驱动ID宏定义
#define DRV_ID_DEBUG 1

#define IO_ERR_NONE 0          // 无错误
#define IO_ERR_INVALID_ID 1    // 无效的驱动ID
#define IO_ERR_OPEN_FAILED 2   // 打开失败
#define IO_ERR_CLOSE_FAILED 3  // 关闭失败
#define IO_ERR_READ_FAILED 4   // 读取失败
#define IO_ERR_WRITE_FAILED 5  // 写入失败
#define IO_ERR_ASYNC_FAILED 6  // 异步操作失败
#define IO_ERR_CALLBACK_NULL 7 // 回调函数为空

    // IO参数结构体
    typedef struct Type_UniIO_PInfo_t
    {
        uint32_t addr; // 地址
        int32_t len;  // 数据长度
        char *dat;    // 数据指针
    } Type_UniIO_PInfo_t, *pType_UniIO_PInfo_t;

    // 多功能打印结构体
    typedef struct Type_mutfun_print
    {
        void (*printInt)(int32_t);    // 打印整数
        void (*printS)(const char *); // 打印字符串
        void (*printF)(float);        // 打印浮点数
        void (*printHex)(int32_t);    // 打印十六进制数
        void (*putChar)(char);        // 打印单个字符

        void (*println)();                   // 打印换行
        int (*printf)(const char *fmt, ...); // 格式化打印
        void *dev;                           // 设备指针
    } Type_mutfun_print, *pType_mutfun_print;

    // IO驱动结构体
    typedef struct Type_COMP_uni_io_t
    {
        int32_t id; // 驱动ID
        int32_t lock;
        
        // 打开和关闭函数
        int32_t (*open)(void *);
        int32_t (*close)(void *);

        // 同步读写函数
        int32_t (*read)(uint32_t addr, int32_t len, char *dat);
        int32_t (*write)(uint32_t addr, int32_t len, char *dat); // static int32_t uio_write(uint32_t addr, int32_t len, char *dat){  ;}

        // 异步读写函数
        int32_t (*read_async)(uint32_t addr, int32_t len, char *dat);
        int32_t (*write_async)(uint32_t addr, int32_t len, char *dat);

        // 回调读写函数
        int32_t (*read_call)(uint32_t addr, int32_t len, char *dat);
        int32_t (*write_call)(uint32_t addr, int32_t len, char *dat);

        // 调试打印函数
        int (*printf)(const char *fmt, ...);
        int (*vprintf)(const char *fmt, va_list arg);
        pType_mutfun_print debug; // 调试打印实例
    } Type_COMP_uni_io_t, *pType_COMP_uni_io_t;

    // 驱动注册函数
    void UniIO_Drv_Register(pType_COMP_uni_io_t p_drv);

    // 驱动获取函数
    pType_COMP_uni_io_t UniIO_Drv_Get(int id);

    // 全局变量
    extern Type_COMP_uni_io_t debug_drv;   // 调试驱动实例
    extern Type_mutfun_print mulfun_print; // 多功能打印实例

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#endif // __COMPONET_UNIIO_H__







