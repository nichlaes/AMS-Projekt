/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting S�rensen (201706553)
 */ 

#include "Game.h"

static enum State gameState = PreGameState;
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
void PreviousState(){
	gameState--;
}

void NewGame(Player *p1, Player *p2){
	gameState = PreGameState;
	turnNumber = 1;
	
	for (int i = 0; i<p1->shotsFired; i++)
	{
		p1->Shots[i].hit = 0;
		p1->Shots[i].x = 0;
		p1->Shots[i].y = 0; 
	}
	
	for (int i = 0; i<p2->shotsFired; i++)
	{
		p2->Shots[i].hit = 0;
		p2->Shots[i].x = 0;
		p2->Shots[i].y = 0;
	}
	
	p1->shotsFired=0;
	p2->shotsFired=0;
	
	p1->shipsFieldsLeft = SMALLSHIPSIZE + MEDIUMSHIPSIZE + BIGSHIPSIZE;
	p2->shipsFieldsLeft = SMALLSHIPSIZE + MEDIUMSHIPSIZE + BIGSHIPSIZE;
		
	for (int i = 0; i<BIGSHIPSIZE; i++)
	{
		if(i < SMALLSHIPSIZE){
			p1->smallShip[i].hit = 0;
			p1->smallShip[i].x = 0;
			p1->smallShip[i].y = 0;
			p2->smallShip[i].hit = 0;
			p2->smallShip[i].x = 0;
			p2->smallShip[i].y = 0;
		}
		if(i < MEDIUMSHIPSIZE){
			p1->mediumShip[i].hit = 0;
			p1->mediumShip[i].x = 0;
			p1->mediumShip[i].y = 0;
			p2->mediumShip[i].hit = 0;
			p2->mediumShip[i].x = 0;
			p2->mediumShip[i].y = 0;
		}
		if(i < BIGSHIPSIZE){
			p1->BigShip[i].hit = 0;
			p1->BigShip[i].x = 0;
			p1->BigShip[i].y = 0;
			p2->BigShip[i].hit = 0;
			p2->BigShip[i].x = 0;
			p2->BigShip[i].y = 0;
		}
	}
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
int GetTurnNumber(){
	return turnNumber;
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
void SetShip(Player *player, int x, int y){
	if(player->smallShip[0].x==0){
		player->smallShip[0].x = x;
		player->smallShip[0].y = y;
		DrawShip(SMALLSHIPSIZE,x,y);
	}else if(player->mediumShip[0].x==0){
		if(x<5){
			if(player->smallShip[0].y==y &&(player->smallShip[0].x == x || player->smallShip[0].x == x+1))
			{return;}
			player->mediumShip[0].x=x;
			player->mediumShip[1].x=x+1;
			player->mediumShip[0].y=y;
			player->mediumShip[1].y=y;
			DrawShip(MEDIUMSHIPSIZE,x,y);
		}
	}
	else if(player->BigShip[0].x==0){
		if(x<4){
			if((player->smallShip[0].y==y &&(player->smallShip[0].x == x || player->smallShip[0].x == x+1||player->smallShip[0].x==x+2))
			||(player->mediumShip[0].y==y && (player->mediumShip[0].x == x || player->mediumShip[0].x == x+1 || player->mediumShip[0].x == x+2
			||player->mediumShip[1].x == x || player->mediumShip[1].x == x+1 || player->mediumShip[1].x == x+2
			)))
			{
				return;
			}
				
			player->BigShip[0].x = x;
			player->BigShip[1].x = x+1;
			player->BigShip[2].x = x+2;
			player->BigShip[0].y = y;
			player->BigShip[1].y = y;
			player->BigShip[2].y = y;
			DrawShip(BIGSHIPSIZE,x,y);
		}
	}
}
