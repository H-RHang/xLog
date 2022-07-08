/**
 * ____            __                   ____
 * \ \ \     _  __/ /   ____  ____ _   / / /
 *  \ \ \   | |/_/ /   / __ \/ __ `/  / / /
 *  / / /  _>  </ /___/ /_/ / /_/ /   \ \ \
 * /_/_/  /_/|_/_____/\____/\__, /     \_\_\
 *                         /____/
 *
 * \file            xLog
 * \brief           ������־��
 */

/*
 * Copyright (c) 2022 R-Hang
 *
 * Author:  R-Hang <none>
 * Version: v1.0.0
 * Date:    2022/04/01
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "xLog.h"
#include "xLog_port.h"

#define XLOG_LOGO \
"\r\n\
 ____            __                   ____ \r\n\
 \\ \\ \\     _  __/ /   ____  ____ _   / / / \r\n\
  \\ \\ \\   | |/_/ /   / __ \\/ __ `/  / / /  \r\n\
  / / /  _>  </ /___/ /_/ / /_/ /   \\ \\ \\  \r\n\
 /_/_/  /_/|_/_____/\\____/\\__, /     \\_\\_\\ \r\n\
                         /____/            \r\n\
\r\n"

//"\n\
// ____            __                   ____ \n\
// \ \ \     _  __/ /   ____  ____ _   / / / \n\
//  \ \ \   | |/_/ /   / __ \/ __ `/  / / /  \n\
//  / / /  _>  </ /___/ /_/ / /_/ /   \ \ \  \n\
// /_/_/  /_/|_/_____/\____/\__, /     \_\_\ \n\
//                         /____/            \n\
//"


static S_XLog s_XLog;
static char   s_XLogMsgBuff[XLOG_MSG_BUFF_SIZE];

extern void logUartInit(void);

#if (XLOG_COLOR_ENABLE)

static const char *s_pXLogLvColorsStrArr[] = {
    "\033[34m",    /*-- eXLOG_TRACE Color --*/
    "\033[36m",    /*-- eXLOG_DEBUG Color --*/
    "\033[32m",    /*-- eXLOG_INFO Color --*/
    "\033[33m",    /*-- eXLOG_WARN Color --*/
    "\033[31m",    /*-- eXLOG_ERROR Color --*/
    "\033[35m"     /*-- eXLOG_FATAL Color --*/
};

/**
 * \brief       ��ȡ��־�ȼ������ɫ
 * \param[in]	E_XLog_Lv: ����ȼ� \ref E_XLog_Lv
 * \return      none
 */
static const char *xlog_get_lv_color_str(E_XLog_Lv lv)
{
    switch (lv) {
        case eXLOG_TRACE:    return s_pXLogLvColorsStrArr[0];
        case eXLOG_DEBUG:    return s_pXLogLvColorsStrArr[1];
        case eXLOG_INFO:     return s_pXLogLvColorsStrArr[2];
        case eXLOG_WARN:     return s_pXLogLvColorsStrArr[3];
        case eXLOG_ERROR:    return s_pXLogLvColorsStrArr[4];
        case eXLOG_FATAL:    return s_pXLogLvColorsStrArr[5];
        case eXLOG_OFF:      return s_pXLogLvColorsStrArr[0];
        default:             return s_pXLogLvColorsStrArr[0];
    }
}

#endif

S_XLog_Handle g_XlogMonitor;
S_XLog_Handle g_XlogConsole;
S_XLog_Handle g_XlogModbusMaster;

void xLogTest(void)
{
    xLOG(XLOG_LOGO);

    xLOG("xLog Version: v1.0.0 \r\n");

    g_XlogMonitor      = xLogCreate("Monitor", XLOG_FMT_ALL);
    g_XlogConsole      = xLogCreate("Console", XLOG_FMT_ALL);
    g_XlogModbusMaster = xLogCreate("ModbusMaster", XLOG_FMT_ALL);

    xlogSetEn(g_XlogMonitor, eXLOG_ENABLE);
    xlogSetLv(g_XlogMonitor, eXLOG_TRACE);
    xlogSetFmt(g_XlogMonitor, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    xlogSetEn(g_XlogConsole, eXLOG_ENABLE);
    xlogSetLv(g_XlogConsole, eXLOG_TRACE);
    xlogSetFmt(g_XlogConsole, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    xlogSetEn(g_XlogModbusMaster, eXLOG_ENABLE);
    xlogSetLv(g_XlogModbusMaster, eXLOG_TRACE);
    xlogSetFmt(g_XlogModbusMaster, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    xLOG_TRACE(g_XlogConsole, "Hello xLog TRACE \r\n");
    xLOG_DEBUG(g_XlogConsole, "Hello xLog DEBUG \r\n");
    xLOG_INFO(g_XlogConsole,  "Hello xLog INFO. \r\n");
    xLOG_WARN(g_XlogConsole,  "Hello xLog WARN. \r\n");
    xLOG_ERROR(g_XlogConsole, "Hello xLog ERROR \r\n");
    xLOG_FATAL(g_XlogConsole, "Hello xLog FATAL \r\n");

    xLOG("\r\n");

//    xLOG_TRACE(g_XlogConsole, "Hello xLog TRACE\r\n");
//    xLOG_DEBUG(g_XlogConsole, "Hello xLog DEBUG\r\n");
//    xLOG_INFO(g_XlogConsole, "Hello xLog INFO.\r\n");
//    xLOG_WARN(g_XlogConsole, "Hello xLog WARN.\r\n");
//    xLOG_ERROR(g_XlogConsole, "Hello xLog ERROR\r\n");
//    xLOG_FATAL(g_XlogConsole, "Hello xLog FATAL\r\n");

//    xLOG("\r\n");
//    xlogSetEn(g_XlogModbusMaster, eXLOG_DISABLE);
}

/**
 * \brief       ��־��ʼ��
 * \return      none
 */
void xLogInit(void)
{
	memset((void *) &s_XLog, 0, sizeof(S_XLog));

    xLogTest();
}

/**
 * \brief       ��־ģ�鴴��
 * \param[in]   logModName: ��־ģ������
 * \param[in]	fmt: ��־��ʽ
 * \return      ��־ģ����
 */
S_XLog_Handle
xLogCreate(const char * const logModName, T_XLog_Fmt fmt)
{
	if (s_XLog.modCount >= XLOG_MAX_MOD_NUM) {
        return (S_XLog_Handle) &s_XLog.xLogModArr[s_XLog.modCount];
	}

	s_XLog.xLogModArr[s_XLog.modCount].modId = s_XLog.modCount;
	s_XLog.xLogModArr[s_XLog.modCount].logEn = eXLOG_ENABLE;
	s_XLog.xLogModArr[s_XLog.modCount].logLv = eXLOG_WARN;
	s_XLog.xLogModArr[s_XLog.modCount].logFmt.fmtVal = fmt;

	for( uint8_t i = 0; i < XLOG_MOD_NAME_LEN; i++ ) {
		s_XLog.xLogModArr[s_XLog.modCount].modName[i] = logModName[i];

		if( logModName[i] == 0x00 )
		{
			break;
		}
	}

	s_XLog.modCount++;

	return (S_XLog_Handle) &s_XLog.xLogModArr[s_XLog.modCount - 1];
}

/**
 * \brief       ������־ģ��ʹ��״̬
 * \param[in]	logHandle: ��־ģ����
 * \param[in]	enStat: ʹ��״̬ \ref E_XLog_En_Stat
 * \return      none
 */
void xlogSetEn(S_XLog_Handle logHandle, E_XLog_En_Stat enStat)
{
	logHandle->logEn = enStat;
}

/**
 * \brief       ������־ģ������ȼ�
 * \param[in]	logHandle: ��־ģ����
 * \param[in]	E_XLog_Lv: ����ȼ� \ref E_XLog_Lv
 * \return      none
 */
void xlogSetLv(S_XLog_Handle logHandle, E_XLog_Lv lv)
{
	logHandle->logLv = lv;
}

/**
 * \brief       ������־��ʽ
 * \param[in]	logHandle: ��־ģ����
 * \return      none
 */
void xlogSetFmt(S_XLog_Handle logHandle, T_XLog_Fmt fmt)
{
	logHandle->logFmt.fmtVal = fmt;
}

/**
 * \brief      ��־��Ϣ���
 * \return     none
 */
void xLogPrint(const char *fmt, ...)
{
	xLogPortLock();

	va_list args;
	va_start (args, fmt);
	vsnprintf(s_XLogMsgBuff, XLOG_MSG_BUFF_SIZE, fmt, args);
	va_end(args);

	xLogPort(s_XLogMsgBuff, strlen(s_XLogMsgBuff));

	xLogPortUnLock();
}

/**
 * \brief        ��־��Ϣ���������־�ȼ�������ģ��
 * \param[in]    logHandle: ��־ģ����
 * \return       none
 */
void xLogMsg(S_XLog_Handle logHandle, E_XLog_Lv lv, const char *lvStr, const char *fmt, ...)
{
    uint16_t len, offset = 0;

	if (logHandle->logEn != eXLOG_ENABLE) return;

	xLogPortLock();

	/*-- �ж���־�ȼ� --*/
	if (lv >= logHandle->logLv) {

		/*-- �����־�ȼ���Ϣ --*/
        if (logHandle->logFmt.fmtBit.fmtLv) {
            #if (XLOG_COLOR_ENABLE)
            len = (XLOG_LV_MSG_LEN + XLOG_COLOR_STR_LEN);

            /*-- �����־�ȼ���ɫ��ʽ --*/
            if (logHandle->logFmt.fmtBit.fmtColor) {
                offset = snprintf(s_XLogMsgBuff, len, "[%s%s\033[0m]", xlog_get_lv_color_str(lv), lvStr);
                offset = offset > len - 1 ? len - 1 : offset;
            } else {
                offset = snprintf(s_XLogMsgBuff, XLOG_LV_MSG_LEN, "[%s]", lvStr);
                offset = offset > XLOG_LV_MSG_LEN - 1 ? XLOG_LV_MSG_LEN - 1 : offset;
            }
            #else
            offset = snprintf(s_XLogMsgBuff, XLOG_LV_MSG_LEN, "[%s]", lvStr);
            offset = offset > XLOG_LV_MSG_LEN - 1 ? XLOG_LV_MSG_LEN - 1 : offset;
            #endif
        }

		/*-- �����־ģ����Ϣ --*/
		if (logHandle->logFmt.fmtBit.fmtModMsg) {
			len    =  snprintf(&s_XLogMsgBuff[offset], XLOG_MOD_NAME_LEN, "[%s]", logHandle->modName);
            len    =  len > XLOG_MOD_NAME_LEN - 1 ? XLOG_MOD_NAME_LEN - 1 : len;
            offset += len;
		}

		/*-- �����־ϵͳʱ��� --*/
		if (logHandle->logFmt.fmtBit.fmtTime) {
			len    =  snprintf(&s_XLogMsgBuff[offset], XLOG_TIME_MSG_LEN, "[%d]", xLogGetTimestamp());
            len    =  len > XLOG_TIME_MSG_LEN - 1 ? XLOG_TIME_MSG_LEN - 1 : len;
            offset += len;
		}

        s_XLogMsgBuff[offset] = ':';
        s_XLogMsgBuff[offset + 1]     = ' ';

        offset += 2;

		/*-- �����־��Ϣ���� --*/
		va_list args;
		va_start (args, fmt);

		len = vsnprintf(&s_XLogMsgBuff[offset], XLOG_MSG_BUFF_SIZE - offset, fmt, args);
        len =  len > (XLOG_MSG_BUFF_SIZE - offset) - 1 ? (XLOG_MSG_BUFF_SIZE - offset) - 1 : len;
        offset += len;

		va_end(args);
		xLogPort(s_XLogMsgBuff, offset);
	}

	xLogPortUnLock();
}
