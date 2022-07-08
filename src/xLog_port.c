
/**
 * \file            xLog_port.c
 * \brief           日志输出端口
 */

/*
 * Copyright (c) 2021 hrh
 *
 * Author:  hrh <none>
 * Version: v1.0.0
 * Date:    2022/04/01
 */

#include "xLog_port.h"

extern uint32_t bspGetSysTick(void);
extern int bspCom4Write(const uint8_t *buf, uint16_t writeSize);

/**
 * \brief     lock
 * \return    none
 */
void xLogPortLock(void)
{

}

/**
 * \brief     unlock
 * \return    none
 */
void xLogPortUnLock(void)
{

}

/**
 * \brief        日志输出端口
 * \param[in]    msg: 日志缓存
 * \param[in]    len: 日志长度
 * \return       0:   日志实际输出长度
 *              -1:  输出失败
 */
int
xLogPort(const char *msg, size_t len)
{
	return bspCom4Write((const uint8_t *)msg, len);
}

/**
 * \brief     获取系统运行时间
 * \return    系统时间 ms
 */
uint32_t
xLogGetTimestamp(void)
{
	return bspGetSysTick();
}
