/**
******************************************************************************
  * 文件名程: DYP-RD.h
  * 作    者: Jason_xy
  * 个人博客：https://jason-xy.cn
  * 版    本: V1.0
  * 编写日期: 2021-03-04
  * 功    能: 超声波传感器应用层驱动实现
  ******************************************************************************
  * 说明：
  * 1.需要事先配置好串口收发。
  * 2.该模块为自动串口，采集速率10Hz。
  * 
  * 功能：
  * 1.接收并解析超声波传感器数据。
  ******************************************************************************
  */
  
#ifndef __DYPRD_H__
#define __DYPRD_H__

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "ESP8266.H"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int Distance;

void DataAnalysis(uint8_t* receive); //数据解析

#endif /* __DYPRD_H__ */
