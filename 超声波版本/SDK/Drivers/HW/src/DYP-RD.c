/**
******************************************************************************
  * 文件名程: DYP-RD.c
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
  
#include "DYP-RD.H"
  
int Distance;	//单位mm

void DataAnalysis(uint8_t* receive){    //数据解析
	if(USART1_RX_STA == 4){
		Distance = *(receive+1)*256 + *(receive + 2);
		USART1_RX_STA = 0;
		if(Distance <= 800)
		{
      if(isGoal(DistanceGroup)){
        ESP8266_SendJson(DeviceID);
      }
      #if DEBUG
			char s[100];
			memset(s, 0, sizeof(char));
			sprintf(s, "Distance: %dmm\t", Distance);
			ESP8266_cipsend(s);
      #endif
		}
	}
}


