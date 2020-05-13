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

int i = 0;

int main(void)
{	
	DisplayInit();
	initIRQInterrupt();
	sei(); // Global interrupt enable
	//DrawBackground();

	DisplayOn();
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
	DrawText("t",(i++)*16,(i++)*16,1);
	int dataX = readTouchXInput();
	int dataY = readTouchYInput();
	EIMSK |= 0b00010000;

}


void initIRQInterrupt(){
	// INT4:Falling edge
	EICRB = 0b00000010;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}
