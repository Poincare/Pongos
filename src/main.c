#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SIZES_H
#include "sizes.h"
#endif

#define START_SPEED 3 

int main (void) {
	/* Variable declarations */
	Paddle mainPaddle;
	Ball mainBall;

	SDL_Surface *screen = NULL;
	SDL_Surface *gameover = NULL;

	SDL_Surface *three = NULL;
	SDL_Surface *two = NULL;
	SDL_Surface *one = NULL;

	SDL_Surface *controls = NULL;

	int done = 0;
	/* center the gameover message (and, this can be used for controls) */
	SDL_Rect go_rect;
	go_rect.x = (int) (SCREEN_WIDTH-OVER_WIDTH)/2;
	go_rect.y = (int) (SCREEN_HEIGHT-OVER_HEIGHT)/2;
	
	/* center the countdown rect, which centers 3, 2, 1 */
	SDL_Rect countdown_rect;
	countdown_rect.x = (int) (SCREEN_WIDTH-OVER_WIDTH)/2;
	countdown_rect.y = (int) (SCREEN_HEIGHT-OVER_HEIGHT)/2;	

	/* Basic setup */
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, 32, SDL_DOUBLEBUF|SDL_HWSURFACE );

	/* load images, fill out structs, blit them onto the screen */
	gameover = SDL_LoadBMP("gameover.bmp");

	controls = SDL_LoadBMP("controls.bmp");
	SDL_BlitSurface(controls, NULL, screen, &(go_rect));
	SDL_Flip(screen);
	SDL_Delay(3000);

	clearScreen(screen);

	three = SDL_LoadBMP("3.bmp");
	two = SDL_LoadBMP("2.bmp");
	one = SDL_LoadBMP("1.bmp");
	
	mainPaddle.image = SDL_LoadBMP("paddle.bmp");
	mainBall.image = SDL_LoadBMP("ball.bmp");

	while(!done) {
		/* go 3, 2, and 1 */
		SDL_BlitSurface(three, NULL, screen, &(countdown_rect));
		SDL_Flip(screen);
		SDL_Delay(1000);

		clearScreen(screen);

		SDL_BlitSurface(two, NULL, screen, &(countdown_rect));
		SDL_Flip(screen);	
		SDL_Delay(1000);

		clearScreen(screen);

		SDL_BlitSurface(one, NULL, screen, &(countdown_rect));
		SDL_Flip(screen);
		SDL_Delay(1000);
	
		clearScreen(screen);

		mainPaddle.pos.x = SCREEN_WIDTH/2 - PADDLE_WIDTH;
		mainPaddle.pos.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
		SDL_BlitSurface(mainPaddle.image, NULL, screen, &(mainPaddle.pos));

		mainBall.pos.x = SCREEN_WIDTH/2;
		mainBall.pos.y = SCREEN_HEIGHT/2;

		mainBall.xspeed = START_SPEED;
		mainBall.yspeed = START_SPEED;

		SDL_BlitSurface(mainPaddle.image, NULL, screen, &(mainPaddle.pos));
		SDL_BlitSurface(mainBall.image, NULL, screen, &(mainBall.pos));

		SDL_Flip(screen);

		SDL_Delay(1000);

		/* call game loop here, defined in gameloop.c, handover all the filled structs */
		initGameloop(&mainPaddle, &mainBall, screen);	
		int score = runGameloop();
	
		SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		SDL_BlitSurface(gameover, NULL, screen, &go_rect);
		SDL_Flip(screen);
		SDL_Delay(3000);

		/* handle escape or space */
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if(keystate[SDLK_SPACE]) {
			done = 0;
		}
		else if(keystate[SDLK_ESCAPE]) {
			done = 1;
		}
		printf("Score: %d\n", score);
	}

	SDL_Quit();
	
	
	return 0;
}
