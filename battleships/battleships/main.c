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
	DisplayInit();
	DrawBackground();
	//DrawText("CC", 10,10,1);
	DrawShip(4, 5,5);
	//DrawShot(5,5);
	DisplayOn();
	// INT4:Falling edge
	EICRB = 0b00000010;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
	sei(); // Global interrupt enable
    while (1) 
    {
		DisplayOn();
		
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	EIMSK &= ~(0b00010000);
	//DisplayOff();
	long x = GetXPosition();
	DrawText('x',1,1,1);
	long y = GetYPosition();

	EIMSK |= 0b00010000;

}

