/*
 * touchDriver.c
 *
 * Created: 07-05-2020 12:07:44
 *  Author: Tobias
 */ 
/*
 * TouchDriver.c
 *
 * Created: 14-03-2019 09:16:23
 *  Author: caing
 
 
 */ 
#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include "touchDriver.h"
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

#define CLK_PORT PORTH
#define CLK_BIT 3
#define CS_PORT PORTE
#define CS_BIT 3
#define DIN_PORT PORTG
#define DIN_BIT 5
#define DOUT_PORT PORTE
#define DOUT PINE
#define DOUT_BIT 5
#define IRQ_PORT PORTE
#define IRQ_BIT 4

void TouchDriverInit() 
{
	DDRE |= 0b00001000;
	DDRH |= 0b00001000;
	DDRG |= 0b00100000;

}

void SendDIN(char input)
{ 
	char command = 0;
	
	for(int i = 7; i>-1; i--)
	{
		command = (input>>i) & 0b00000001;
		if(command == 0)
		{
			//setting D_in
			/*char temp = 0xFF;
			temp &= (~1<<DIN_BIT);
			DIN_PORT |= temp;*/
			DIN_PORT &= (~(1<<DIN_BIT));
		}
		else if(command == 1)
		{
			//setting D_in
			DIN_PORT |= (1<<DIN_BIT);
		}
		
		//set clock high
		CLK_PORT |= (1<<CLK_BIT);
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		
		//set clock low
		CLK_PORT &= (~1<<CLK_BIT);
		
	}
	
}

long GetDOUT()
{
	int data = 0;
	int temp = 0;
		for(int i = 11; i>-1; i--)
		{
			//set clock high
			CLK_PORT |= (1<<CLK_BIT);
			_NOP();
			_NOP();
			//read Dout to res
			temp = DOUT>>DOUT_BIT &0b00000001;
			data |= temp<<i;
			
			_NOP();
			
			//set clock low
			CLK_PORT &= (~1<<CLK_BIT);
			_NOP();
			_NOP();
			_NOP();
			_NOP();
		}
		return data;
	
}
	
long GetXPosition()
{
	//CS low
	CS_PORT &= (~1<<CS_BIT); 
	_NOP();
	
	SendDIN(0xD0);
	_delay_ms(2);	
	long res = GetDOUT();
	CS_PORT &= (~1<<CS_BIT);
	
	return res;
	
}

long GetYPosition()
{
	CS_PORT &= (~1<<CS_BIT);
	_NOP();
	
	SendDIN(0x90);
	_delay_ms(2);
	long res = GetDOUT();
	
	CS_PORT &= (~1<<CS_BIT);
	
	return res;
}