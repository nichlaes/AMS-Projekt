/* ITAMSF20
 * AMS-Projekt
 * Battle Ships
 * Date: 29/05/2020
 * Author : Tobias Apollo Lauridsen (201705755) & Nichlaes Hytting S�rensen (201706553)
 * 
 * Reference: ITAMSF20 TFTDisplay Driver
 */ 
void DisplayInit();
void DisplayOff();
void DisplayOn();
void SleepOut();
void MemoryAccessControl(unsigned char parameter);
void InterfacePixelFormat(unsigned char parameter);
void WritePixel(unsigned char Red, unsigned char Blue, unsigned char Green);
void SetColumnAddress(unsigned int Start, unsigned int End);
void SetPageAddress(unsigned int Start, unsigned int End);
void MemoryWrite();
void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width, 
                   unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue);
unsigned int readTouchXInput();
unsigned int readTouchYInput();
void delayNop(int times);
void writeSymbol(char *data, unsigned char red, unsigned char green, unsigned char blue,
unsigned int StartX, unsigned int StartY, unsigned int Width, unsigned int Height,
unsigned int sizeMultiplier);
void writeTouchData(char);
unsigned int readTouchData();


