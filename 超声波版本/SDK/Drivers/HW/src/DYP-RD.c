/**
******************************************************************************
  * �ļ�����: DYP-RD.c
  * ��    ��: Jason_xy
  * ���˲��ͣ�https://jason-xy.cn
  * ��    ��: V1.0
  * ��д����: 2021-03-04
  * ��    ��: ������������Ӧ�ò�����ʵ��
  ******************************************************************************
  * ˵����
  * 1.��Ҫ�������úô����շ���
  * 2.��ģ��Ϊ�Զ����ڣ��ɼ�����10Hz��
  * 
  * ���ܣ�
  * 1.���ղ��������������������ݡ�
  ******************************************************************************
  */
  
#include "DYP-RD.H"
  
int Distance;	//��λmm

void DataAnalysis(uint8_t* receive){    //���ݽ���
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


