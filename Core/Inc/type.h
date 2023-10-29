/*
 * type.h
 *
 *  Created on: Oct 4, 2023
 *      Author: trant
 */

#ifndef INC_TYPE_H_
#define INC_TYPE_H_


/********************************************************************************************************
 * @file    types.h
 *
 * @brief   This is the header file for types
 *
 * @author  Driver & Zigbee Group
 * @date    2021
 *
 *******************************************************************************************************/

#pragma once

#if 0
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef int16_t coffee_page_t;
#endif

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;


typedef long long s64;
typedef unsigned long long u64;

typedef void (*fn_ptr)(u8*);

typedef u32  u24;
typedef s32	 s24;

// Generic Status return
typedef u8 status_t;
typedef u32 UTCTime;

typedef u32 arg_t;

enum {
  ZB_FALSE = 0,
  ZB_TRUE = 1
};

typedef u8 cId_t;

/**
 *  @brief Type definition for extended address
 */
typedef u8 addrExt_t[8];
typedef u8 extPANId_t[8];

typedef addrExt_t extAddr_t;

typedef union {
	u16  shortAddr;
	addrExt_t extAddr;
}tl_zb_addr_t;

typedef union {
	u32	srcId;
	addrExt_t gpdIeeeAddr;
}gpdId_t;

/**
 *  @brief Type definition for combined short/extended device address
 */
typedef struct {
    union {
        u16         shortAddr;         //!< Short address
        addrExt_t   extAddr;           //!< Extended address
    } addr;
    u8  addrMode;                      //!< Address mode
} addr_t;

typedef struct {
	u16 id;
    u8  mode;                      //!< Address mode
} pan_id_t;

#ifdef WIN32
#ifndef FALSE
#define FALSE	0
#endif
#ifndef TRUE
#define TRUE	1
#endif

#define PACK_1
#define CODE
#define __no_init
#define GENERIC

#define NULL_OK
#define INP
#define OUTP
#define UNUSED
#define ONLY
#define READONLY
#define SHARED
#define KEEP
#endif

#ifndef NULL
#define NULL	0
#endif

#ifndef __cplusplus

#ifndef FALSE
#define FALSE 	0
#endif
#ifndef TRUE
#define TRUE 	(!FALSE)
#endif

#ifndef bool
#define bool	u8
#endif

#ifndef false
#define false	FALSE
#endif

#ifndef true
#define true	TRUE
#endif


#elif defined WIN32

#ifndef FALSE
#define FALSE	0
#endif
#ifndef TRUE
#define TRUE	1
#endif

#endif

#endif /* INC_TYPE_H_ */
