/**
******************************************************************************
  * �ļ�����: ESP8266.c
  * ��    ��: Jason_xy
  * ���˲��ͣ�https://jason-xy.cn
  * ��    ��: V1.0
  * ��д����: 2021-03-04
  * ��    ��: WiFi(ESP8266)Ӧ�ò�����ʵ��
  ******************************************************************************
  * ˵����
  * 1.��Ҫ�������úô����շ������ض���printf�����ڡ�
  * 
  * ���ܣ�
  * 1.APģʽ�µ�TCP_Server͸����ʼ����
  ******************************************************************************
  */
#include "ESP8266.h"
char msg[100] = {0};
char espFlag[50] = {0};

void ESP8266_cmd(char* cmd){    //����ATָ��
	HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
}

void ESP8266_init(void){    //8266�ĳ�ʼ��
	HAL_Delay(5000);//�ȴ�WIF����
	//"AT+CIPSTART=\"TCP\",\"serverIP\",serverPORT\r\n"
	ESP8266_cmd("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n"); //���ӷ�����
	HAL_Delay(500);
	ESP8266_cmd("AT+CIPMODE=1\r\n"); //͸��
    HAL_Delay(500);
	ESP8266_cmd("AT+CIPSEND\r\n"); //͸����ʼ
    HAL_Delay(500);
}

void ESP8266_cipsend(char* data){   //TCP_Server���ݷ���
	HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}

void ESP8266_SendGoal(uint32_t* DeviceID){   //����
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"goal\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);;
	HAL_Delay(50);
}

void ESP8266_SendShot(uint32_t* DeviceID){    //Ͷ��
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"shot\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);;
	HAL_Delay(50);
}

void ESP8266_SendBeat(uint32_t* DeviceID){   //��������
	memset(msg, 0, sizeof(char)*100);
	sprintf(msg,"{\"type\":\"ping\",\"sn\":\"%08x%08x%08x\"}\n\r",DeviceID[0],DeviceID[1],DeviceID[2]);
	ESP8266_cipsend(msg);
	HAL_Delay(50);
}

char* FindStringValue(char* point,char* key){
	//ע��ð�ź���һ��Ҫ�пո�
	//"name": "xiaoming"
	char *aim;
	if((aim = strstr(point,key))!=NULL){
		aim = aim + strlen(key) + 4;
		return aim;
	}
	return NULL;
}

char* FindValue(char* point,char* key){
	//ע��ð�ź���һ��Ҫ�пո�
	//"name": "xiaoming"
	char *aim;
	if((aim = strstr(point,key))!=NULL){
		aim = aim + strlen(key) + 3;
		return aim;
	}
	return NULL;
}
