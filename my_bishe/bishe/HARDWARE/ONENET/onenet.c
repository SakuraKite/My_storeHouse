/**
	**********************************************************************
	**********************************************************************
	**********************************************************************
	*	�ļ����� 	onenet.c
	*	���ߣ� 		zh
	*	���ڣ� 		
	*	�汾�� 		V1.1
	*	˵���� 		��onenetƽ̨�����ݽ����ӿڲ�
	*	�޸ļ�¼��	
	*	
	**********************************************************************
	**********************************************************************
	**********************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "esp8266.h"

//Э���ļ�
#include "onenet.h"
#include "mqttkit.h"

//Ӳ������
#include "uart.h"
#include "delay.h"
//#include "dht11.h"

//C��
#include <string.h>
#include <stdio.h>

#define PROID		"7Kr0k6XBVi"  //��ƷID

#define AUTH_INFO	"version=2018-10-31&res=products%2F7Kr0k6XBVi%2Fdevices%2Fwendu&et=2551840150&method=md5&sign=oE1dJ2mkrVhxzHubQ0Znow%3D%3D"
#define DEVID		"wendu"   //�豸����

#define REPORT_TOPIC	"$sys/7Kr0k6XBVi/wendu/thing/property/post"

extern unsigned char esp8266_buf[128];

//==========================================================
//	�������ƣ�	OneNet_DevLink
//
//	�������ܣ�	��onenet��������
//
//	��ڲ�����	��
//
//	���ز�����	1-�ɹ�	0-ʧ��
//
//	˵����		��onenetƽ̨��������
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//Э���

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 1, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)  //�޸�clean_session=1
	{
		
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);	//�ϴ�ƽ̨
		
		dataPtr = ESP8266_GetIPD(250);	//�ȴ�ƽ̨��Ӧ
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:status = 0;break;
					
					case 1:break;
					case 2:break;
					case 3:break;
					case 4:break;
					case 5:break;
					
					default:break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);		//ɾ��
	}
	
	return status;
	
}

extern SMART_HOME Smart_home;
//����ONENET��Ҫ�ύJSON���ݣ��ͻ�ȡ������ʪ��ת��ΪJSON������ʽ
unsigned char MqttOnenet_Savedata(char *t_payload)
{
	
//	char json[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f}}}";  //������JSON������ʽ������OneNET����
    char json[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f},\"window\":{\"value\":%d},\"chuanglian\":{\"value\":%d},\"fan\":{\"value\":%d},\"humidity\":{\"value\":%d},\"led\":{\"value\":%d}}}";
	//char json[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f},\"window\":{\"value\":%d},\"chuanglian\":{\"value\":%d},\"fan\":{\"value\":%d},\"humidity\":{\"value\":%d},\"led\":{\"value\":%d}}}";
	//char json[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f},\"window\":{\"value\":%d},\"chuanglian\":{\"value\":%d},\"fan\":{\"value\":%d},\"humidity\":{\"value\":%d},\"led\":{\"value\":%d}}}";
	//char json1[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"humidity\":{\"value\":%d},\"led\":{\"value\":%d}}}";
	char t_json[200] = {0};
    unsigned short json_len;
	//sprintf(t_json, json, Smart_home._data.temperature_one, Smart_home._data.window_ZT_zero, Smart_home._data.chuanglian_ZT_zero, Smart_home._data.fan_ZT_zero, 1);
	sprintf(t_json, json, Smart_home._data.temperature_one, Smart_home._data.window_ZT_zero, Smart_home._data.chuanglian_ZT_zero, Smart_home._data.fan_ZT_zero, Smart_home._data.humidity_zero, Smart_home._data.led_ZT_zero);
    json_len = strlen(t_json)/sizeof(char);
  	memcpy(t_payload, t_json, json_len);
	
    return json_len;	
}

//==========================================================
//	�������ƣ�	OneNet_SendData
//
//	�������ܣ�	�ϴ����ݵ�ƽ̨
//
//	��ڲ�����	type���������ݵĸ�ʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};		//Э���
	
	char buf[256];
	short body_len = 0, i = 0;
	memset(buf, 0, sizeof(buf));    //���buff
	body_len=MqttOnenet_Savedata(buf);	
	
	if(body_len)
	{
		
		if(MQTT_PacketSaveData(REPORT_TOPIC, body_len, NULL, 5, &mqttPacket) == 0)							//���
		{//**********************************ע���������Ҫ���и����豸���ƺͲ�ƷID
			
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//�ϴ����ݵ�ƽ̨
			
			MQTT_DeleteBuffer(&mqttPacket);															//ɾ��
		}
	}
	
}

extern SMART_HOME Smart_home;

//==========================================================
//	�������ƣ�	OneNet_RevPro
//
//	�������ܣ�	ƽ̨�������ݼ��
//
//	��ڲ�����	dataPtr��ƽ̨���ص�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//Э���
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_CMD:		//�����·�
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//���topic����Ϣ��
			if(result == 0)
			{
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//����ظ����
				{	
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//�ظ�����
					MQTT_DeleteBuffer(&mqttPacket);			//ɾ��
				}
			}
		
			break;
			
		case MQTT_PKT_PUBACK:			//����Publish��Ϣ��ƽ̨�ظ���Ack
			
			break;
		
		default:
			result = -1;
			break;
	}
	
	ESP8266_Clear();									//��ջ���
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, ':');					//����'}'

	if(dataPtr != NULL && result != -1)					//����ҵ���
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//�ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//תΪ��ֵ��ʽ
		
		if(strstr((char *)req_payload, "window"))		//����"key"
		{
			Smart_home._data.window_ZT_zero = num;
					//UsartPrintf(USART_DEBUG,"key = %d\r\n", num);            //num����key:{V}��V��ֵ
		}
//		else if(strstr((char *)req_payload, "knob"))	//����"knob"
//		{
//			//UsartPrintf(USART_DEBUG,"knob = %d\r\n", num);
//		}
	}

	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
