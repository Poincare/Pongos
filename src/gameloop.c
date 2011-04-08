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
	int score;
		
}Gameloop;

static Gameloop glp;

void initGameloop(Paddle *p, Ball *b, SDL_Surface *s) {
	glp.mainBall = b;
	glp.mainPaddle = p;
	glp.screen = s;
	glp.score = 0;
}

int oldmoveBall() {
	/* check if the ball is colliding with the horizontal walls */
	if(glp.mainBall->pos.y >= SCREEN_HEIGHT) {
		return 0;
	}
	if(glp.mainBall->pos.y >= glp.mainPaddle->pos.y-BALL_SIZE && glp.mainBall->pos.x >= glp.mainPaddle->pos.x && glp.mainBall->pos.x <= glp.mainPaddle->pos.x+PADDLE_WIDTH) {

		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
		glp.score++;
	} 

	if(glp.mainBall->pos.y <= BALL_SIZE) {
		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
	}	
	/* check if the ball is colliding with the vertical walls */
	if(glp.mainBall->pos.x <= 0 || glp.mainBall->pos.x >= SCREEN_WIDTH-BALL_SIZE) {
		glp.mainBall->xspeed = -(glp.mainBall->xspeed);
	}
 
	glp.mainBall->pos.x += glp.mainBall->xspeed;
	glp.mainBall->pos.y += glp.mainBall->yspeed;
	return 1;
}

int moveBall() {
	if(glp.mainBall->pos.x <= 0 || glp.mainBall->pos.x >= SCREEN_WIDTH-BALL_SIZE) {
		glp.mainBall->xspeed = -(glp.mainBall->xspeed); 
 	}

	/* hit the upper wall */	
	if(glp.mainBall->pos.y <= BALL_SIZE) {
		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
	}
	
	if(glp.mainBall->pos.y >= SCREEN_HEIGHT-PADDLE_HEIGHT-BALL_SIZE-3 && glp.mainBall->pos.x <= glp.mainPaddle->pos.x+PADDLE_WIDTH && glp.mainBall->pos.x >= glp.mainPaddle->pos.x) {
		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
	}

	else if(glp.mainBall->pos.y >= SCREEN_HEIGHT) {
		return 0;
	}
	
	glp.mainBall->pos.x += glp.mainBall->xspeed;
	glp.mainBall->pos.y += glp.mainBall->yspeed; 
}

int runGameloop() {
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
		if(!moveBall()) {
			return glp.score;
		}
		
		/* blit the ball and the paddle */
		blitBall(glp.mainBall, glp.screen);
		blitPaddle(glp.mainPaddle, glp.screen);
		SDL_Flip(glp.screen);
	}
	return glp.score;
}
