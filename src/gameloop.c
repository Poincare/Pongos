#include "SDL/SDL.h"

#ifndef STRUCTS_H
#include "structs.h"
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

void runGameloop() {
	for(;;) {

	}
}
