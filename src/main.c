#include "SDL/SDL.h"

#include "structs.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PADDLE_HEIGHT 30
#define PADDLE_WIDTH 90

int main (void) {
	/* Variable declarations */
	Paddle mainPaddle;
	Ball mainBall;
	SDL_Surface *screen = NULL;
	
	/* Basic setup */
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, 32, SDL_SWSURFACE);

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
	
	SDL_Delay(2000);
	return 0;
}
