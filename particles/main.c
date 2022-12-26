#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

int main(void)
{
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		fprintf(stderr, "SDL could not be initialized!\n"
		  "SDL_Error: %s\n", SDL_GetError());
		return 0;
	}

	SDL_CreateWindowAndRenderer(
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE,
			&window, &renderer);

	Vec2 *points =
	int running = 1;

	while (running) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
				break;
				case SDL_MOUSEBUTTONDOWN:
				break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						SDL_UpdateWindowSurface(window);
					}
				break;
				case SDL_MOUSEBUTTONUP:
				break;
			}
		}

		filledCircleColor(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 20, 0xFFFFFFFF);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();

	return 0;
}
