#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SIZES_H
#include "sizes.h"
#endif


/* variable declarations */
static Paddle mainPaddle;
static Ball mainBall;

static SDL_Surface *screen = NULL;

static SDL_Surface *three = NULL;
static SDL_Surface *two = NULL;
static SDL_Surface *one = NULL;

static SDL_Surface *controls = NULL;

static int done = 0;

static SDL_Rect go_rect;

static SDL_Rect countdown_rect;


/* self-explanatory */
void setupRects(void) {
	/* center the gameover message (and, this can be used for controls) */
        go_rect.x = (int) (SCREEN_WIDTH-OVER_WIDTH)/2;
        go_rect.y = (int) (SCREEN_HEIGHT-OVER_HEIGHT)/2;

        /* center the countdown rect, which centers 3, 2, 1 */
        countdown_rect.x = (int) (SCREEN_WIDTH-OVER_WIDTH)/2;
        countdown_rect.y = (int) (SCREEN_HEIGHT-OVER_HEIGHT)/2;
}

void startSDL(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
        screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);
}

void loadImages(void) {
	controls = SDL_LoadBMP("controls.bmp");
	
	three = SDL_LoadBMP("3.bmp");
	two = SDL_LoadBMP("2.bmp");
	one = SDL_LoadBMP("1.bmp");

	mainPaddle.image = SDL_LoadBMP("paddle.bmp");
	mainBall.image = SDL_LoadBMP("ball.bmp");
}

void showControls(void) {
	SDL_BlitSurface(controls, NULL, screen, &(go_rect));
	SDL_Flip(screen);
	SDL_Delay(3000);
}

void countdown(void) {

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
}

void initiateImages(void) {

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
}

int main (void) {
	/* center messages, etc. */
	setupRects();

	/* Basic setup */
	startSDL();

	/* load images */
	loadImages();

	/* blit them onto the screen */
	showControls();

	clearScreen(screen);

	/* go 3, 2, and 1 */
	countdown();

	/* put the paddle and the ball in the initial position */
	initiateImages();

	/* call game loop here, defined in gameloop.c, handover all the filled structs */
	initGameloop(&mainPaddle, &mainBall, screen);	
	int score = runGameloop();
	
	printf("Score: %d\n", score);

	SDL_Quit();
	
	
	return 0;
}
