/*
 * service.c
 *
 *  Created on: Nov 11, 2023
 *      Author: trant
 */

#include "service.h"
#include "main.h"
#include "protocol.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern u8 nc_rx_payload;

extern u8 cur_mode;
extern __TYPE_CONFIG MODULE_CONFIG;

void FLASH_read()
{
	MODULE_CONFIG = *(__IO __TYPE_CONFIG*)(CONFIG_ADDRESS);
}

void FLASH_write()
{
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef eraseInit;
	eraseInit.Banks = 1;
	eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
	eraseInit.NbPages = 1;
	eraseInit.PageAddress = CONFIG_ADDRESS;
	uint32_t PAGEError = 0;
	if (HAL_FLASHEx_Erase(&eraseInit, &PAGEError) != HAL_OK)
	{
	  HAL_FLASH_GetError ();
	}
	uint32_t data = BUILD_U32(MODULE_CONFIG.type, MODULE_CONFIG.id, MODULE_CONFIG.baudrate, 0x00);
	if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CONFIG_ADDRESS, data) != HAL_OK)
	{
	  HAL_FLASH_GetError ();
	}
	HAL_FLASH_Lock();
}
// service for process data
void processConnect(Packet_t packet)
{
//	HAL_UART_Transmit(&huart1, (uint8_t*)&packet, sizeof(Packet_t), 1000);
	for(int i =0; i<10; i++)
	{
		HAL_GPIO_TogglePin(GPIOC, LED_PIN_Pin);
		HAL_Delay(300);
	}
	//blink led in 3s
}

void processReadConfig(Packet_t packet)
{
	FLASH_read();
	packet.module = MODULE_CONFIG.type;
	packet.dataLength = 0x0002;
	packet.data[0] = MODULE_CONFIG.id;
	packet.data[1] = MODULE_CONFIG.baudrate;
	packet.data[2] = BYTE_STOP;
	HAL_UART_Transmit(&huart1, (uint8_t*)&packet, sizeof(Packet_t), 1000);
}
void processConfig(Packet_t packet)
{
	MODULE_CONFIG.type = packet.module;
	MODULE_CONFIG.id = packet.data[0];
	MODULE_CONFIG.baudrate = packet.data[1];
	Uart_SetBaudrate(MODULE_CONFIG.baudrate);
	FLASH_write();
	packet.dataLength = 0x02;
	HAL_UART_Transmit(&huart1, (uint8_t*)&packet, sizeof(Packet_t), 1000);
}
Packet_t processChangeMode()
{
	Packet_t packet;
	packet.module = MODULE_CONFIG.type;
	packet.cmdWord = CHANGE_MODE;
	packet.dataLength = 0x0001;
	packet.data[0] = cur_mode;
	packet.data[1] = BYTE_STOP;
	return packet;
}

void processSendDataRF(Packet_t packet)
{
	HAL_UART_Transmit(&huart1, (u8*)&packet, sizeof(Packet_t), 1000);
}

void processSendDataNC(Packet_t packet)
{
	HAL_UART_Transmit(&huart2, packet.data, packet.dataLength, 1000);
}

uint32_t Match_Baudrate(uint8_t baudrate)
{
	switch(baudrate)
	{
	case 0x00:
			return 300;
	case 0x01:
			return 1200;
	case 0x02:
			return 2400;
	case 0x03:
			return 4800;
	case 0x04:
			return 9600;
	case 0x05:
			return 19200;
	case 0x06:
			return 38400;
	case 0x07:
			return 57600;
	case 0x08:
			return 115200;
	default:
		return 0;
	}
}

void Uart_SetBaudrate(uint8_t baudrate)
{
	uint32_t Baudrate = Match_Baudrate(baudrate);
	if(Baudrate != 0 && Baudrate != huart2.Init.BaudRate)
	{
	    huart2.Init.BaudRate = Baudrate;
	    HAL_UART_Init(&huart2);
	    HAL_UART_Receive_IT(&huart2, &nc_rx_payload, 1);
	}
}

