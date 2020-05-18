/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting Sørensen (201706553)
 */ 

#include "Game.h"

#ifndef DRAW_H_
#define DRAW_H_
void DrawBackground();
void ClearScreen();
void DrawText();
void DrawText(char *text, unsigned int startx, unsigned int starty, unsigned int size);
void DrawShip(int size, int startx, int starty);
void DrawShot(Point shot);
void DrawPlayer(Player *player);

#endif /* DRAW_H_ */