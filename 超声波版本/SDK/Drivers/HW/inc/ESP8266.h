/**
  ******************************************************************************
  * 文件名程: ESP8266.h
  * 作    者: Jason_xy
  * 个人博客：https://jason-xy.cn
  * 版    本: V1.0
  * 编写日期: 2021-03-04
  * 功    能: WiFi(ESP8266)应用层驱动实现
  ******************************************************************************
  * 说明：
  * 1.需要事先配置好串口收发，并重定向printf至串口。
  * 2.未进行应答检测。
  * 
  * 功能：
  * 1.AP模式下的TCP_Server透传初始化。
  ******************************************************************************
  */


#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm32f1xx_hal.h"
#include "main.h"

extern char msg[100];

void ESP8266_cmd(char* cmd);    //发送AT指令
void ESP8266_TCP_Connect(void); //连接服务器
void ESP8266_TCP_Close(void);   //断开服务器

void ESP8266_init(void);    //8266的初始化
void ESP8266_cipsend(char* data);   //TCP_Server透传数据发送

void ESP8266_SendJson(uint32_t* DeviceID);   //发送json
void ESP8266_SendBeat(uint32_t* DeviceID);   //发送心跳

char* FindStringValue(char* point,char* key);
char* FindValue(char* point,char* key);


#endif /* __ESP8266_H__ */
