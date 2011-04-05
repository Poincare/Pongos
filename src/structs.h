#include "SDL/SDL.h"
#define STRUCTS_H 1

typedef struct {
	SDL_Surface *image;
	SDL_Rect pos; /* also has width and height info */
}Paddle;

typedef struct {
	SDL_Surface *image;
	SDL_Rect pos; /* also has width and height info */
}Ball;
