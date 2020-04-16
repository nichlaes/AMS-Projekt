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
	DDRD |= 0b10000000;
	DDRC = 0xFF; // Port C output
	
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

unsigned char readTouchInput()
{
	unsigned char controlbit = 0b10001000;
	
	PORTE &= 0b11110111;
	
	for (int i=0;i<7;i++){
	PORTG |= (controlbit & 0b00000001<<i) <<5;
	delayNop(4); //delay min 200ns
	}
	delayNop(5); //delay min 220ns wait for !busy
	
	unsigned char data;
	for (int i=0;i<7;i++){
		data |=  (0b00000001 & (PORTE>>5))<<i;
	}
	return data;
}
void delayNop(int times){
	for (int i =0;i<times;i++){
		_NOP();
	}
}