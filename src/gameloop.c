#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
#endif

/* TODO this ifndef stuff is clumsy, anyone know a better way? */
#ifndef SIZES_H
#include "sizes.h"
#endif

#ifndef UTIL_H
#include "util.h"
#endif 

/* main structure, but only for this file */
/* Sort of like an Object, but, no OO syntax */
typedef struct {
	Ball *mainBall; /* TODO add support for multiple balls */
	Paddle *mainPaddle;
	SDL_Surface *screen;
	int score;
		
}Gameloop;

static Gameloop glp;

/* A constructor, but, without OO syntax from C++ (so we don't have the bloated crapware of C++) */
void initGameloop(Paddle *p, Ball *b, SDL_Surface *s) {
	glp.mainBall = b;
	glp.mainPaddle = p;
	glp.screen = s;
	glp.score = 0;
}

/* DEPRECTATED METHOD */
int oldmoveBall() {
	/* Check if the ball is colliding with the bottom of the screen,
	If so, return to the main routine to display the badly drawn
	"game over" message.
	*/
	if(glp.mainBall->pos.y >= SCREEN_HEIGHT) {
		return 0;
	}

	if(glp.mainBall->pos.y >= glp.mainPaddle->pos.y-BALL_SIZE && glp.mainBall->pos.x >= glp.mainPaddle->pos.x-BALL_SIZE && glp.mainBall->pos.x <= glp.mainPaddle->pos.x+PADDLE_WIDTH) {

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

void incrSpeed() {
	if(glp.mainBall->xspeed > 0) {
		glp.mainBall->xspeed++;
	}
	else {
		glp.mainBall->xspeed--;
	}
	if(glp.mainBall->yspeed > 0) {
		glp.mainBall->yspeed++;
	}
	else {
		glp.mainBall->yspeed--;	
	}
}

void ballHitGround() {
	SDL_Delay(1000);
}

int moveBall() {
	/* check if the ball is colliding with the two side walls*/
	if(glp.mainBall->pos.x <= 0 || glp.mainBall->pos.x >= SCREEN_WIDTH-BALL_SIZE) {
		glp.mainBall->xspeed = -(glp.mainBall->xspeed); 
		
		incrSpeed(); /* makes the ball go faster */
 	}

	/* hit the upper wall */	
	if(glp.mainBall->pos.y <= BALL_SIZE) {
		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
		incrSpeed(); /* makes the ball go faster */
	}

	
	/* check if the ball collided with the paddle */
	if(glp.mainBall->pos.y >= SCREEN_HEIGHT-PADDLE_HEIGHT-BALL_SIZE-3 && glp.mainBall->pos.x <= glp.mainPaddle->pos.x+PADDLE_WIDTH && glp.mainBall->pos.x >= glp.mainPaddle->pos.x) {
		glp.mainBall->yspeed = -(glp.mainBall->yspeed);
		glp.score++;
	}

	/* Check if the ball is colliding with the bottom of the screen,
        If so, return to the main routine to display the badly drawn
        "game over" message.
        */
	else if(glp.mainBall->pos.y >= SCREEN_HEIGHT) {
		ballHitGround();
		return 0;
	}
	
	glp.mainBall->pos.x += glp.mainBall->xspeed;
	glp.mainBall->pos.y += glp.mainBall->yspeed; 
	
	/* This loop is a hack, try not to read it */
	/* It stops the ball from rolling on your paddle */
	while(glp.mainBall->pos.y >= SCREEN_HEIGHT-PADDLE_HEIGHT-BALL_SIZE && 
	glp.mainBall->pos.x <= glp.mainPaddle->pos.x+PADDLE_WIDTH 
	&& glp.mainBall->pos.x >= glp.mainPaddle->pos.x) {
		glp.mainBall->pos.y--;
	}
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
		clearScreen(glp.screen);
	
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
