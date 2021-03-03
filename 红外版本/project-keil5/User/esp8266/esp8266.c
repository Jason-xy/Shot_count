#include "./esp8266/esp8266.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./beep/bsp_beep.h" 

/*ESP8266��Ҫ��ǰ��ɵ�����
*1.����ΪAPģʽ
*2.����wifi��д��flash��
*3.����TCP AT+CIPSTART="TCP","212.64.54.38",54321��д��flash��
*
*/
void ESP8266_Init(){
	


}

void ESP8266_SendJson(uint32_t* DeviceID){
//	char JsonToSend[100];
//	char temp[40]={0};
//	uint32_t unixtime;
//	unixtime=RTC_GetCounter();
//	memset((void*)JsonToSend,0,100);
	//strcat(JsonToSend,"{\"type\":\"goal\",\"sn\":\"");
	//printf("{\"type\":\"goal\",\"sn\":\"");
	//sprintf(temp,"%8x%8x%8x\"",DeviceID[0],DeviceID[1],DeviceID[2]);
	printf("{\"type\":\"goal\",\"sn\":\"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
//	strcat(JsonToSend,temp);
//	strcat(JsonToSend,"}\n");
//	printf("}\n");
	//sprintf(temp,"\"time\":\"%d\"}",unixtime);
	//strcat(JsonToSend,temp);
//	printf("%s",JsonToSend);//͸��
}

void ESP8266_SendBeat(uint32_t* DeviceID){
	char JsonToSend[100];
	char temp[40]={0};
	memset((void*)JsonToSend,0,100);
	strcat(JsonToSend,"{\"type\":\"ping\",\"sn\":\"");
	sprintf(temp,"%08x%08x%08x\"}\n",DeviceID[0],DeviceID[1],DeviceID[2]);
	strcat(JsonToSend,temp);
	//strcat(JsonToSend,"\"}\n");
	printf("%s",JsonToSend);//͸��
}

void ESP8266_ReceiveData(char *data){
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
	RTC_SetCounter((uint32_t)strtoul(TheDate,&point,10));//�ַ���תunixʱ���
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


