/*
 * protocol.h
 *
 *  Created on: Oct 29, 2023
 *      Author: trant
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_

#include "type.h"
#include "stddef.h"
#define LENGTH_RX_BUFFER 256

#define BUILD_u16(lo, hi)			( (unsigned short)((((hi) & 0x00FF) << 8) + ((lo) & 0x00FF)) )
#define BUILD_U24(b0, b1, b2)		( (unsigned int)((((b2) & 0x000000FF) << 16) + (((b1) & 0x000000FF) << 8) + ((b0) & 0x000000FF)) )
#define BUILD_U32(b0, b1, b2, b3)	( (unsigned int)((((b3) & 0x000000FF) << 24) + (((b2) & 0x000000FF) << 16) + (((b1) & 0x000000FF) << 8) + ((b0) & 0x000000FF)) )

enum LORA_MODE {
	NORMAL = 0,
	WAKE_UP = 1,
	POWER_SAVING = 2,
	SLEEP = 3,
	INIT = 3,
};

enum DEVICE_TYPE {
	LORA = 0x01,
	ZIGBEE = 0x02,
};

enum CMD {
	CONNECT = 0x00,
	READ_CONFIG = 0x01,
	CONFIG = 0x02,
	CHANGE_MODE = 0x03,
	SEND_DATA = 0x04,
};

typedef struct LoraPacket{
	u8 module;
	u8 cmdWord;
	u16 dataLength;
	u8 data[LENGTH_RX_BUFFER];
}Packet_t;



#endif /* INC_PROTOCOL_H_ */
