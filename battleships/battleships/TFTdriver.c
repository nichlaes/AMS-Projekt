/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  NHS
************************************************************/  
#include <avr/io.h> 
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "TFTdriver.h"
#include <string.h>

// Data port definitions:
#define DATA_PORT_HIGH PORTA
#define DATA_PORT_LOW  PORTC

// Control port definitions:
#define WR_PORT PORTG
#define WR_BIT 2
#define DC_PORT PORTD
#define DC_BIT  7  //"DC" signal is at the shield called RS
#define CS_PORT PORTG
#define CS_BIT  1
#define RST_PORT PORTG
#define RST_BIT 0
//TouchDriver definitions:
#define IRQ_PORT PORTE
#define IRQ_BIT 4
#define CLK_PORT PORTH
#define CLK_BIT 3
#define CS_TOUCH_PORT PORTE
#define CS_TOUCH_BIT 3
#define DIN_PORT PORTG
#define DIN_BIT 5
#define DOUT_PORT PORTE
#define DOUT_BIT 5

// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// ILI 9341 data sheet, page 238
void WriteCommand(unsigned int command)
{
		PORTD &= ~(1<<DC_BIT);
		PORTG &= ~(1<<CS_BIT);
		PORTG &= ~(1<<WR_BIT);
		_NOP();
		DATA_PORT_LOW = command;
		PORTG |= 1<<WR_BIT;
		PORTG |= 1<<CS_BIT;
		PORTD |= 1<<DC_BIT;
			_delay_ms(2);
}

// ILI 9341 data sheet, page 238
void WriteData(unsigned int data)
{
	PORTD |= 1<<DC_BIT;
	PORTG &= ~(1<<CS_BIT);
	PORTG &= ~(1<<WR_BIT);
	_NOP();
	DATA_PORT_HIGH = data>>8;
	DATA_PORT_LOW = data;
	PORTG |= 1<<WR_BIT;
	PORTG |= 1<<CS_BIT;
	PORTD &= ~(1<<DC_BIT);
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
	//Port setup
	DDRA = 0xFF;
	DDRB |= 0b00001111;
	DDRG |= 0b00000111;
	DDRD = ~(0b00000100); //Sets all others outputs, prev DDRD |= 0b10000000
	DDRC = 0xFF; // Port C output
	
	//Touch Ports
	DDRE |= 1<<CS_TOUCH_BIT;
	DDRE &= 0b11001111;
	DDRH |= 0b00001000;
	DDRG |= 0b00100000;
	
	PORTG |= 0b00000111;	
	PORTD |= 0b10000000;
	
	//Reset low
	PORTG &= ~(1<<RST_BIT); 
	_delay_ms(500);
	// Reset high
	PORTG |= 1<<RST_BIT; 
	_delay_ms(130); //Configure here
	//Exit Sleep Mode
	SleepOut();
	// Display on
	DisplayOn();
	// Set bit BGR (scanning direction)
	MemoryAccessControl(0b00001000);
	// 16 bits (2 bytes) per pixel
	InterfacePixelFormat(0b00000101);
}

void DisplayOff()
{
	WriteCommand(0x28);
}

void DisplayOn()
{
	WriteCommand(0x29);
}

void SleepOut()
{
	WriteCommand(0x11);
}

void MemoryAccessControl(unsigned char parameter)
{
	WriteCommand(0x36);
		
	WriteData(parameter);
}

void InterfacePixelFormat(unsigned char parameter)
{
	WriteCommand(0x3A);
	WriteData(parameter);
}

void MemoryWrite()
{
	WriteCommand(0x2C);
}

// Red 0-31, Green 0-63, Blue 0-31
void WritePixel(unsigned char Red, unsigned char Green, unsigned char Blue)
{
	unsigned int color = Red<<11;
	color |= Green<<5;
	color |= Blue<<0;
	  
	WriteData(color);
}

// Set Column Address (0-239), Start > End
void SetColumnAddress(unsigned int Start, unsigned int End)
{
	if (Start < End && End < 240)
	{
		WriteCommand(0x2A);
		WriteData(Start >> 8);
		WriteData(Start);
		WriteData(End >> 8);
		WriteData(End);
	}
	
}

// Set Page Address (0-319), Start > End
void SetPageAddress(unsigned int Start, unsigned int End)
{
	if (Start < End && End < 320)
	{
		WriteCommand(0x2B);
		WriteData(Start >> 8);
		WriteData(Start);
		WriteData(End >> 8);
		WriteData(End);
	}
}

// Fills rectangle with specified color
// (StartX,StartY) = Upper left corner. X horizontal (0-319) , Y vertical (0-239).
// Height (1-240) is vertical. Width (1-320) is horizontal.
// R-G-B = 5-6-5 bits.
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue)
{
	SetPageAddress(StartX,StartX+Width-1);
	SetColumnAddress(StartY, StartY+Height-1);
	MemoryWrite();
	for (long int i =0; i< (unsigned long int)Height*Width;i++)
	{
		WritePixel(Red,Green,Blue);
	}
	
	WriteCommand(0);
	
}

void delayNop(int times){
	for (int i =0;i<times;i++){
		_NOP();
	}
}

void writeSymbol(
char *data, unsigned char red, unsigned char green, unsigned char blue, 
unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height, 
unsigned int sizeMultiplier
){
	SetPageAddress(StartX,(StartX + Width*sizeMultiplier)-1);
	SetColumnAddress(StartY, (StartY + Height*sizeMultiplier)-1);
	MemoryWrite();
		
	
	for (int i = 0;i<16;i++){
		char cfirst=*(data+(i*2));
		char csecond=*(data+((i*2)+1));
		for(int q=0;q<sizeMultiplier;q++){
			for (int j=0;j<8;j++){
				char off= cfirst<<j;
				off&=0b10000000;
				if(off == 0)
				{
					for(int size=0;size<sizeMultiplier;size++){
						WritePixel(red, green, blue);
					}
				
				} else {
					for(int size=0;size<sizeMultiplier;size++){
						WritePixel(0, 0, 0);
					}
				}
			}
			for (int p=0;p<8;p++){
				char off= csecond<<p;
				off&=0b10000000;
				if(off == 0)
				{
					for(int size=0;size<sizeMultiplier;size++){
						WritePixel(red, green, blue);
					}
								
					} else {
					for(int size=0;size<sizeMultiplier;size++){
						WritePixel(0, 0, 0);
					}
				}
			}
		}		
	}

	WriteCommand(0);

}

void writeTouchData(unsigned int data){
	
	CLK_PORT &= ~(1<<CLK_BIT); //Sets CLK low
	CS_TOUCH_PORT &= ~(1<<CS_TOUCH_BIT); //Sets CS low
	delayNop(3); //minimum 100ns
	for (int i=0;i<8;i++){
		PORTG |= (data<<i & 0b10000000)>>2; //Sets D_IN
		CLK_PORT |= 1<<CLK_BIT; //Sets CLK high
		delayNop(6); //min 200ns
		CLK_PORT &= ~(1<<CLK_BIT); //Sets CLK low
		delayNop(6); //min 200ns
	}
}

unsigned int readTouchData(){
	unsigned int data = 0;
	for (int i=0;i<12;i++){
		data = data<<i;
		CLK_PORT |= (1<<CLK_BIT); //Sets CLK high 
		delayNop(6); // minimum 200ns
		CLK_PORT |= (1<<CLK_BIT); //Sets CLK low
		data |=  (0b00000001 & (DOUT_PORT>>DOUT_BIT));
		delayNop(5); //(minimum 200ns)
	}
	CS_TOUCH_PORT &= ~(1<<CS_TOUCH_BIT);
	return data;
}

unsigned int readTouchXInput()
{
	unsigned int getXData = 0x90;
	writeTouchData(getXData);
	_delay_ms(2); //Busy wait
	return readTouchData();
}

unsigned int readTouchYInput()
{
	unsigned int getYData = 0xD0;
	writeTouchData(getYData);
	delayNop(8);
	return readTouchData();
}

void pulseCLK(){
	CLK_PORT &= 1<<CLK_BIT; //Sets CLK high
	delayNop(1);
	CLK_PORT &= ~(1<<CLK_BIT); //Sets CLK low
}