
/**
 ***************************************************************************************************
 * @file        component_log.h
 * @author      wsn
 * @version     V1.0
 * @date        2024.11.27
 * @brief       打印组件自定义
 *
 *
 * @license     wsn
 ***************************************************************************************************
 * @attention
 *
 *
 * 版本说明
 *
 * 修改说明
 *     24/11/28 v1.0.0
 *
 ***************************************************************************************************
 **/

#include <stdio.h>

// 使用标准printf而不是debug_drv.printf
#define COMP_PRINTF printf

#define get_sys_time()

#define COMP_LOG_LEVEL COMP_LOG_LEVEL_DEBUG

#define COMP_LOG_LEVEL_OFF 0
#define COMP_LOG_LEVEL_USER 1
#define COMP_LOG_LEVEL_ERROR 2
#define COMP_LOG_LEVEL_WARN 3
#define COMP_LOG_LEVEL_INFO 4
#define COMP_LOG_LEVEL_DEBUG 5
#define COMP_LOG_LEVEL_FW 6

#define COMP_LOG_LEVEL_LOOP_SLOW 10
#define COMP_LOG_LEVEL_LOOP_FAST 20
#define COMP_LOG_LEVEL_ALL 0xff


#define COMP_LOG_FW(format, ...)                                                                \
    do                                                                                          \
    {                                                                                           \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_FW)                                                \
        {                                                                                       \
            get_sys_time();                                                                     \
            COMP_PRINTF("[%20s] [%6d] [FW ]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                       \
    } while (0)

#define COMP_LOG_DEBUG(format, ...)                                                               \
    do                                                                                            \
    {                                                                                             \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_DEBUG)                                               \
        {                                                                                         \
            get_sys_time();                                                                       \
            COMP_PRINTF("[%20s] [%6d] [DEBUG]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                         \
    } while (0)

#define COMP_LOG_INFO(format, ...)                                                                \
    do                                                                                            \
    {                                                                                             \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_INFO)                                                \
        {                                                                                         \
            get_sys_time();                                                                       \
            COMP_PRINTF("[%20s] [%6d] [INFO ]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                         \
    } while (0)

#define COMP_LOG_WARN(format, ...)                                                                \
    do                                                                                            \
    {                                                                                             \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_WARN)                                                \
        {                                                                                         \
            get_sys_time();                                                                       \
            COMP_PRINTF("[%20s] [%6d] [WARN ]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                         \
    } while (0)

#define COMP_LOG_ERROR(format, ...)                                                               \
    do                                                                                            \
    {                                                                                             \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_ERROR)                                               \
        {                                                                                         \
            get_sys_time();                                                                       \
            COMP_PRINTF("[%20s] [%6d] [ERROR]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                         \
    } while (0)

#define COMP_LOG_USER(format, ...)                                                               \
    do                                                                                           \
    {                                                                                            \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_USER)                                               \
        {                                                                                        \
            get_sys_time();                                                                      \
            COMP_PRINTF("[%20s] [%6d] [USER]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                        \
    } while (0)

#define COMP_LOG_LOOP_FAST(format, ...)                                                          \
    do                                                                                           \
    {                                                                                            \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_LOOP_FAST)                                          \
        {                                                                                        \
            get_sys_time();                                                                      \
            COMP_PRINTF("[%20s] [%6d] [FAST]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                        \
    } while (0)

#define COMP_LOG_LOOP_SLOW(format, ...)                                                          \
    do                                                                                           \
    {                                                                                            \
        if (COMP_LOG_LEVEL >= COMP_LOG_LEVEL_LOOP_SLOW)                                          \
        {                                                                                        \
            get_sys_time();                                                                      \
            COMP_PRINTF("[%20s] [%6d] [SLOW]  " format "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        }                                                                                        \
    } while (0)
