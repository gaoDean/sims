#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "back.h"

SDL_Window *window;
SDL_Surface *screen;

int init(SDL_Window *window,
		SDL_Surface *screen,
		Uint32 *background)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	screen = SDL_GetWindowSurface(window);

	*background = SDL_MapRGB(screen->format, 113, 113, 113);
	SDL_FillRect(screen, NULL, *background);
	SDL_UpdateWindowSurface(window);

	return 0;
}

int deinit(void)
{
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
