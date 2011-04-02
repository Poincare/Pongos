#include "util.h"

void blitPaddle(Paddle *p, SDL_Surface *screen) {
	SDL_BlitSurface(p->image, NULL, screen, &(p->pos));
}
