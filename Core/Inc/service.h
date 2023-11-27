/*
 * service.h
 *
 *  Created on: Nov 11, 2023
 *      Author: trant
 */

#ifndef INC_SERVICE_H_
#define INC_SERVICE_H_

#include "ring_buffer.h"
#include "main.h"


#define BUILD_u16(lo, hi)			( (unsigned short)((((hi) & 0x00FF) << 8) + ((lo) & 0x00FF)) )
#define BUILD_U24(b0, b1, b2)		( (unsigned int)((((b2) & 0x000000FF) << 16) + (((b1) & 0x000000FF) << 8) + ((b0) & 0x000000FF)) )
#define BUILD_U32(b0, b1, b2, b3)	( (unsigned int)((((b3) & 0x000000FF) << 24) + (((b2) & 0x000000FF) << 16) + (((b1) & 0x000000FF) << 8) + ((b0) & 0x000000FF)) )

#define CONFIG_ADDRESS ((uint32_t)0x0801FC00)  //flash
#define BYTE_STOP		 0x23

void FLASH_read();
void FLASH_write();
void processConnect(Packet_t packet);
void processReadConfig(Packet_t packet);
void processConfig(Packet_t packet);
Packet_t processChangeMode();
void processSendDataRF(Packet_t packet);
void processSendDataNC(Packet_t packet);
uint32_t Match_Baudrate(uint8_t baudrate);
void Uart_SetBaudrate(uint8_t baudrate);

#endif
