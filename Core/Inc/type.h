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
