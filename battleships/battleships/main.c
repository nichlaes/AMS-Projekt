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
#include <stddef.h>
#include "Game.h"

Player p1;
Player p2;
Point Shot;

int isStateHandled = 1;

int main(void)
{	

	p1.name[0] = 'P';
	p1.name[1] = '1';
	p1.name[2] = '\0';
	p1.smallShip[0].x = 0;
	p1.smallShip[0].y = 0;
	p1.mediumShip[0].x = 0;
	p1.mediumShip[0].y = 1;
	p1.BigShip[0].x = 0;
	p1.BigShip[0].y = 2;
	Point shot1 = {1,1,1};
	p1.Shots[0] = shot1;
	Point shot2 = {3,1,0};
	p1.Shots[1] = shot2;
	p1.shotsFired = 2;
	
	p2.name[0] = 'P';
	p2.name[1] = '2';
	p2.smallShip[0].x = 2;
	p2.smallShip[0].y = 1;
	p2.mediumShip[1].x = 3;
	p2.mediumShip[1].y = 3;
	
	
	DisplayInit();
	//initIRQInterrupt();
	sei(); // Global interrupt enable
	TouchDriverInit();
	//handleGameOverState();
	//Shot = {3,3,0};
	DisplayInit();
	//initIRQInterrupt();
	sei(); // Global interrupt enable

	TouchDriverInit();
	//DrawBackground();
	//int c=1;
	//int length = snprintf( NULL, 0, "%d", c );
	//char* str = malloc( length + 1 );
	//snprintf( str, length + 1, "%d", c );
	//
	//DrawText(str, 10,10,1);
	//DrawShip(4, 5,5);
	DisplayOn();
	handleAttackState();
    while (1) 
    {
		if(isStateHandled == 0)
		{
			switch(GetGameState()){
				case IdleState:
				handleIdleState();
				break;
				case AttackState:
				handleAttackState();
				break;
				case EndState:
				handleEndState();
				break;
				case GameOverState:
				//handleGameOverState();
				break;
				default:
				break;
			}
			isStateHandled = 1;
			EIMSK |= 0b00010000;	
		}
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	EIMSK &= ~(0b00010000);
	//DrawText("t",(i++)*16,(i++)*16,1);
	//unsigned int dataX = readTouchXInput();
	//unsigned int dataY = readTouchYInput();
	//dataX = readTouchXInput();
	//dataY = readTouchYInput();
	//DisplayOff();
	_delay_ms(10);
	unsigned int y = GetYPosition();
	unsigned int x = GetXPosition();
	y= GetYPosition();
	x = GetXPosition();
	int xkoord = GetMapXKoord(x);
	int ykoord  = GetMapYKoord(y);
	if((xkoord == 0 || xkoord == 1 || xkoord == 2 || xkoord == 3)&&(ykoord == 0 || ykoord == 1 || ykoord == 2 || ykoord == 3 || ykoord == 4)){
		DrawShip(2,ykoord, xkoord);
		//int length = snprintf( NULL, 0, "%d", dataX );
		//char* str = malloc( length + 1 );
		//snprintf( str, length + 1, "%d", dataX );
		//DrawText(str,5,5,1);
		//free(str);
//
		//int lengthy = snprintf( NULL, 0, "%d", dataY );
		//char* stry = malloc( lengthy + 1 );
		//snprintf( stry, lengthy + 1, "%d", dataY );
		//DrawText(stry,30,30,1);
		//free(stry);
	}
	isStateHandled = 0;
	//EIMSK |= 0b00010000;

}


void initIRQInterrupt(){
	// INT4:Falling edge
	EICRB = 0b00000000;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}

void handleAttackState(){
	
	DrawBackground();
	if(GetCurrentPlayer() == 1){
		DrawPlayer(&p1);
	} else DrawPlayer(&p2);
	NextState();
}

void handleEndState(){
	
	int shotHit;
	if(GetCurrentPlayer() == 1){
		shotHit = TakeShot(&p1, Shot, &p2);
	} else shotHit = TakeShot(&p2, Shot, &p1);
	
	//If shot is 
	if (shotHit != -1){
		if(p1.shipsFieldsLeft == 0 || p1.shipsFieldsLeft == 0){
			EndGame();
		} else NextState();	
	}
}

void handleIdleState(){
	//ClearScreen();
	int playerId = GetCurrentPlayer();
	Player *player;
	ClearScreen();
	if(playerId==1){
		player=&p1;
	}else{
		player=&p2;
	}
	char name[16];
	snprintf(name, sizeof name, "%s%s", player->name, "s turn");
	//strcpy(name, player->name);
	//strcpy(name, "s turn");
	DrawText(name, 50,50, 2);
	DrawText("tap to continue", 50, 150, 1);
	
void handleGameOverState(){
	Player *player;
	ClearScreen();
	int playerId = GetCurrentPlayer();
	if(playerId==1){
		player = &p1;
	}else{
		player = &p2;
	}
	char name[16];
	snprintf(name, sizeof name, "%s%s", "Winner ", player->name);
	int length = snprintf( NULL, 0, "%d",  GetTurnNumber());
	char* str = malloc( length + 1 );
	snprintf( str, length + 1+11, "%s%d%s", "took ", GetTurnNumber(), " turns" );
	DrawText(name, 25, 50, 2);
	DrawText(str, 65, 120, 1);
	int shipsLeft = player->shipsFieldsLeft;
	int length1 = snprintf( NULL, 0, "%d",  shipsLeft);
	char* str1 = malloc( length1 + 1 );
	snprintf( str1, length1 + 1+14, "%d%s", shipsLeft, " nonhit fields" );
	

	DrawText(str1, 65, 180, 1);
	
	free(str);
	free(str1);
	
	}
}
