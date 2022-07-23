#ifndef BACK_H_
#define BACK_H_

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT (SCREEN_WIDTH/16*9)

int init(SDL_Window *, SDL_Surface *, Uint32 *);
int deinit(void);

#endif
