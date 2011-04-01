#ifndef INIT_H
#include "init.h"
#endif

void startSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
}

SDL_Surface* getScreen() {
	SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	return screen;
}
