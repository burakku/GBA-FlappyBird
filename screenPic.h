/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -palette=200 -start=55 /home/wenqi/Downloads/CS2110/screenPic /home/wenqi/Downloads/CS2110/bg.png /home/wenqi/Downloads/CS2110/gameover.jpg /home/wenqi/Downloads/CS2110/splash.png /home/wenqi/Downloads/CS2110/win.jpg 
 * Time-stamp: Monday 11/10/2014, 11:54:07
 * 
 * Image Information
 * -----------------
 * /home/wenqi/Downloads/CS2110/bg.png 240@160
 * /home/wenqi/Downloads/CS2110/gameover.jpg 240@160
 * /home/wenqi/Downloads/CS2110/splash.png 240@160
 * /home/wenqi/Downloads/CS2110/win.jpg 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * Why do we want intelligent terminals when there are so many stupid users?
 * 
 * You are going to have some new clothes.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef SCREENPIC_BITMAP_H
#define SCREENPIC_BITMAP_H

#define SCREENPIC_PALETTE_OFFSET  55

extern const unsigned short screenPic_palette[200];
#define SCREENPIC_PALETTE_SIZE 200

extern const unsigned short bg[19200];
#define BG_SIZE 19200
#define BG_WIDTH 240
#define BG_HEIGHT 160

extern const unsigned short gameover[19200];
#define GAMEOVER_SIZE 19200
#define GAMEOVER_WIDTH 240
#define GAMEOVER_HEIGHT 160

extern const unsigned short splash[19200];
#define SPLASH_SIZE 19200
#define SPLASH_WIDTH 240
#define SPLASH_HEIGHT 160

extern const unsigned short win[19200];
#define WIN_SIZE 19200
#define WIN_WIDTH 240
#define WIN_HEIGHT 160

#endif

