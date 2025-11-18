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
 *
 *
 *
 ***************************************************************************************************
 **/

#include <stdio.h>
#include <stdarg.h>
#include "component_uni_io.h"
#if CUST_COMP_UNI_IO
#define MAX_IO_DRV_NUM 10

static int32_t null_fun(uint32_t a, int32_t b, char *c) {return 0;}

static void printInt(int32_t p);
static void printS(const char *p);
static void printF(float p);
static void printHex(int32_t p);
static void putChar(char p);
static void println();
static int cust_printf(const char *fmt, ...);

Type_mutfun_print mulfun_print =
    {
        .printInt = printInt,
        .printS = printS,
        .printF = printF,
        .printHex = printHex,
        .putChar = putChar,
        .println = println,
        .printf = cust_printf,
};

Type_COMP_uni_io_t debug_drv =
    {
        .id = -1,
        .write = null_fun,
        .read = null_fun,

        .write_async = null_fun,
        .read_async = null_fun,

        .read_call = null_fun,
        .write_call = null_fun,

        .printf = printf,
        .vprintf = vprintf,
        .debug = &mulfun_print,
};

pType_COMP_uni_io_t s_drv_list[MAX_IO_DRV_NUM] = {NULL};
void UniIO_Drv_Register(pType_COMP_uni_io_t p_drv)
{
    int i;
    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        if (s_drv_list[i] == NULL)
        {
            s_drv_list[i] = p_drv;
            if (p_drv->id == DRV_ID_DEBUG)
            {
                debug_drv.id = p_drv->id;
                debug_drv.printf = p_drv->printf;
            }
            // p_drv->debug = &mulfun_print;
            return;
        }
        else if (s_drv_list[i]->id == p_drv->id)
        {
            debug_drv.printf("p_drv id exist");
            return;
        }
    }
}

pType_COMP_uni_io_t UniIO_Drv_Get(int id)
{
    int i;
    if (s_drv_list[i] == NULL || s_drv_list[i]->id == 0)
    {
        return NULL;
    }

    for (i = 0; i < MAX_IO_DRV_NUM; i++)
    {
        if (s_drv_list[i]->id == 0)
        {
            return NULL;
        }
        if (s_drv_list[i]->id == id)
        {
            return s_drv_list[i];
        }
    }
    return NULL;
}

void printInt(int32_t p) { debug_drv.printf("%d ", p); }
void printS(const char *p) { debug_drv.printf("%s ", p); }
void printF(float p) { debug_drv.printf("%f ", p); }
void printHex(int32_t p) { debug_drv.printf("0x%X ", p); }
void putChar(char p) { debug_drv.printf("%c ", p); }
void println() { debug_drv.printf("\r\n"); }

int cust_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int ret = debug_drv.vprintf(fmt, args); // 使用 vprintf 代替 printf
    va_end(args);
    return ret;
}


#if 0




#endif


#endif


















