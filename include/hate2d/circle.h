#ifndef __HATE2D_CIRCLE_H__
#define __HATE2D_CIRCLE_H__

#include <stdlib.h>

#include <SDL3/SDL.h>

struct hate2d_point_arr {
  SDL_FPoint* spoints;
  size_t size;
  size_t capacity;
};

struct hate2d_point_arr* hate2d_point_arr_new();

void hate2d_point_arr_delete(struct hate2d_point_arr*);

void hate2d_point_arr_add(struct hate2d_point_arr*, float, float);

void hate2d_point_arr_circle_points(struct hate2d_point_arr*, int, int, int);

void hate2d_point_arr_filled_circle_points(struct hate2d_point_arr*, int, int, int);

#endif