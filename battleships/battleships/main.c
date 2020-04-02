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
	DisplayInit();
	DrawBackground();
    while (1) 
    {
		DisplayOn();
    }
}

