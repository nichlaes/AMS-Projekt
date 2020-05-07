/*
 * Draw.c
 *
 * Created: 02/04/2020 10.10.03
 *  Author: Nichl
 */ 

#include "TFTdriver.h"
#include "Draw.h"
#include "fonts.h"

#define tileWidth 64
#define tileHeight 60
#define displayWidth 320
#define displayHeight 240

void DrawBackground(){
	int xTiles = displayWidth/tileWidth;
	int yTiles = displayHeight/tileHeight;
	
	for (unsigned int i = 1; i < xTiles+1; i++)
	{
		FillRectangle(i*tileWidth-4,0,4,240,0,0,0);
	}
	for (unsigned int i = 0; i < yTiles+1; i++)
	{
		FillRectangle(0,i*tileHeight-5,320,5,0,0,0);		
	}
}


void DrawText(char *text, unsigned int startx, unsigned int starty, unsigned int size){
	for(int i=0; i<strlen(text); i++){
		char *cx=getChar(*(text+i));
		unsigned int start=startx+i*14*size;

		writeSymbol(cx, 0b00001111, 0b00011111, 0b00001111, start, starty, 16, 16, size);
	}
	char *cx=getChar(*(text+0));

	//char *cx=getChar(*(text+0));
	//writeSymbol(cx, 0b00001111, 0b00011111, 0b00001111, startx, starty, 8, 8, 2);

}