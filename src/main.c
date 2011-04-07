#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SIZES_H
#include "sizes.h"
#endif

int main (void) {
	/* Variable declarations */
	Paddle mainPaddle;
	Ball mainBall;
	SDL_Surface *screen = NULL;
	
	/* Basic setup */
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, 32, SDL_FULLSCREEN|SDL_DOUBLEBUF );

	/* load images, fill out structs, blit them onto the screen */
	mainPaddle.image = SDL_LoadBMP("paddle.bmp");
	mainPaddle.pos.x = SCREEN_WIDTH/2 - PADDLE_WIDTH;
	mainPaddle.pos.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
	SDL_BlitSurface(mainPaddle.image, NULL, screen, &(mainPaddle.pos));

	mainBall.image = SDL_LoadBMP("ball.bmp");
	mainBall.pos.x = SCREEN_WIDTH/2;
	mainBall.pos.y = SCREEN_HEIGHT/2;
	SDL_BlitSurface(mainBall.image, NULL, screen, &(mainBall.pos));

	SDL_Flip(screen);

	/* call game loop here, defined in gameloop.c, handover all the filled structs */
	initGameloop(&mainPaddle, &mainBall, screen);	
	runGameloop();

	return 0;
}
