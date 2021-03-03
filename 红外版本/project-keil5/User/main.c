/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc ���ԣ���ʾʱ���ʽΪ: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-�Ե� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
volatile uint32_t time = 0; // ms ��ʱ���� 
volatile uint32_t Beat = 0;
volatile uint8_t SendData;
extern __IO uint32_t TimeDisplay ;
extern __IO uint32_t TimeAlarm ;
extern __IO uint16_t ADC_ConvertedValue;
uint32_t DeviceID[3]={0};

/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

//��*��ע�����
//��bsp_rtc.h�ļ��У�

//1.�����ú�USE_LCD_DISPLAY�����Ƿ�ʹ��LCD��ʾ
//2.�����ú�RTC_CLOCK_SOURCE_LSI��RTC_CLOCK_SOURCE_LSE����ʹ��LSE������LSI����

//3.STM32��LSE����Ҫ��ǳ��ϸ�ͬ���ĵ�·������������Ʒʱ����Щ��������⡣
//  ��ʵ����Ĭ��ʹ��LSI����
//  
//4.��������ϣ��RTC������Դ�������Ȼ���У���Ҫ��������ĵ�ز۰�װť�۵�أ�
//  �������Ҹĳ�ʹ���ⲿ����ģʽRTC_CLOCK_SOURCE_LSE
//  ť�۵���ͺţ�CR1220
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
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
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE|USART_IT_IDLE,DISABLE);//�ȹر��жϣ���ֹ8266�ĳ�ʼ����Ϣ���»���	
	GENERAL_TIM_Init();	
	/* ����RTC���ж����ȼ� */
	//RTC_NVIC_Config();
	//RTC_CheckAndConfig(&systmtime);
	
	//wifi�����Լ�TCP������esp8266flash�����ã��ϵ��Զ�����
	//BEEP(OFF);
	time = 0;
	while(time<4000);//��ʱ4s���ȴ�wifiģ���ʼ��
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE|USART_IT_IDLE,ENABLE);//���´��ж�
	time = 0;
	Beat = 0;
	GetDiviceId();
	LED2(ON);//��������
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
		//30*1000ms,30sһ������
		if(Beat > 30000){
			Beat = 0;
			ESP8266_SendBeat(DeviceID);
		}
	}
}

/***********************************END OF FILE*********************************/

