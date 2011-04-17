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
	int gameover;
	int done;
	int restart;
	
}Gameloop;

static Gameloop glp;

static SDL_Surface *gameover = NULL;

int checkExit(void *);

/* A constructor, but, without OO syntax from C++ (so we don't have the bloated crapware of C++) */
void initGameloop(Paddle *p, Ball *b, SDL_Surface *s) {
	glp.mainBall = b;
	glp.mainPaddle = p;

	glp.screen = s;
	glp.score = 0;

	glp.gameover =0;

	glp.restart = 0;

	SDL_CreateThread(checkExit, NULL);
}

void showGameover(void) {
	gameover = SDL_LoadBMP("gameover.bmp");

	SDL_Rect go_rect;
	go_rect.x = (int) (SCREEN_WIDTH-OVER_WIDTH)/2;
	go_rect.y = (int) (SCREEN_HEIGHT-OVER_HEIGHT)/2;

        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        SDL_BlitSurface(gameover, NULL, glp.screen, &go_rect);
        SDL_Flip(glp.screen);

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

void reinitImages(void) {

        glp.mainPaddle->pos.x = SCREEN_WIDTH/2 - PADDLE_WIDTH;
        glp.mainPaddle->pos.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
        SDL_BlitSurface(glp.mainPaddle->image, NULL, glp.screen, &(glp.mainPaddle->pos));

        glp.mainBall->pos.x = SCREEN_WIDTH/2;
        glp.mainBall->pos.y = SCREEN_HEIGHT/2;

        glp.mainBall->xspeed = START_SPEED;
        glp.mainBall->yspeed = START_SPEED;

        SDL_BlitSurface(glp.mainBall->image, NULL, glp.screen, &(glp.mainBall->pos));

        SDL_Flip(glp.screen);

        SDL_Delay(1000);
}

int checkExit(void *unused) {
	SDL_Event event;

	while(1) {
		SDL_PumpEvents();
		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							glp.done = 1;
							break;
						
						case SDLK_SPACE:
							glp.gameover = 0;
							glp.done = 0;
							glp.restart = 1;
							break;
					}
				case SDL_QUIT:
					glp.done = 1;
					break;
			}
		}
	}		
}

int runGameloop() {
	glp.done = 0;

	SDL_Event event;

	int mouse_pos = 0;
	terribleGotoJump:
	if(glp.restart) {
		reinitImages();
	}
	
	while(!glp.done) {
		if(glp.restart) {
			goto terribleGotoJump;
		}
		/* clear the screen */
		if(!glp.gameover) {
	                clearScreen(glp.screen);
		}

		SDL_PumpEvents();

		if(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_MOUSEMOTION:
					mouse_pos = event.motion.x;
					break;

				case SDL_QUIT:
					return glp.score;
					break;

			}
		}

		/* update the ball's coordinates */
		if(!moveBall()) {
			glp.gameover = 1;
			showGameover();
			continue;
		}
	
		if(!glp.gameover) {
			/* update the paddle's coordinates */
                	(glp.mainPaddle)->pos.x = mouse_pos;    
	
			/* blit the ball and the paddle */
			blitBall(glp.mainBall, glp.screen);
			blitPaddle(glp.mainPaddle, glp.screen);
			SDL_Flip(glp.screen);
		}

		if(glp.done) {
			return glp.score;
		}
	}
	return glp.score;	
}
