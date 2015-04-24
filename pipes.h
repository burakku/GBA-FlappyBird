/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=20,120 -palette=10 -start=3 /home/wenqi/Downloads/CS2110/pipes /home/wenqi/Downloads/CS2110/pipes.png 
 * Time-stamp: Tuesday 11/11/2014, 19:10:16
 * 
 * Image Information
 * -----------------
 * /home/wenqi/Downloads/CS2110/pipes.png 20@120
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * A C program is like a fast dance on a newly waxed dance floor by people carrying razors. - Waldi Ravens.
 * 
 * Man is born to live and not prepared to live.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef PIPES_BITMAP_H
#define PIPES_BITMAP_H

#define PIPES_PALETTE_OFFSET  3

extern const unsigned short pipes_palette[10];
#define PIPES_PALETTE_SIZE 10

extern const unsigned short pipes[1200];
#define PIPES_SIZE 1200
#define PIPES_WIDTH 20
#define PIPES_HEIGHT 120

#endif

