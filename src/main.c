#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"

/* defines init functions, not much */
#include "init.h"

/* defines structures like Paddle and Ball */
#include "structures.h" 

/* defines simple utilities, like blitting a Paddle struct */
#include "util.h"

int main (void) {
	/* initialize variables, call utilities, functions for this held in init.c */
	startSDL();
	SDL_Surface *screen = getScreen();

	Paddle mainPaddle;
	Ball mainBall;

	mainPaddle.image = SDL_LoadBMP("../images/paddle.bmp");
	mainBall.image = SDL_LoadBMP("../images/ball.bmp");

	mainPaddle.pos.x = SCREEN_WIDTH/2;
	mainPaddle.pos.y = 0;

	mainBall.pos.x = SCREEN_WIDTH/2;
	mainBall.pos.y = SCREEN_HEIGHT/2;

	blitPaddle(&mainPaddle, screen);	
	/* call gameloop, defined in game.c */
		
	return 0;
}
