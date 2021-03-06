#include "myLib.h"
#include "text.h"

void drawChar(int row, int col, char ch, u16 color)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[(r*6+c)+(48*ch)] == 1)
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void drawChar4(int row, int col, char ch, u8 index)
{
	int r,c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[(r*6+c)+(48*ch)] == 1)
			{
				setPixel4(row+r, col+c, index);
			}
		}
	}
}

void drawString4(int row, int col, char *str, u8 index)
{
	while(*str)
	{
		drawChar4(row, col, *str++, index);
		col += 6;
	}
}


