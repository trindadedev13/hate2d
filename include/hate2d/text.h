#ifndef __HATE2D_TEXT_H__
#define __HATE2D_TEXT_H__

#include <stdbool.h>
#include <stdint.h>

#include <SDL3/SDL.h>

struct hate2d_text {
  char* text;
  int x;
  int y;
  SDL_Color color;
};

// returns new text structure
// expects a text, x, y, r, g, b and a
struct hate2d_text*
hate2d_text_new(const char*, int, int, uint8_t, uint8_t, uint8_t, uint8_t);

bool hate2d_text_draw(struct hate2d_text*);

void hate2d_text_destroy(struct hate2d_text*);

#endif