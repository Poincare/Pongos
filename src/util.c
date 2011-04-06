#include "SDL/SDL.h"

#ifndef UTIL_H
#include "util.h"
#endif

void blitBall(Ball *b, SDL_Surface *screen) {
	SDL_BlitSurface(b->image, NULL, screen, &(b->pos));
}

void blitPaddle(Paddle *p, SDL_Surface *screen) {
	SDL_BlitSurface(p->image, NULL, screen, &(p->pos));
}
