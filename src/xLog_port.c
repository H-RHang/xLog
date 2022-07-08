
/**
 * \file            xLog_port.c
 * \brief           ��־����˿�
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
 * \brief        ��־����˿�
 * \param[in]    msg: ��־����
 * \param[in]    len: ��־����
 * \return       0:   ��־ʵ���������
 *              -1:  ���ʧ��
 */
int
xLogPort(const char *msg, size_t len)
{
	return bspCom4Write((const uint8_t *)msg, len);
}

/**
 * \brief     ��ȡϵͳ����ʱ��
 * \return    ϵͳʱ�� ms
 */
uint32_t
xLogGetTimestamp(void)
{
	return bspGetSysTick();
}
