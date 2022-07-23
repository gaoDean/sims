#include <SDL2/SDL.h>
#include "back.h"

int main(void)
{

	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Surface *screen = NULL;
	Uint32 background;

	init(window, screen, &background);

	int running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					screen = SDL_GetWindowSurface(window);
					SDL_FillRect(screen, NULL, background);
					SDL_UpdateWindowSurface(window);
				}
			}
		}
		SDL_Delay(16);
	}

	deinit();

	return 0;
}
