//Wenqi Hu

#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "screenPic.h"
#include "text.h"
#include "flappy.h"
#include "pipes.h"

void start();
int game();
void winning();
void lose();

int main()
{
	int state = SPLASH;

	PALETTE[0] = BLACK;
	PALETTE[1] = MAGENTA;
	PALETTE[2] = YELLOW;

	DMA[3].src = pipes_palette;
	DMA[3].dst = PALETTE + PIPES_PALETTE_OFFSET;
	DMA[3].cnt = DMA_ON | PIPES_PALETTE_SIZE;
	
	DMA[3].src = screenPic_palette;
	DMA[3].dst = PALETTE + SCREENPIC_PALETTE_OFFSET;
	DMA[3].cnt = DMA_ON | SCREENPIC_PALETTE_SIZE;

	DMA[3].src = flappy_palette;
	DMA[3].dst = PALETTE + FLAPPY_PALETTE_OFFSET;
	DMA[3].cnt = DMA_ON | FLAPPY_PALETTE_SIZE;

	while(1)
	{
		REG_DISPCTL = MODE4 | BG2_ENABLE | BUFFER1FLAG;

		switch(state)
		{
			case SPLASH:
				start();
				state = GAME;
				break;
			case GAME:
				state = game();
				break;
			case WIN:
				winning();
				state = SPLASH;
				break;
			case LOSE:
				lose();
				state = SPLASH;
				break;
			default:
				break;
		}
	}
	return 0;
}

void start()
{
	fillScreen4(PALETTE[0]);
	FlipPage();
	fillScreen4(PALETTE[0]);


	drawImage4(0, 0, 240, 160, (u16*)splash);
	waitForVblank();
	FlipPage();
	while(!KEY_DOWN_NOW(BUTTON_START));
}

int game()
{
	int score = 0;
	int life = 5;
	int speed = 1;
	int timer = 10;
	int pipeTimer = 0;
	char scoreStr[20];
	char lifeStr[20];

	BIRD bd;
	bd.r = 70;
	bd.c = BIRD_C;

	drawImage4(0, 0, 240, 160, (u16*)bg);
	FlipPage();
	drawImage4(0, 0, 240, 160, (u16*)bg);

	PIPE pp[4];
	for(int i = 0; i < 4; i++)
	{
		pp[i].r = 10;
		pp[i].c = 219 - i*60;
		pp[i].hole = 25 + rand() / (RAND_MAX / (145 - HOLE_L - 25 + 1) + 1);
		pp[i].on = 0;

		if(i == 0)
		{
			pp[i].on = 1;
		}
	}

	int frame = 0;

	while(1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			return SPLASH;
		}

		if(KEY_DOWN_NOW(BUTTON_A))
		{
			speed = -5;		//set move speed
		}

		if(timer == 0)
		{
			bd.r += speed;		// move bird up or down
			speed++;
			timer = 3;
		}
		timer--;

		if(pipeTimer == 0)
		{
			pp[0].on = 1;
		}
		else
		{
			pipeTimer--;
		}

		if(bd.r < 10)
		{
			bd.r = 10;
		}

		if(bd.r > 149)
		{
			life--;

			if(life < 0)
			{
				return LOSE;
			}
			bd.r = 70;
			speed = 1;
			timer = 2;
		}

		//set pipe on
		for(int i = 1; i < 4; i++)
		{
			if(pp[0].c < 220 - i*60 && !pp[i].on)
			{
				pp[i].c = 219;
				pp[i].on = 1;
			}
		}

		//move pipe
		for(int i = 0; i < 4; i++)
		{
			if(pp[i].on)
			{
				pp[i].c -= 1;

				if(bd.c == (pp[i].c + PIPE_W / 2) && pp[i].on)
				{
					score++;

					if(score == 10)
					{
						return WIN;
					}
				}

				if(pp[i].c < 0)
				{
					pp[i].c = 219;
					pp[i].hole = 25 + rand() / (RAND_MAX / (145 - HOLE_L - 25 + 1) + 1);
					pipeTimer = 20;
					pp[i].on = 0;
				}

				//collision detection
				if(bd.c + 14 > pp[i].c && bd.c < pp[i].c + 20 && ((bd.r < pp[i].hole) | (bd.r + 10 > pp[i].hole + HOLE_L)) && pp[i].on)
				{
					life--;
					if(life < 0)
					{
						return LOSE;
					}
					bd.r = pp[i].hole + 2;
					speed = 1;
					timer = 2;
				}
			}
		}

		//draw background
		drawImage4(0, 0, 240, 160, (u16*)bg);

		//display pipe
		for(int i = 0; i < 4; i++)
		{
			if(pp[i].on)
			{
				drawPipe(pp[i].r, pp[i].c, pp[i].hole, (u16*)pipes);
			}
		}

		//display bird
		if(frame >= 0 && frame < 11)
		{
			drawImage4(bd.r, bd.c, BIRD_W, BIRD_H, (u16*)flappy);
			frame++;
		}
		else if(frame >= 11 && frame < 21)
		{
			drawImage4(bd.r, bd.c, BIRD_W, BIRD_H, (u16*)flappy2);
			frame++;
		}
		else if(frame >= 21 && frame < 31)
		{
			drawImage4(bd.r, bd.c, BIRD_W, BIRD_H, (u16*)flappy3);
			frame++;
		}
		else if(frame >= 31 && frame < 41)
		{
			drawImage4(bd.r, bd.c, BIRD_W, BIRD_H, (u16*)flappy4);
			frame++;
		}
		else
		{
			drawImage4(bd.r, bd.c, BIRD_W, BIRD_H, (u16*)flappy5);
			frame++;
			if(frame == 50)
			{
				frame = 0;
			}
		}

		sprintf(scoreStr, "Score: %d", score);
		drawRect4(0, 200, 30, 10, 0x79);
		drawString4(0, 170, scoreStr, PALETTE[0]);
		sprintf(lifeStr, "Life: %d", life);
		drawRect4(0, 40, 30, 10, 0x79);
		drawString4(0, 10, lifeStr, PALETTE[0]);

		waitForVblank();
		FlipPage();
	}
	return 1;
}

void winning()
{
	fillScreen4(PALETTE[0]);
	FlipPage();
	fillScreen4(PALETTE[0]);

	drawImage4(0, 0, 240, 160, (u16*)win);
	drawString4(30, 140, "You Win!", PALETTE[0]);
	drawString4(100, 40, "Press Select", PALETTE[0]);
	waitForVblank();
	FlipPage();
	while(!KEY_DOWN_NOW(BUTTON_SELECT));
}

void lose()
{
	fillScreen4(PALETTE[0]);
	FlipPage();
	fillScreen4(PALETTE[0]);

	drawImage4(0, 0, 240, 160, (u16*)gameover);
	waitForVblank();
	FlipPage();
	while(!KEY_DOWN_NOW(BUTTON_SELECT));
}