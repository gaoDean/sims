#include <SDL2/SDL.h>
#include <stdlib.h>
#include "vec.h"

// segmented line
int drawSegLine(SDL_Renderer *render,
		SDL_Color color,
		Vec2 *segments,
		int numsegments)
{
	int rc = 0;
	SDL_SetRenderDrawColor(render,
			color.r,
			color.g,
			color.b,
			color.a);

	for (int i = 0; i < numsegments - 1; ++i)
	{
		rc += SDL_RenderDrawLine(render,
				segments[i].x,
				segments[i].y,
				segments[i + 1].x,
				segments[i + 1].y);
	}
	return rc;
}

/* int drawAALine(SDL_Renderer renderer, SDL_Color color, int x1, int y1, int x2, int y2) */
/* { */
/* 	int dx = x1 - x2; */
/* 	int dy = y1 - y2; */
/* 	float grad = (float)dy / (float)dx; */
/* 	if (dx == 0 || dy == 0 || fabsf(grad) == 1) { // vertical or horizontal or diagonal */
/* 		return SDL_RenderDrawLine(renderer, x1, y1, x2, y2); */
/* 	} */
/* 	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); */
/* 	SDL_RenderDrawPoint(renderer, x1, y1); */
/* 	SDL_RenderDrawPoint(renderer, x2, y2); */
/* 	for (int i = 0; i < dx; ++i) { */
/* 		int xval = x1 + i; */
/* 		float yeval = grad * xval; */
/* 		int closest = round(yeval); */
/* 		float diff = closest - yeval; */
/* 		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a * ); */
/* 		SDL_RenderDrawPoint(renderer, x2, y2); */
/* 	} */
/* } */
