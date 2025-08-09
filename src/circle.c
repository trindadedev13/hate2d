#include "hate2d/circle.h"

#include <stdlib.h>
#include <math.h>

#include <SDL3/SDL.h>

struct hate2d_circle* hate2d_circle_new() {
  struct hate2d_circle* it = malloc(sizeof(struct hate2d_circle));
  if (!it) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create hate2d point array");
    return NULL;
  }

  it->capacity = 16;
  it->size = 0;
  it->spoints = malloc(it->capacity * sizeof(SDL_FPoint));
  if (!it->spoints) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create SDL_FPoint array");
    return NULL;
  }

  return it;
}

void hate2d_circle_delete(struct hate2d_circle* self) {
  if (!self) return;
  if (!self->spoints) {
    free(self);
    return;
  }
  self->size = 0;
  self->capacity = 0;
  free(self->spoints);
  free(self);
}

void hate2d_circle_add(struct hate2d_circle* self, float x, float y) {
  if (self->size == self->capacity) {
    self->capacity *= 2;
    SDL_FPoint* new_spoints = realloc(self->spoints, self->capacity * sizeof(SDL_FPoint));
    if (!new_spoints) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                   "Failed to reallocate memory for SDL_FPoint array");
      hate2d_circle_delete(self);
      return;
    }
    self->spoints = new_spoints;
  }
  self->spoints[self->size].x = x;
  self->spoints[self->size].y = y;
  self->size++;
}

// Thanks for
// https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379
void hate2d_circle_outlined_points(struct hate2d_circle* self, int centerX, int centerY, int radius) {
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    hate2d_circle_add(self, centerX + x, centerY + y);
    hate2d_circle_add(self, centerX + y, centerY + x);
    hate2d_circle_add(self, centerX - y, centerY + x);
    hate2d_circle_add(self, centerX - x, centerY + y);
    hate2d_circle_add(self, centerX - x, centerY - y);
    hate2d_circle_add(self, centerX - y, centerY - x);
    hate2d_circle_add(self, centerX + y, centerY - x);
    hate2d_circle_add(self, centerX + x, centerY - y);

    y += 1;
    if (err <= 0) {
      err += 2 * y + 1;
    } else {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}

void hate2d_circle_filled_points(struct hate2d_circle* self, int centerX, int centerY, int radius) {
  for (int y = -radius; y <= radius; y++) {
    int dx = (int)sqrt(radius * radius - y * y);
    for (int x = -dx; x <= dx; x++) {
      hate2d_circle_add(self, centerX + x, centerY + y);
    }
  }
}