/**
 * ____            __                   ____
 * \ \ \     _  __/ /   ____  ____ _   / / /
 *  \ \ \   | |/_/ /   / __ \/ __ `/  / / /
 *  / / /  _>  </ /___/ /_/ / /_/ /   \ \ \
 * /_/_/  /_/|_/_____/\____/\__, /     \_\_\
 *                         /____/
 *
 * \file            xLog
 * \brief           轻型日志库
 */

/*
 * Copyright (c) 2022 R-Hang
 *
 * Author:  R-Hang <none>
 * Version: v1.0.0
 * Date:    2022/04/01
 */

#ifndef __XLOG_H
#define __XLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define XLOG_MAX_MOD_NUM          16    /*-- 最大支持的日志模块数量 --*/
#define XLOG_USER_MSG_BUFF_SIZE   512   /*-- 用户区日志缓存大小 --*/

#define XLOG_LV_MSG_LEN      16    /*-- 日志等级信息长度 --*/
#define XLOG_MOD_NAME_LEN    16    /*-- 日志模块名字长度 --*/
#define XLOG_TIME_MSG_LEN    16    /*-- 日志时间信息长度 --*/
#define XLOG_COLOR_STR_LEN   16    /*-- 日志等级颜色字符长度 --*/
#define XLOG_MSG_BUFF_SIZE   ( XLOG_LV_MSG_LEN      \
                             + XLOG_MOD_NAME_LEN    \
                             + XLOG_TIME_MSG_LEN    \
                             + XLOG_COLOR_STR_LEN   \
                             + 1                    \
                             + XLOG_USER_MSG_BUFF_SIZE )   /*-- 日志缓存大小 --*/

#define XLOG_FMT_LV              0x01
#define XLOG_FMT_MOD_NAME        0x02
#define XLOG_FMT_TIME            0x04
#define XLOG_FMT_COLOR           0x08
#define XLOG_FMT_ALL             0x0F
#define XLOG_FMT_OFF             0x00

typedef struct _S_XLog_Mod* S_XLog_Handle;
typedef uint16_t            T_XLog_Fmt;

struct _S_XLog_Mod {
	uint8_t modId;     /*!< 日志模块Id */
	char    modName[XLOG_MOD_NAME_LEN];     /*!< 日志模块名字 */
	uint8_t logEn;     /*!< 日志使能 */
	uint8_t logLv;     /*!< 日志等级 */
	union {
		struct {
            uint8_t fmtLv     :1;    /*!< 日志等级信息 */
			uint8_t fmtModMsg :1;    /*!< 日志模块信息 */
            uint8_t fmtTime   :1;    /*!< 日志系统时间戳信息 */
			uint8_t fmtColor  :1;    /*!< 日志等级颜色 */
			uint8_t res2      :4;
		} fmtBit;
		uint8_t fmtVal;
	} logFmt;
};

typedef struct {
    uint8_t 	       modCount;    /*!< 当前日志模块数量 */
	struct _S_XLog_Mod xLogModArr[XLOG_MAX_MOD_NUM];    /*!< 日志模块 */
} S_XLog;

/*-- 日志等级 --*/
typedef enum {
	eXLOG_TRACE = 100,
	eXLOG_DEBUG,
	eXLOG_INFO,
	eXLOG_WARN,
	eXLOG_ERROR,
	eXLOG_FATAL,
	eXLOG_OFF,
} E_XLog_Lv;

/*-- 日志模块使能 --*/
typedef enum {
	eXLOG_DISABLE = 0,
	eXLOG_ENABLE,
} E_XLog_En_Stat;

void xLogPrint(const char *fmt, ...);
void xLogMsg(S_XLog_Handle logHandle, E_XLog_Lv lv, const char *lvStr, const char *fmt, ...);

void xLogTest(void);
void xLogInit(void);
void xlogSetEn(S_XLog_Handle logHandle, E_XLog_En_Stat enStat);
void xlogSetLv(S_XLog_Handle logHandle, E_XLog_Lv lv);
void xlogSetFmt(S_XLog_Handle logHandle, T_XLog_Fmt fmt);
S_XLog_Handle xLogCreate(const char * const logModName, T_XLog_Fmt fmt);

extern S_XLog_Handle g_XlogMonitor;
extern S_XLog_Handle g_XlogConsole;
extern S_XLog_Handle g_XlogModbusMaster;

/*-- 编译级别日志输出设置 --*/
#define XLOG_ENABL          1   /*-- 日志使能 0-失能/1-使能 --*/
#define XLOG_COLOR_ENABLE   1   /*-- 日志等级颜色 0-失能/1-使能 --*/

#if (XLOG_ENABL)
	#define xLOG_INIT()                             xLogInit()
	#define xLOG(...)                               xLogPrint(__VA_ARGS__)
	#define xLOG_TRACE(handle, ...)                 xLogMsg(handle, eXLOG_TRACE,    "TRACE",    __VA_ARGS__)
	#define xLOG_DEBUG(handle, ...)                 xLogMsg(handle, eXLOG_DEBUG,    "DEBUG",    __VA_ARGS__)
	#define xLOG_INFO(handle, ...)                  xLogMsg(handle, eXLOG_INFO,     "INFO.",    __VA_ARGS__)
	#define xLOG_WARN(handle, ...)                  xLogMsg(handle, eXLOG_WARN,     "WARN.",    __VA_ARGS__)
	#define xLOG_ERROR(handle, ...)                 xLogMsg(handle, eXLOG_ERROR,    "ERROR",    __VA_ARGS__)
	#define xLOG_FATAL(handle, ...)                 xLogMsg(handle, eXLOG_FATAL,    "FATAL",    __VA_ARGS__)
#else
	#define xLOG_INIT()                             do {} while (0)
	#define xLOG(handle, ...)                       do {} while (0)
	#define xLOG_TRACE(handle, ...)                 do {} while (0)
	#define xLOG_DEBUG(handle, ...)                 do {} while (0)
	#define xLOG_INFO(handle, ...)                  do {} while (0)
	#define xLOG_WARN(handle, ...)                  do {} while (0)
	#define xLOG_ERROR(handle, ...)                 do {} while (0)
	#define xLOG_FATAL(handle, ...)                 do {} while (0)
#endif

#endif
