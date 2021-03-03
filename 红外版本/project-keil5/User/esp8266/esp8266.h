#ifndef _ESP_8266
#define _ESP_8266
#include <stdint.h>
void ESP8266_Init(void);
void ESP8266_SendJson(uint32_t* DeviceID);
void ESP8266_SendBeat(uint32_t* DeviceID);
void ESP8266_ReceiveData(char *data);
char* FindStringValue(char* point,char* key);
char* FindValue(char* point,char* key);

#endif
