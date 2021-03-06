/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting S�rensen (201706553)
 */ 

#include "TFTdriver.h"
#include "Draw.h"
#include "fonts.h"
#include <string.h>

#define tileWidth 64
#define tileHeight 60
#define displayWidth 320
#define displayHeight 240

void DrawBackground(){
	int xTiles = displayWidth/tileWidth;
	int yTiles = displayHeight/tileHeight;
	ClearScreen();
	
	for (unsigned int i = 1; i < xTiles+1; i++)
	{
		FillRectangle(i*tileWidth-4,0,4,240,0,0,0);
	}
	for (unsigned int i = 0; i < yTiles+1; i++)
	{
		FillRectangle(0,i*tileHeight-5,320,5,0,0,0);		
	}
}

void ClearScreen(){
	FillRectangle(0,0,displayWidth, displayHeight, 0b00001111, 0b00011111, 0b00001111);
}

void DrawText(char *text, unsigned int startx, unsigned int starty, unsigned int size){
	for(int i=0; i<strlen(text); i++){
		char *cx=getChar(*(text+i));
		unsigned int start=startx+i*14*size;

		writeSymbol(cx, 0,0,0, start, starty, 16, 16, size);
	}
	char *cx=getChar(*(text+0));
}

void DrawShip(int size, int startx, int starty){
	char *c=getStartShip();
	startx = (startx-1)*tileWidth;
	starty = (starty-1)*tileHeight+5;
	if(startx == 0){startx+=5;}
	writeSymbol(c, 0,0,0, (startx + (45-32)/2), (starty +((45-32)/2)), 16, 16, 2);
	int i = 2;
	for(;i<=size;i++){
		char *c=getMiddleShip();
		writeSymbol(c, 0,0,0, (startx + (tileWidth*(i-2)) + 32), (starty +((45-32)/2)), 16, 16, 2);
		writeSymbol(c, 0,0,0, (startx + tileWidth*(i-1)), (starty +((45-32)/2)), 16, 16, 2);

	}
	char *cx=getEndShip();
	writeSymbol(cx, 0,0,0, (startx + tileWidth*(i-2) + 20), (starty +((45-32)/2)), 16, 16, 2);
}

void DrawHit(Point shot){
	unsigned int startx = (shot.x-1)*tileWidth;
	unsigned int starty = (shot.y-1)*tileHeight+2;
	if(startx == 0){startx+=2;}
	startx+=5+(32/2);
	starty+=(32/2);
	char *c = getChar('x');
	writeSymbol(c, 0,0,0, startx, starty, 16,16,1);
}
	
void DrawShot(Point shot){
	unsigned int startx = (shot.x-1)*tileWidth;
	unsigned int starty = (shot.y-1)*tileHeight+2;
	if(startx == 0){startx+=2;}
	startx+=5;
	char *c = getChar('o');
	if(shot.hit){
		writeSymbol(c, 31,0,0, startx, starty, 16,16,3);
	}
	else{
		writeSymbol(c, 0,0,0, startx, starty, 16,16,3);
	}
}

void DrawPlayer(Player *player){
	DrawShip(SMALLSHIPSIZE, player->smallShip[0].x, player->smallShip[0].y);
	DrawShip(MEDIUMSHIPSIZE, player->mediumShip[0].x, player->mediumShip[0].y);
	DrawShip(BIGSHIPSIZE, player->BigShip[0].x, player->BigShip[0].y);
	
	for (int i = 0; i<player->shotsFired; i++)
	{
		DrawShot(player->Shots[i]);
	}
	
	for (int i = 0; i<BIGSHIPSIZE; i++)
	{
		if(i < SMALLSHIPSIZE){
			if (player->smallShip[i].hit == 1){
				DrawHit(player->smallShip[i]);
			}
		}
		if(i < MEDIUMSHIPSIZE){
			if (player->mediumShip[i].hit == 1){
				DrawHit(player->mediumShip[i]);
			}
		}
		if(i < BIGSHIPSIZE){
			if (player->BigShip[i].hit == 1){
				DrawHit(player->BigShip[i]);
			}
		}
	}
		
}