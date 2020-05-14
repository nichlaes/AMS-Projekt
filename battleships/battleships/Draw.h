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
void ClearScreen();
//void DrawMissile();
//void DrawShip();
//void DrawText();
void DrawText(char *text, unsigned int startx, unsigned int starty, unsigned int size);
void DrawShip(int size, int startx, int starty);
void DrawShot(unsigned int startx, unsigned int starty);

#endif /* DRAW_H_ */