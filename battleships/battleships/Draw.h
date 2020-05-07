/*
 * Draw.h
 *
 * Created: 02/04/2020 10.10.18
 *  Author: Nichl
 */ 


#ifndef DRAW_H_
#define DRAW_H_
//void Draw();
void DrawBackground();
//void DrawMissile();
//void DrawShip();
//void DrawText();
void DrawText(char *text, unsigned int startx, unsigned int starty, unsigned int size);
void DrawShip(int size, unsigned int startx, unsigned int starty);

#endif /* DRAW_H_ */