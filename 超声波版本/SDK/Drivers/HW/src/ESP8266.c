/**
******************************************************************************
  * 文件名程: ESP8266.c
  * 作    者: Jason_xy
  * 个人博客：https://jason-xy.cn
  * 版    本: V1.0
  * 编写日期: 2021-03-04
  * 功    能: WiFi(ESP8266)应用层驱动实现
  ******************************************************************************
  * 说明：
  * 1.需要事先配置好串口收发，并重定向printf至串口。
  * 
  * 功能：
  * 1.AP模式下的TCP_Server透传初始化。
  ******************************************************************************
  */
#include "ESP8266.h"

void ESP8266_cmd(char* cmd){    //发送AT指令
	HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
}

void ESP8266_init(void){    //8266的初始化
	ESP8266_cmd("AT+RST\r\n");  //复位模块
    HAL_Delay(300);
    ESP8266_cmd("AT+CWMODE=1\r\n"); //设置为AP模式
    HAL_Delay(300);
    ESP8266_cmd("AT+CWJAP=\"WuhuTakeOff\",\"uestc404\"\r\n");   //WiFi基本设置
    HAL_Delay(10000);
    ESP8266_cmd("AT+CIPMUX=0\r\n");   //单链路设置
    HAL_Delay(300);
    ESP8266_cmd("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n"); //TCP服务器
    HAL_Delay(300);
    ESP8266_cmd("AT+CIPMODE=1\r\n"); //透传
    HAL_Delay(300);
	ESP8266_cmd("AT+CIPSEND\r\n"); //透传开始
    HAL_Delay(300);
}

void ESP8266_cipsend(char* data){   //TCP_Server透传数据发送
	strcat(data, "\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}

void ESP8266_SendJson(uint32_t* DeviceID){   //发送json
	printf("{\"type\":\"goal\",\"sn\":\"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
}

void ESP8266_SendBeat(uint32_t* DeviceID){   //发送心跳
	char JsonToSend[100];
	char temp[40]={0};
	memset((void*)JsonToSend,0,100);
	strcat(JsonToSend,"{\"type\":\"ping\",\"sn\":\"");
	sprintf(temp,"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
	strcat(JsonToSend,temp);
	printf("%s",JsonToSend);//透传
}

void ESP8266_ReceiveData(char *data){        //接收数据
	char* point;
	char TheDate[30];
	//	printf("receive data:\n%s\n\n",data);
	if(0){
		//设备ID不正确
		
	}
	
	if((point=FindStringValue(data,"time"))!=NULL){
		int i = 0;
		while(*point!='\"')TheDate[i++] = *point++;
		TheDate[i]=0;
	}
	//printf("TheData:%s\n",TheDate);
	//RTC_SetCounter((uint32_t)strtoul(TheDate,&point,10));//字符串转unix时间戳
	//SetTimeByXML(TheDate);
	return;
}

char* FindStringValue(char* point,char* key){
	//注意冒号后面一定要有空格
	//"name": "xiaoming"
	char *aim;
	if((aim = strstr(point,key))!=NULL){
		aim = aim + strlen(key) + 4;
		return aim;
	}
	return NULL;
}

char* FindValue(char* point,char* key){
	//注意冒号后面一定要有空格
	//"name": "xiaoming"
	char *aim;
	if((aim = strstr(point,key))!=NULL){
		aim = aim + strlen(key) + 3;
		return aim;
	}
	return NULL;
}
