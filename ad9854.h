#ifndef _AD9854_H
#define _AD9854_H

#include "delay.h"

#define CS				PCout(6)
#define SCLK			PCout(7)
#define SDIO_DATA		PCout(8)
#define IO_RESET		PDout(2)
#define MRESET			PDout(6)
#define UD_CLK			PDout(7)
#define F_B_H			PEout(5)
#define OSK				PEout(6)

#define PA1				0x00
#define PA2				0x01
#define FTW1			0x02
#define FTW2			0x03
#define DFW				0x04
#define UC				0x05
#define RRC				0x06
#define CTRL			0x07
#define OSKIM			0x08
#define OSKQM			0x09
#define OSKRR			0x0A
#define QDAC			0x0B

#define Freq_mult 1876499.84473770

void AD9854_GPIO_Init(void);
void AD9854_Init(void);
void AD9854_SendOneByte(u8 data);
void AD9854_SendData(u8 _register, u8* data, u8 ByteNum);
void AD9854_SetFreq(double fre);

#endif
