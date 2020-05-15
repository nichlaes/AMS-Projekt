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
#include "TouchHelper.h"

Player p1;
Player p2;
Point Shot;

int main(void)
{	
	p1.name[0] = 'P';
	p1.name[1] = '1';
	p1.name[2] = '\0';
	//p1.smallShip[0].x = 0; //Remember to set the hole ship!!!!!
	//p1.smallShip[0].y = 0;
	//p1.mediumShip[0].x = 0;
	//p1.mediumShip[0].y = 1;
	//p1.mediumShip[1].x = 1;
	//p1.mediumShip[1].y = 1;
	//p1.BigShip[0].x = 0;
	//p1.BigShip[0].y = 2;
	//p1.BigShip[1].x = 1;
	//p1.BigShip[1].y = 2;
	//p1.BigShip[2].x = 2;
	//p1.BigShip[2].y = 2;
	p1.shipsFieldsLeft = 1;
	
	p2.name[0] = 'P';
	p2.name[1] = '2';
	//p2.smallShip[0].x = 0;
	//p2.smallShip[0].y = 0;
	//p2.mediumShip[0].x = 0;
	//p2.mediumShip[0].y = 1;
	//p2.BigShip[0].x = 0;
	//p2.BigShip[0].y = 2;
	p2.shipsFieldsLeft = 1;
	NewGame(&p1, &p2);
	DisplayInit();
	initIRQInterrupt();
	sei(); // Global interrupt enable
	DisplayOn();
    while (1) 
    {
    }
}

//INTERRUPTS RUTINES
// Interrupt service rutine for INT2
ISR (INT4_vect)
{
	EIMSK &= ~(0b00010000);
	unsigned int x = readTouchXInput();
	unsigned int y = readTouchYInput();
	int xkoord = GetMapXKoord(x); 
	int ykoord = GetMapYKoord(y);
	Shot.x = xkoord;
	Shot.y = ykoord;
	if(xkoord!=0  && ykoord !=0){
		switch(GetGameState()){
			case PreGameState:
			handlePreGameState();
			break;
			case BeforeSetShipState:
			handleBeforeSetShipState();
			break;
			case SetShipState:
			handleSetShipState(xkoord, ykoord);
			break;
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
			handleGameOverState();
			break;
			default:
			break;
		}	
	}
	
	_delay_ms(200);
	EIMSK |= 0b00010000;
}


void initIRQInterrupt(){
	// INT4:Falling edge
	EICRB = 0b00000000;
	// Enable extern interrupt INT4
	EIMSK |= 0b00010000;
}

void handlePreGameState(){
	ClearScreen();
	Player *currentPlayer;
	if (p1.BigShip[0].x == 0){
		currentPlayer = &p1;
	} else currentPlayer = &p2;
	DrawText(currentPlayer->name, 135,50, 2);
	DrawText("please place", 80, 100, 1);
	DrawText("your battleships", 50, 150, 1);
	NextState();
}

void handleBeforeSetShipState(){
	DrawBackground();
	NextState();
}

void handleSetShipState(int x, int y){
	Player *player;
	int lastPlayer = 0;
	if(p1.BigShip[0].x==0){
		player = &p1;
	}
	else{
		player = &p2;
		lastPlayer = 1;
	}
	SetShip(player, x, y);
	
	if(player->BigShip[0].x!=0){
		if(lastPlayer){
			NextState();
		}else{
			PreviousState();
			PreviousState();
		}
	}
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
	
	//If shot is valid
	if (shotHit != -1){
		Shot.hit = shotHit;
		DrawShot(Shot);
		if(p1.shipsFieldsLeft == 0 || p2.shipsFieldsLeft == 0){
			EndGame();
		} else NextState();	
	}
}

void handleIdleState(){
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
	DrawText(name, 50,50, 2);
	DrawText("tap to continue", 50, 150, 1);
	NextState();
}
	
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
	snprintf( str1, length1 + 1+14, "%d%s", shipsLeft, " Ship-fields left" );
	
	DrawText(str1, 65, 180, 1);

	free(str);
	free(str1);
	NewGame(&p1, &p2);	
}



