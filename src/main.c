#include <SDL2/SDL.h>
#include "back.h"
#include "vec.h"

int main(void)
{
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *render = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_RESIZABLE,
			&window, &render);

	Vec2 *points = malloc(sizeof(Vec2));
	Vec2 mousepos;
	int running = 1, npoints = 0, pointing = 0;

	while (running) {
		SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(render);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						SDL_UpdateWindowSurface(window);
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					points = realloc(points, ++npoints * sizeof(Vec2));
					pointing = 1;
					break;
				case SDL_MOUSEBUTTONUP:
					pointing = 0;
					if (mousepos.x < 0 || mousepos.y < 0) {
						npoints -= 1; // invalid, outside screen, redo
					}
					/* printf("(%4d, %4d)\n", mousepos.x, mousepos.y); */
					break;
			}
		}
		// in the end, the mousepos pos of points is where the mouse as released
		if (pointing) {
			SDL_GetMouseState(&mousepos.x, &mousepos.y);
			points[npoints - 1] = mousepos;
		}
		SDL_Color linecolor = {.r = 255, .b = 255, .g = 255, .a = SDL_ALPHA_OPAQUE};
		drawSegLine(render, linecolor, points, npoints);
		SDL_RenderPresent(render);
		SDL_Delay(16);
	}
	free(points);

	if (render) {
		SDL_DestroyRenderer(render);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}

	return 0;
}
