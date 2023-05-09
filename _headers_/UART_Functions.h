/*0.Documentation Section
Author: Ahmed Haitham Ismael El-Ebidy
Date: 29,April,2023
Description: functions to provide an interface with UART protocol services in the TM4C123GH6PM microcontroller
/*


#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdio.h>

#define elif else if
/*================================================================
										UART 0 Function Prototypes
================================================================*/
void UART0_Init(unsigned long frequency, unsigned long BaudRate);
unsigned char UART0_InChar(void);
void UART0_OutChar(char UART_CHAR);
void UART0_InString(char *ptr, int size);
void UART0_CRLF(void);


/*================================================================
										UART 1 Function Prototypes
================================================================*/
//void UART1_Init(unsigned long frequency, unsigned long BaudRate);
void UART1_Init(void);
unsigned char UART1_InChar(void);
void UART1_OutChar(char UART_CHAR);
void UART1_InString(char *ptr, int size);
void UART1_CRLF(void);


/*=====================================
				//UART 0 FUNCTIONS//
=======================================*/
void UART0_Init(unsigned long frequency, unsigned long BaudRate)
{
	unsigned long BRD = ((frequency<<2)+BaudRate)/BaudRate;
	//Enabling UART0 Clock
	SYSCTL_RCGCUART_R |= 0x01;
	
	//Enabling PORT A's clock and waiting for it
	SYSCTL_RCGCGPIO_R |= 0x01;
	while(SYSCTL_PRGPIO_R == 0);
	
	//Disable UART0 
	UART0_CTL_R &= ~(0x01);
	
	//Setting the baudrate divisor
	UART0_IBRD_R = (BRD>>6);
	UART0_FBRD_R = BRD&0x2F;
	
	//Setting Preferred Line Controls
	UART0_LCRH_R = 0x0070;
	
	//Enabling Tx0 and Rx0 and UART0
	UART0_CTL_R |= 0x301;
	
//_________________________________
	
	//Initializing Port A pins A0 and A1
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_AMSEL_R &= ~(0x03);
	
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;
}

unsigned char UART0_InChar(void)
{
	while(UART0_FR_R& 0x10);		//while UART0 Recieving FIFO empty, Do nothing
	return UART0_DR_R;					//once you get data, return it
}

void UART0_OutChar(char UART_CHAR)
{
	while(UART0_FR_R&0x20);		//while UART0 Transmission FIFO full, do nothing
	UART0_DR_R = UART_CHAR;		//once its not FULL, output the given character
}

void UART0_InString(char *string, int size)
{
	int current;		//current index in the given string
	char temp;
	
	if(size<=0)
	{
		return;
	}
	
	for(current = 0; current<size ;current++)
	{
		temp = UART0_InChar();
		if(temp == '\r')
		{
			UART0_CRLF();
			string[current] = 0;
			return;
		}
		
		UART0_OutChar(temp);
		if(temp == '\b')
		{
			if(current == 0)
			{
				string[current] = 0;
				current--;
			}
			else
			{
				current--;
				string[current] = 0;
				current--;
			}
			continue;
		}
		string[current] = temp;
	}
	string[size] = 0;
	UART0_CRLF();
	
}

void UART0_CRLF(void)
{
		UART0_OutChar('\r');
		UART0_OutChar('\n');
}


/*=====================================
				//UART 1 FUNCTIONS//
=======================================*/

//void UART1_Init(unsigned long frequency, unsigned long BaudRate)
///WARNING: MODIFIED USE FOR GPS MODULE FUNCTIONALITY - DOESN'T WORK WITH SERIAL MONITORS
void UART1_Init(void)
{
	//unsigned long BRD = ((frequency<<2)+BaudRate)/BaudRate;
	unsigned long BRD = ((16000000<<2)+9600)/9600;
	//Enabling UART1 Clock
	SYSCTL_RCGCUART_R |= 0x02;
	
	//Enabling PORT B's clock and waiting for it
	SYSCTL_RCGCGPIO_R |= 0x02;
	while(SYSCTL_PRGPIO_R == 0);
	
	//Disable UART1
	UART1_CTL_R &= ~(0x01);
	
	//Setting the baudrate divisor
	UART1_IBRD_R = (BRD>>6);
	UART1_FBRD_R = BRD&0x2F;
	
	//Setting Preferred Line Controls
	UART1_LCRH_R = 0x0070;
	
	//Enabling Tx0 and Rx0 and UART0
	UART1_CTL_R |= 0x301;
	
//_________________________________
	
	//Initializing Port B pins B0 and B1
	GPIO_PORTB_AFSEL_R |= 0x03;
	GPIO_PORTB_AMSEL_R &= ~(0x03);
	
	GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xFFFFFF00) + 0x00000011;
	GPIO_PORTB_DEN_R |= 0x03;
}

unsigned char UART1_InChar(void)
{
	while(UART1_FR_R& 0x10);		//while UART1 Recieving FIFO empty, Do nothing
	return UART1_DR_R;					//once you get data, return it
}

void UART1_OutChar(char UART_CHAR)
{
	while(UART1_FR_R&0x20);		//while UART1 Transmission FIFO full, do nothing
	UART1_DR_R = UART_CHAR;		//once its not FULL, output the given character
}

void UART1_InString(char *string, int size)
{
	int current;		//current index in the given string
	char temp;
	
	if(size<=0)
	{
		return;
	}
	
	for(current = 0; current<size ;current++)
	{
		temp = UART1_InChar();
		if(temp == '\r')
		{
			continue;
		}
		if(temp == '\n')
		{
			string[current]=0;
			return;
		}
		
		//UART1_OutChar(temp);
		if(temp == '\b')
		{
			if(current == 0)
			{
				string[current] = 0;
				current--;
			}
			else
			{
				current--;
				string[current] = 0;
				current--;
			}
			continue;
		}
		string[current] = temp;
	}
	string[size] = 0;
	//UART1_CRLF();
	
}

void UART1_CRLF(void)
{
		//UART1_OutChar('\r');
		//UART1_OutChar('\n');
}

