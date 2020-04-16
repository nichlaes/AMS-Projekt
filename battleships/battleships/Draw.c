/*
 * Draw.c
 *
 * Created: 02/04/2020 10.10.03
 *  Author: Nichl
 */ 

#include "TFTdriver.h"
#include "Draw.h"

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

void drawExample(){
	//WritePixel()
}