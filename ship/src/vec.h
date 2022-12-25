#ifndef VEC_H_
#define VEC_H_

typedef struct Vec2
{
	int x;
	int y;
} Vec2;

int drawSegLine(SDL_Renderer *, SDL_Color, Vec2 *, int);

#endif
