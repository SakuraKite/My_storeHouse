/**
	**********************************************************************
	**********************************************************************
	**********************************************************************
	*	文件名： 	onenet.c
	*	作者： 		zh
	*	日期： 		
	*	版本： 		V1.1
	*	说明： 		与onenet平台的数据交互接口层
	*	修改记录：	
	*	
	**********************************************************************
	**********************************************************************
	**********************************************************************
**/

//单片机头文件
#include "stm32f10x.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "mqttkit.h"

//硬件驱动
#include "uart.h"
#include "delay.h"
//#include "dht11.h"

//C库
#include <string.h>
#include <stdio.h>

#define PROID		"7Kr0k6XBVi"  //产品ID

#define AUTH_INFO	"version=2018-10-31&res=products%2F7Kr0k6XBVi%2Fdevices%2Fwendu&et=2551840150&method=md5&sign=oE1dJ2mkrVhxzHubQ0Znow%3D%3D"
#define DEVID		"wendu"   //设备名称

#define REPORT_TOPIC	"$sys/7Kr0k6XBVi/wendu/thing/property/post"

extern unsigned char esp8266_buf[128];

//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//协议包

	unsigned char *dataPtr;
	
	_Bool status = 1;
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 1, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)  //修改clean_session=1
	{
		
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);	//上传平台
		
		dataPtr = ESP8266_GetIPD(250);	//等待平台响应
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
		
		MQTT_DeleteBuffer(&mqttPacket);		//删包
	}
	
	return status;
	
}

extern SMART_HOME Smart_home;
//访问ONENET需要提交JSON数据，就获取到的温湿度转换为JSON数据形式
unsigned char MqttOnenet_Savedata(char *t_payload)
{
	
//	char json[]="{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"temp\":{\"value\":%.1f}}}";  //更换了JSON数据形式，符合OneNET需求
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
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};		//协议包
	
	char buf[256];
	short body_len = 0, i = 0;
	memset(buf, 0, sizeof(buf));    //清空buff
	body_len=MqttOnenet_Savedata(buf);	
	
	if(body_len)
	{
		
		if(MQTT_PacketSaveData(REPORT_TOPIC, body_len, NULL, 5, &mqttPacket) == 0)							//封包
		{//**********************************注意这个函数要进行更改设备名称和产品ID
			
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//上传数据到平台
			
			MQTT_DeleteBuffer(&mqttPacket);															//删包
		}
	}
	
}

extern SMART_HOME Smart_home;

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//协议包
	
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
		case MQTT_PKT_CMD:		//命令下发
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//解出topic和消息体
			if(result == 0)
			{
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//命令回复组包
				{	
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//回复命令
					MQTT_DeleteBuffer(&mqttPacket);			//删包
				}
			}
		
			break;
			
		case MQTT_PKT_PUBACK:			//发送Publish消息，平台回复的Ack
			
			break;
		
		default:
			result = -1;
			break;
	}
	
	ESP8266_Clear();									//清空缓存
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, ':');					//搜索'}'

	if(dataPtr != NULL && result != -1)					//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')		//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		
		num = atoi((const char *)numBuf);				//转为数值形式
		
		if(strstr((char *)req_payload, "window"))		//搜索"key"
		{
			Smart_home._data.window_ZT_zero = num;
					//UsartPrintf(USART_DEBUG,"key = %d\r\n", num);            //num就是key:{V}中V的值
		}
//		else if(strstr((char *)req_payload, "knob"))	//搜索"knob"
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
