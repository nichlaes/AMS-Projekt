/*
 * TouchHelper.c
 *
 * Created: 15/05/2020 12.49.49
 *  Author: Nichl
 */ 

#include "TouchHelper.h"

int GetMapXKoord(unsigned int xKoord){
	int x;
	if(xKoord > 1630){
		x=0;
	}
	else if(xKoord < 1595 && xKoord> 1270){
		x=1;
	}
	else if(xKoord < 1230 && xKoord> 930){
		x=2;
	}
	else if(xKoord < 870 && xKoord>580){
		x=3;
	}
	else if(xKoord < 520){
		x=4;
	}
	return x;
}

int GetMapYKoord(unsigned int yKoord){
	int y;
	if(yKoord > 1550){
		y=0;
	}
	else if(yKoord < 1420 && yKoord> 1080){
		y=1;
	}
	else if(yKoord < 960 && yKoord> 590){
		y=2;
	}
	else if(yKoord < 490 ){
		y=3;
	}
	return y;
}