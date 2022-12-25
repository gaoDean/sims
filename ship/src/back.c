#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "back.h"

int init(SDL_Window *window, SDL_Renderer *render)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE,
			&window, &render);

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
