# xLog

 ---

 ## 1. ���                                    

[xLog](https://gitee.com/H-RHang/xLog) ��һ��ʹ��C99ʵ�ֵ�`����`��`������`�� `C` ��־�⡣

 ![](docs/images/xLogLogo.png)

 ## 2. ����

 - �����ʽ����`��־ģ��`��`����`��`ʱ���`����Ϣ��
 - ֧�ְ�`��־ģ��`��`����`��`ʱ���`���ж�̬���ˣ�
 - ��־����֧�ֲ�ͬ`��ɫ`��ʾ��

## 3. ʹ��

### 3.1 ��������

xLog ���о�̬/��̬���������ʽ�����������Щ���ԡ�

- ��̬��ʹ�ú궨�壬�ڱ��� `xLog.h` �ļ�ʱ����
  - ֧�ֵ���־ģ��������
    ```c
    #define XLOG_MAX_MOD_NUM    16    /*-- ���֧�ֵ���־ģ������ --*/
    ```
  - ��־���أ�
    ```c
    #define XLOG_ENABL          1   /*-- ��־ʹ�� 0-ʧ�� / 1-ʹ�� --*/
    ```
  - ��־������ɫ��
    ```c
    #define XLOG_COLOR_ENABLE   1   /*-- ��־ʹ�� 0-ʧ�� / 1-ʹ�� --*/
    ```
- ��̬��ʹ��API�ӿڣ�������ʱ����
  - ��־ģ�鿪�����ã�
    ```c
    void xlogSetEn(S_XLog_Handle logHandle, E_XLog_En_Stat enStat);
    ```
  - ��־����������ã�
    ```c
    void xlogSetLv(S_XLog_Handle logHandle, E_XLog_Lv lv);
    ```
  - ��־��ʽ������á�
    ```c
    void xlogSetFmt(S_XLog_Handle logHandle, T_XLog_Fmt fmt);
    ```
### 3.2 �������

��־����������Ϊ 105(Fatal) �����Ϊ 100(Trace)��
```
��־�ȼ�:
100 [TRACE] ׷��(Trace)
101 [DEBUG] ����(Debug)
102 [INFO.] ��Ϣ(Info)
103 [WARN.] ����(Warn)
104 [ERROR] ����(Error)
105 [FATAL] ����(Fatal)
```

### 3.3 ��ֲ
xLog��־���ӡ��Ҫ�û��� `xLog_port.h` �ļ��ṩ�˿�������ܺ�ʱ����Ϣ��ȡ��
```c
/**
 * \brief        ��־����˿�
 * \param[in]    msg: ��־����
 * \param[in]    len: ��־����
 * \return       0:   ��־ʵ���������
 *              -1:  ���ʧ��
 */
int xLogPort(const char *msg, size_t len)
{
	return bspCom4Write((const uint8_t *) msg, len);
}

/**
 * \brief     ��ȡϵͳ����ʱ��
 * \return    ϵͳʱ�� ms
 */
uint32_t xLogGetTimestamp(void)
{
	return bspGetSysTick();
}
```

### 3.4 Demo
```c
#include"xLog.h"

void xLogInit(void)
{
    /*-- ��ʼ�� xLog --*/
    memset((void *) &s_XLog, 0, sizeof(S_XLog));

    /*-- xLog �汾 --*/
    xLOG("xLog Version: v1.0.0 \r\n");

    /*-- ��ӡ xLog Logo --*/
    xLOG(XLOG_LOGO);

    /*-- ���� Console ��־ģ�飬��������и�ʽ --*/
    g_XlogConsole = xLogCreate("Console", XLOG_FMT_ALL);

    /*-- ���� ModbusMaster ��־ģ�飬��������и�ʽ --*/
    g_XlogModbusMaster = xLogCreate("ModbusMaster", XLOG_FMT_ALL);

    /*-- ���� Monitor ��־ģ�飬��������и�ʽ --*/
    g_XlogMonitor = xLogCreate("Monitor", XLOG_FMT_ALL);

    /*-- ʹ�� Console ��־ģ����� --*/
    xlogSetEn(g_XlogConsole, eXLOG_ENABLE);

    /*-- ���� Console ��־ģ���������ΪTrace --*/
    xlogSetLv(g_XlogConsole, eXLOG_TRACE);

    /*-- ���� Console ��־ģ�������ʽ����Ϊ: ��־���� + ģ���ǩ + ʱ��� + ��־������ɫ --*/
    xlogSetFmt(g_XlogConsole, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    xlogSetEn(g_XlogModbusMaster, eXLOG_ENABLE);
    xlogSetLv(g_XlogModbusMaster, eXLOG_TRACE);
    xlogSetFmt(g_XlogModbusMaster, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    xlogSetEn(g_XlogMonitor, eXLOG_ENABLE);
    xlogSetLv(g_XlogMonitor, eXLOG_TRACE);
    xlogSetFmt(g_XlogMonitor, XLOG_FMT_LV | XLOG_FMT_MOD_NAME | XLOG_FMT_TIME | XLOG_FMT_COLOR);

    /*-- ��� Console ��־ģ�鼶����Ϣ --*/
    xLOG_TRACE(g_XlogConsole, "Hello xLog TRACE \r\n");
    xLOG_DEBUG(g_XlogConsole, "Hello xLog DEBUG \r\n");
    xLOG_INFO(g_XlogConsole,  "Hello xLog INFO. \r\n");
    xLOG_WARN(g_XlogConsole,  "Hello xLog WARN. \r\n");
    xLOG_ERROR(g_XlogConsole, "Hello xLog ERROR \r\n");
    xLOG_FATAL(g_XlogConsole, "Hello xLog FATAL \r\n");

    xLOG("\r\n");
}
```
- ���Ч����  
![](docs/images/xLog.png)

## 4. ���

MIT Copyright (c) rhang00gle@gmail.com