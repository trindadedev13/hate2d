#ifndef __HATE2D_CIRCLE_H__
#define __HATE2D_CIRCLE_H__

#include <stdlib.h>

#include <SDL3/SDL.h>

struct hate2d_circle {
  SDL_FPoint* spoints;
  size_t size;
  size_t capacity;
};

struct hate2d_circle* hate2d_circle_new();

void hate2d_circle_destroy(struct hate2d_circle*);

void hate2d_circle_add(struct hate2d_circle*, float, float);

void hate2d_circle_outlined_points(struct hate2d_circle*, int, int, int);
void hate2d_circle_filled_points(struct hate2d_circle*, int, int, int);

#endif