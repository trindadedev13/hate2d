#ifndef __HATE2D_WINDOW_H__
#define __HATE2D_WINDOW_H__

#include <SDL3/SDL.h>

// represents a window in hate2d
struct hate2d_window {
  SDL_Window* raw;  // sdl window
  int w;            // window width
  int h;            // window height
};

// initializes window
struct hate2d_window* hate2d_window_create(char*, int, int);

// cleanup window memory
void hate2d_window_destroy(struct hate2d_window*);

#endif