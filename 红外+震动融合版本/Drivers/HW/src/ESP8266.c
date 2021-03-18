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
char msg[100] = {0};
char espFlag[50] = {0};

void ESP8266_cmd(char* cmd){    //发送AT指令
	HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
}

void ESP8266_init(void){    //8266的初始化
	HAL_Delay(5000);//等待WIF连接
	//"AT+CIPSTART=\"TCP\",\"serverIP\",serverPORT\r\n"
	ESP8266_cmd("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n"); //连接服务器
	HAL_Delay(500);
	ESP8266_cmd("AT+CIPMODE=1\r\n"); //透传
    HAL_Delay(500);
	ESP8266_cmd("AT+CIPSEND\r\n"); //透传开始
    HAL_Delay(500);
}

void ESP8266_cipsend(char* data){   //TCP_Server数据发送
	HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}

void ESP8266_SendGoal(uint32_t* DeviceID){   //进球
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"goal\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);;
	HAL_Delay(50);
}

void ESP8266_SendShot(uint32_t* DeviceID){    //投篮
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"shot\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);;
	HAL_Delay(50);
}

void ESP8266_SendBeat(uint32_t* DeviceID){   //发送心跳
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"ping\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);
	HAL_Delay(50);
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
