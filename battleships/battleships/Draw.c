/*
 * Draw.c
 *
 * Created: 02/04/2020 10.10.03
 *  Author: Nichl
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
	startx = startx*tileWidth;
	starty = starty*tileHeight+5;
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

void DrawHit(unsigned int startx, unsigned int starty){
	char *c = getChar('x');
	writeSymbol(c, 0,0,0, startx+5, starty, 16,16,3);
}
	
void DrawShot(unsigned int startx, unsigned int starty){
	startx = startx*tileWidth;
	starty = starty*tileHeight+2;
	if(startx == 0){startx+=2;}
	startx+=5;
	char *c = getChar('o');
	writeSymbol(c, 0,0,0, startx, starty, 16,16,3);
}