/*
 * TouchDriver.h
 *
 * Created: 14-03-2019 09:07:22
 *  Author: caing
 */ 


#ifndef TOUCHDRIVER_H_
#define TOUCHDRIVER_H_


void TouchDriverInit();
unsigned int GetXPosition();
unsigned int GetYPosition();
unsigned int GetDOUT();
int GetMapYKoord(unsigned int yKoord);
int GetMapXKoord(unsigned int xKoord);




#endif /* TOUCHDRIVER_H_ */