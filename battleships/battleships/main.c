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
#include <stdio.h>
#include "TFTdriver.h"
#include "Draw.h"
#include "Game.h"

Player p1;
Player p2;
Point Shot;

int main(void)
{	

	p1.name[0] = 'P';
	p1.name[1] = '1';
	p1.smallShip[0].x = 2;
	p1.smallShip[0].y = 1;
	p1.mediumShip[0].x = 3;
	p1.mediumShip[0].y = 3;
	
	p2.name[0] = 'P';
	p2.name[1] = '2';
	p2.smallShip[0].x = 2;
	p2.smallShip[0].y = 1;
	p2.mediumShip[1].x = 3;
	p2.mediumShip[1].y = 3;
	
	Shot = {3,3,0};
	int hit = TakeShot(&p1, Shot, &p2);
	//DisplayInit();
	initIRQInterrupt();
	sei(); // Global interrupt enable
	//DisplayOn();
    while (1) 
    {
		//DisplayOn();
		//_delay_ms(1000);
		EIMSK |= 0b00010000;
		switch(GetGameState()){
			case IdleState:
				break;
			case AttackState:
				break;
			case EndState:
				if(p1.shipsFieldsLeft == 0 || p1.shipsFieldsLeft == 0){
					EndGame();
				} else NextState();
				break;
			case GameOverState:
				break;
			default:
				break;
		}
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	EIMSK &= ~(0b00010000);
	//long x = GetXPosition();
	//DrawText(x,5,5,1);
	//long y = GetYPosition();
	//DrawText(y,20,20,1);
}


void initIRQInterrupt(){
	// INT4:Falling edge
	EICRB = 0b00000000;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}

void handleAttackState(){
	int shotHit;
	if(GetCurrentPlayer() == 1){
		shotHit = TakeShot(&p1, Shot, &p2);
	} else shotHit = TakeShot(&p2, Shot, &p1);
}
