#ifndef __COMPONET_UNIIO_H__
#define __COMPONET_UNIIO_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "component_config.h"

#if CUST_COMP_UNI_IO


#define IO_ERR_NONE 0		   // 无错误
#define IO_ERR_INVALID_ID 1	   // 无效的驱动ID
#define IO_ERR_OPEN_FAILED 2   // 打开失败
#define IO_ERR_CLOSE_FAILED 3  // 关闭失败
#define IO_ERR_READ_FAILED 4   // 读取失败
#define IO_ERR_WRITE_FAILED 5  // 写入失败
#define IO_ERR_ASYNC_FAILED 6  // 异步操作失败
#define IO_ERR_CALLBACK_NULL 7 // 回调函数为空

// 2. 外层宏：批量定义驱动结构体
#define UNI_IO_DEFINE_DRV(DRV_NAME, DRV_ID) \
	Type_COMP_uni_io_t DRV_NAME = {         \
		.id = DRV_ID,                       \
		.name = STRINGIFY(DRV_NAME),        \
		.init = drv_init,                   \
		.write = drv_write,                 \
		.read = drv_read,                   \
	}

#define UNI_IO_DEFINE_DRV_ARG(DRV_NAME, DRV_ID, OPEN, CLOSE, READ, WRITE) \
	Type_COMP_uni_io_t DRV_NAME = {                                       \
		.id = DRV_ID,                                                     \
		.name = STRINGIFY(DRV_NAME),                                      \
		.open = OPEN,                                                     \
		.close = CLOSE,                                                   \
		.write = WRITE,                                                   \
		.read = READ,                                                     \
	}

// IO参数结构体
typedef struct Type_UniIO_PInfo_t
{
	uint32_t addr; // 地址
	uint8_t *dat;  // 数据指针
	uint32_t len;  // 数据长度
} Type_UniIO_PInfo_t, *pType_UniIO_PInfo_t;

// IO驱动结构体
typedef struct Type_COMP_uni_io_t
{
	int32_t id; // 驱动ID
#if CUST_COMP_UNI_IO_ASYNC
	int32_t lock;
#endif
	char *name; // 驱动名称

	// 打开和关闭函数
	int32_t (*open)(void *);
	int32_t (*close)(void *);
	int32_t (*init)(void *);
	// 同步读写函数
	int32_t (*read)(uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout);
	int32_t (*write)(uint32_t addr, uint8_t *dat, uint32_t len, uint32_t timeout);

#if CUST_COMP_UNI_IO_ASYNC
	// 异步读写函数
	int32_t (*read_async)(uint32_t addr, uint8_t *dat, uint32_t len);
	int32_t (*write_async)(uint32_t addr, uint8_t *dat, uint32_t len);

	// 回调读写函数
	int32_t (*read_call)(uint32_t addr, uint8_t *dat, uint32_t len);
	int32_t (*write_call)(uint32_t addr, uint8_t *dat, uint32_t len);
#endif

#if CUST_COMP_UNI_IO_PRINT
	// 调试打印函数
	int (*printf)(const char *fmt, ...);
	int (*vprintf)(const char *fmt, va_list arg);
#endif

} Type_COMP_uni_io_t, *pType_COMP_uni_io_t;


#define uni_read(drv, addr, dat, len, timeout) if (drv->read != NULL) drv->read(addr, dat, len, timeout)
#define uni_write(drv, addr, dat, len, timeout) if (drv->write != NULL) drv->write(addr, dat, len, timeout)

#ifdef __cplusplus
extern "C"
{
#endif

	// 驱动注册函数
	uint32_t UniIO_Drv_Register(pType_COMP_uni_io_t p_drv);

	// 驱动获取函数
	pType_COMP_uni_io_t UniIO_Drv_Get(int id);
	pType_COMP_uni_io_t UniIO_Drv_GetByName(const char *name);
	// 全局变量

#ifdef __cplusplus
} // extern "C"
#endif

#endif

#endif // __COMPONET_UNIIO_H__
