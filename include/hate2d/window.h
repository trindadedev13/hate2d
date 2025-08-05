#ifndef __HATE2D_WINDOW_H__
#define __HATE2D_WINDOW_H__

#include <SDL3/SDL.h>

#include "hate2d/lua.h"

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

int hate2d_lua_window_get_dimens(lua_State*);

void hate2d_lua_window_register(lua_State*);

#endif