/*
 * battleships.c
 *
 * Created: 02/04/2020 09.06.15
 * Author : Nichl
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include "Draw.h"



int main(void)
{
	initPENIRQ()
	// Global interrupt enable
	sei();
	DisplayInit();
	DrawBackground();
    while (1) 
    {
		DisplayOn();
		if (PORTD = )
		{
		}
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	
}


void initPENIRQ()
{
	// INT4:Falling edge
	EICRB = 0b00000010;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}
