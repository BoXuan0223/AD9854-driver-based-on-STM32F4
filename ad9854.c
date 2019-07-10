#include "ad9854.h"
#include "delay.h"

void AD9854_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void AD9854_Init(void){
	u8 data[4] = {0x00, 0x06, 0x00, 0x60};
	u8 freq[6];
	u8 shape[2] = {0x0F, 0xFF};
	int i;
	long long ftw;
	ftw = (Freq_mult * 1000.0) + 0.5;
	for(i = 5; i >= 0; i--)	freq[i] = ftw >> ((5 - i) * 8);
	
	AD9854_GPIO_Init();
	
	delay_ms(10);
	UD_CLK = 0;
	CS = 0;
	MRESET = 1;
	delay_us(10);
	MRESET = 0;
	
	AD9854_SendData(CTRL, data, 4);
	delay_ms(50);
	UD_CLK = 1;
	UD_CLK = 0;	
	AD9854_SendData(FTW1, freq, 6);
	AD9854_SendData(OSKIM, shape, 2);
	UD_CLK = 1;
	UD_CLK = 0;
}

void AD9854_SendOneByte(u8 data){
	int i;
	for(i = 7; i >= 0; i--){
		SCLK = 0;
		SDIO_DATA = ((data >> i)&(0x01));
		delay_us(1);
		SCLK = 1;
		delay_us(1);
		SCLK = 0;
		delay_us(1);
	}
}

void AD9854_SendData(u8 _register, u8* data, u8 ByteNum){
	int i;
	IO_RESET = 1;
	delay_us(1);
	IO_RESET = 0;
	AD9854_SendOneByte(_register);
	for(i = 0; i < ByteNum; i++)	AD9854_SendOneByte(data[i]);
}

void AD9854_SetFreq(double fre){
	u8 freq[6];
	int i;
	long long ftw;
	ftw = (Freq_mult * fre) + 0.5;
	for(i = 5; i >= 0; i--)	freq[i] = ftw >> ((5 - i) * 8);
	AD9854_SendData(FTW1, freq, 6);
	UD_CLK = 1;
	UD_CLK = 0;	
}
