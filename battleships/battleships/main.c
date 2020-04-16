/*
 * battleships.c
 *
 * Created: 02/04/2020 09.06.15
 * Author : Nichl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include "Draw.h"



int main(void)
{
	unsigned int data[] = {0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x60, 0x00, 0x00, 0x06, 0x30, 0x00, 0x00, 0x0c, 0x18, 0x00, 0x00, 0x18, 0x0c, 0x00, 0x00, 0x30, 0x06, 0x00, 0x00, 0x60, 0x03, 0x00, 0x00, 0xc0, 0x01, 0x80, 0x01, 0x80, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x06, 0x60, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x60, 0x06, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x00, 0xc0, 0x06, 0x00, 0x00, 0x60, 0x0c, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00, 0x18, 0x30, 0x00, 0x00, 0x0c, 0x60, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x03
	};
	writeSymbol(data, 32*32);
	
	initPENIRQ();
	// Global interrupt enable
	sei();
	DisplayInit();
	DrawBackground();
    while (1) 
    {
		DisplayOn();
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	unsigned char data = readTouchInput();

	for (int i=0; i<7; i++)
	{
		_delay_ms(2000);
		if ((data>>i & 0b00000001) == 1)
		{
			DisplayOn();
		} else DisplayOff();
	}

}


void initPENIRQ()
{
	// INT4:Falling edge
	EICRB = 0b00000010;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}
