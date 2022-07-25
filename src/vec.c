#include <SDL2/SDL.h>
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
