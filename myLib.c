

#include "myLib.h"

unsigned short *videoBuffer = (u16 *)0x6000000;

void setPixel(int row, int col, u16 color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void drawRect4(int row, int col, int width, int height, u8 index)
{
	int r,c;
	for(r=0; r<height; r++)
	{
		for(c=0; c<width; c++)
		{
			setPixel4(row+r, col+c, index);
		}
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void fillScreen4(u8 index)
{	
	volatile u16 color = (index<<8) | index;
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = DMA_ON | DMA_SOURCE_FIXED | 19200;	
}	


void setPixel4(int row, int col, u8 index)
{
	int pixel = row*240+col;
	int whichShort = pixel/2;

	if(col&1)
	{
		// Odd column must insert index into left side
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index<<8);
	}
	else
	{
		// Even column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | index;
	}
}

void drawImage4(int r, int c, int width, int height, const u16* image)
{
	for (int y = 0; y < height; y++) {
		DMA[3].src = &image[OFFSET(y, 0, width / 2)];
		DMA[3].dst = videoBuffer + OFFSET(r + y, c, 240)/2;
		DMA[3].cnt = (width/2) | DMA_ON;
	}
}

void drawPipe(int r, int c, int hole, const u16* image)
{
	drawImage4(r, c, PIPE_W, hole - r, (u16*)image);
	drawImage4(hole + HOLE_L, c, PIPE_W, 160 - hole - HOLE_L, (u16*)image);
}

void FlipPage()
{
	if(REG_DISPCTL & BUFFER1FLAG)
	{
		// We were display BUFFER1
		REG_DISPCTL = REG_DISPCTL & ~BUFFER1FLAG;
		videoBuffer = BUFFER1;
	}
	else
	{
		REG_DISPCTL = REG_DISPCTL | BUFFER1FLAG;
		videoBuffer = BUFFER0;
	}
}

