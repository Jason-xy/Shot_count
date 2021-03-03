/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc 测试，显示时间格式为: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-霸道 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./key/bsp_key.h"
#include "./tim/bsp_GeneralTim.h"
#include "./esp8266/esp8266.h"
#include "./beep/bsp_beep.h"  
char aRxBuffer[400]={0x00};
uint8_t issleep=0;
volatile uint16_t RxCounter=0;
volatile uint8_t ReceiveState=0;
volatile uint32_t time = 0; // ms 计时变量 
volatile uint32_t Beat = 0;
volatile uint8_t SendData;
extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;
extern __IO uint16_t ADC_ConvertedValue;
uint32_t DeviceID[3]={0};

/*时间结构体，默认时间2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

//【*】注意事项：
//在bsp_rtc.h文件中：

//1.可设置宏USE_LCD_DISPLAY控制是否使用LCD显示
//2.可设置宏RTC_CLOCK_SOURCE_LSI和RTC_CLOCK_SOURCE_LSE控制使用LSE晶振还是LSI晶振

//3.STM32的LSE晶振要求非常严格，同样的电路、板子批量产品时总有些会出现问题。
//  本实验中默认使用LSI晶振。
//  
//4.！！！若希望RTC在主电源掉电后仍然运行，需要给开发板的电池槽安装钮扣电池，
//  ！！！且改成使用外部晶振模式RTC_CLOCK_SOURCE_LSE
//  钮扣电池型号：CR1220
/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
void GetDiviceId(){
	uint32_t* aim = (uint32_t*)0x1FFFF7E8;
	for(int i=0;i<3;i++){
		DeviceID[i] = *aim++;
	}
}

int main()
{			
		//struct rtc_time set_time;
	LED_GPIO_Config();
	Key_GPIO_Config();  
	USART_Config();
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE|USART_IT_IDLE,DISABLE);//先关闭中断，防止8266的初始化信息导致混乱	
	GENERAL_TIM_Init();	
	/* 配置RTC秒中断优先级 */
	//RTC_NVIC_Config();
	//RTC_CheckAndConfig(&systmtime);
	
	//wifi连接以及TCP连接在esp8266flash中配置，上电自动启动
	//BEEP(OFF);
	time = 0;
	while(time<4000);//延时4s，等待wifi模块初始化
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE|USART_IT_IDLE,ENABLE);//重新打开中断
	time = 0;
	Beat = 0;
	GetDiviceId();
	LED2(ON);//正常工作
	//printf("init\n");
	//printf("%8x%8x%8x",DeviceID[0],DeviceID[1],DeviceID[2]);
	while (1)
	{
		//printf("0");
//		if(	ReceiveState ==1 ){
//			ReceiveState = 0;
//			ESP8266_ReceiveData(aRxBuffer);
//		}
		if(!Key_Scan(GPIOA,GPIO_Pin_0)){
			ESP8266_SendJson(DeviceID);
			LED1(ON);
			time = 0;
			while(time<500);
			LED1(OFF);
		}
		//30*1000ms,30s一次心跳
		if(Beat > 30000){
			Beat = 0;
			ESP8266_SendBeat(DeviceID);
		}
	}
}

/***********************************END OF FILE*********************************/

