#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "back.h"

int init(SDL_Window *window, SDL_Renderer *render)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE);

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_UpdateWindowSurface(window);

	return 0;
}

int deinit(SDL_Window *window, SDL_Renderer *render)
{
	if (window) {
		SDL_DestroyWindow(window);
	}
	if (render) {
		SDL_DestroyRenderer(render);
	}
	SDL_Quit();

	return 0;
}
