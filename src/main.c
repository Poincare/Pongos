#include <stdio.h>
#include <stdlib.h>

#include "SDL/SDL.h"

#include "init.h"

int main (void) {
	/* initialize variables, call utilities, functions for this held in init.c */
	startSDL();
	SDL_Surface *screen = getScreen();
	/* call gameloop */
	return 0;
}
