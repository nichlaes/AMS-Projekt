/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting Sørensen (201706553)
 */ 

#include "TouchHelper.h"

int GetMapXKoord(unsigned int xKoord){
	int x;
	if(xKoord > 1630){
		x=1;
	}
	else if(xKoord < 1595 && xKoord> 1270){
		x=2;
	}
	else if(xKoord < 1230 && xKoord> 930){
		x=3;
	}
	else if(xKoord < 870 && xKoord>580){
		x=4;
	}
	else if(xKoord < 520){
		x=5;
	}
	return x;
}

int GetMapYKoord(unsigned int yKoord){
	int y;
	if(yKoord > 1550){
		y=1;
	}
	else if(yKoord < 1420 && yKoord> 1080){
		y=2;
	}
	else if(yKoord < 960 && yKoord> 590){
		y=3;
	}
	else if(yKoord < 490 ){
		y=4;
	}
	return y;
}