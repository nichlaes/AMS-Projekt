/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting S�rensen (201706553)
 */ 


#ifndef GAME_H_
#define GAME_H_

#define SMALLSHIPSIZE 1
#define MEDIUMSHIPSIZE 2
#define BIGSHIPSIZE 3

enum State {PreGameState, BeforeSetShipState, SetShipState, IdleState, AttackState, EndState, GameOverState}; 

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
	Point Shots[20];
	unsigned int shotsFired;
	unsigned int shipsFieldsLeft;
} Player ;

int TakeShot(Player *player, Point shot, Player *opponent);
int GetGameState();
void NextState();
void PreviousState();
void EndGame();
int GetCurrentPlayer();
int GetTurnNumber();
void NewGame(Player *p1, Player *p2);
void SetShip(Player *player, int x, int y);
#endif /* GAME_H_ */