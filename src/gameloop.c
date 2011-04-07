#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

#ifndef SIZES_H
#include "sizes.h"
#endif

typedef struct {
	Ball *mainBall;
	Paddle *mainPaddle;
	SDL_Surface *screen;
}Gameloop;

Gameloop glp;

void initGameloop(Paddle *p, Ball *b, SDL_Surface *s) {
	glp.mainBall = b;
	glp.mainPaddle = p;
	glp.screen = s;
}

void moveBall() {
	/* check if the ball is colliding with the horizontal walls */
	if(glp.mainBall->pos.x <= 0) {

	}
	/* check if the ball is colliding with the vertical walls */
}

void runGameloop() {
	int done = 0;
	SDL_Event event;

	int mouse_pos = 0;

	while(!done) {
		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_MOUSEMOTION:
					mouse_pos = event.motion.x;
					break;

				case SDL_QUIT:
					done = 1;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = 1;
							break;
					}	
			}
		}
		/* clear the screen */
		SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		
		/* update the paddle's coordinates */
		(glp.mainPaddle)->pos.x = mouse_pos;			

		/* update the ball's coordinates */
		moveBall();
		
		/* blit the ball and the paddle */
		blitBall(glp.mainBall, glp.screen);
		blitPaddle(glp.mainPaddle, glp.screen);
		SDL_Flip(glp.screen);
	}
	SDL_Quit();
}
