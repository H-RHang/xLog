/**
 * \file            xLog_port.h
 * \brief           日志输出端口
 */

/*
 * Copyright (c) 2022 R-Hang
 *
 * Author:  R-Hang <none>
 * Version: v1.0.0
 * Date:    2022/04/01   
 */

#ifndef __XLOG_PORT_H
#define __XLOG_PORT_H

#include "stdint.h"
#include "stdio.h"

void     xLogPortLock(void);
void     xLogPortUnLock(void);
int 	 xLogPort(const char *msg, size_t len);
uint32_t xLogGetTimestamp(void);

#endif
