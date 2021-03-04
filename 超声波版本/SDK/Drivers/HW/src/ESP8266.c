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

void ESP8266_cmd(char* cmd){    //����ATָ��
	HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 100);
}

void ESP8266_init(void){    //8266�ĳ�ʼ��
	ESP8266_cmd("AT+RST\r\n");  //��λģ��
    HAL_Delay(300);
    ESP8266_cmd("AT+CWMODE=1\r\n"); //����ΪAPģʽ
    HAL_Delay(300);
    ESP8266_cmd("AT+CWJAP=\"WuhuTakeOff\",\"uestc404\"\r\n");   //WiFi��������
    HAL_Delay(10000);
    ESP8266_cmd("AT+CIPMUX=0\r\n");   //����·����
    HAL_Delay(300);
    ESP8266_cmd("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n"); //TCP������
    HAL_Delay(300);
    ESP8266_cmd("AT+CIPMODE=1\r\n"); //͸��
    HAL_Delay(300);
	ESP8266_cmd("AT+CIPSEND\r\n"); //͸����ʼ
    HAL_Delay(300);
}

void ESP8266_cipsend(char* data){   //TCP_Server͸�����ݷ���
	strcat(data, "\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)data, strlen(data), 100);
}

void ESP8266_SendJson(uint32_t* DeviceID){   //����json
	printf("{\"type\":\"goal\",\"sn\":\"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
}

void ESP8266_SendBeat(uint32_t* DeviceID){   //��������
	char JsonToSend[100];
	char temp[40]={0};
	memset((void*)JsonToSend,0,100);
	strcat(JsonToSend,"{\"type\":\"ping\",\"sn\":\"");
	sprintf(temp,"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
	strcat(JsonToSend,temp);
	printf("%s",JsonToSend);//͸��
}

void ESP8266_ReceiveData(char *data){        //��������
	char* point;
	char TheDate[30];
	//	printf("receive data:\n%s\n\n",data);
	if(0){
		//�豸ID����ȷ
		
	}
	
	if((point=FindStringValue(data,"time"))!=NULL){
		int i = 0;
		while(*point!='\"')TheDate[i++] = *point++;
		TheDate[i]=0;
	}
	//printf("TheData:%s\n",TheDate);
	//RTC_SetCounter((uint32_t)strtoul(TheDate,&point,10));//�ַ���תunixʱ���
	//SetTimeByXML(TheDate);
	return;
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
