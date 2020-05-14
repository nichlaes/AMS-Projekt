/*
 * Game.c
 *
 * Created: 13/05/2020 11.10.13
 *  Author: Nichl
 */ 

#include "Game.h"

#define SMALLSHIPSIZE 1
#define MEDIUMSHIPSIZE 2
#define BIGSHIPSIZE 3

static enum State gameState = IdleState;
static unsigned int turnNumber = 1;

int GetGameState(){
	return gameState;
} 

void NextState(){
	if (gameState == EndState){
		gameState = IdleState;
		turnNumber++;
	} else gameState++;
}

void EndGame(){
	gameState = GameOverState;
}

int GetCurrentPlayer(){
	int p = turnNumber % 2;
	if(p == 0)
		p = 2;
	return p;
}

int TakeShot(Player *player, Point shot, Player *opponent){
	
	//Checks if shot is a new shot
	for(int i = 0; i<player->shotsFired; i++){
		if(player->Shots[i].x == shot.x && player->Shots[i].y == shot.y)
			return -1;
	}
	shot.hit = checkIFShotHitShip(opponent, shot);
	
	int shotNr = player->shotsFired; 
	player->Shots[shotNr] = shot;
	player->shotsFired += 1;
	
	return shot.hit;
}

int checkIFShotHitShip(Player *opp, const Point shot){
	for (int i = 0; i<BIGSHIPSIZE; i++)
	{
		if(i < SMALLSHIPSIZE){
			if (opp->smallShip[i].x == shot.x && opp->smallShip[i].y == shot.y){
				opp->smallShip[i].hit = 1;
				opp->shipsFieldsLeft -= 1;
				return 1;
			}	
		}
		if(i < MEDIUMSHIPSIZE){
			if (opp->mediumShip[i].x == shot.x && opp->mediumShip[i].y == shot.y){
				opp->mediumShip[i].hit = 1;
				opp->shipsFieldsLeft -= 1;
				return 1;
			}
		}
		if(i < BIGSHIPSIZE){
			if (opp->BigShip[i].x == shot.x && opp->BigShip[i].y == shot.y){
				opp->BigShip[i].hit = 1;
				opp->shipsFieldsLeft -= 1;
				return 1;
			}
		}	
	}
	return 0;
}