/*
 * Game.h
 *
 * Created: 13/05/2020 11.09.50
 *  Author: Nichl
 */ 


#ifndef GAME_H_
#define GAME_H_

enum State {IdleState, AttackState, EndState, GameOverState}; 

typedef struct Point
{
	int x,y,hit;
} Point ;

typedef struct Player
{
	char name[10];
	Point smallShip[1];
	Point mediumShip[2];
	Point BigShip[3];
	Point Shots[10];
	unsigned int shotsFired;
	unsigned int shipsFieldsLeft;
} Player ;

int TakeShot(Player *player, Point shot, Player *opponent);
int GetGameState();
void NextState();
void EndGame();
int GetCurrentPlayer();
int GetTurnNumber();
#endif /* GAME_H_ */