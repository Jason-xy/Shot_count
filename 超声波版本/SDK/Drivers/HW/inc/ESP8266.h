/**
  ******************************************************************************
  * �ļ�����: ESP8266.h
  * ��    ��: Jason_xy
  * ���˲��ͣ�https://jason-xy.cn
  * ��    ��: V1.0
  * ��д����: 2021-03-04
  * ��    ��: WiFi(ESP8266)Ӧ�ò�����ʵ��
  ******************************************************************************
  * ˵����
  * 1.��Ҫ�������úô����շ������ض���printf�����ڡ�
  * 2.δ����Ӧ���⡣
  * 
  * ���ܣ�
  * 1.APģʽ�µ�TCP_Server͸����ʼ����
  ******************************************************************************
  */


#ifndef __ESP8266_H__
#define __ESP8266_H__

#include "stm32f1xx_hal.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void ESP8266_cmd(char* cmd);    //����ATָ��
void ESP8266_init(void);    //8266�ĳ�ʼ��
void ESP8266_cipsend(char* data);   //TCP_Server͸�����ݷ���

void ESP8266_SendJson(uint32_t* DeviceID);   //����json
void ESP8266_SendBeat(uint32_t* DeviceID);   //��������
void ESP8266_ReceiveData(char *data);        //��������
char* FindStringValue(char* point,char* key);
char* FindValue(char* point,char* key);


#endif /* __ESP8266_H__ */
