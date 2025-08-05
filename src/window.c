#include "hate2d/window.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include "hate2d/lua.h"
#include "hate2d/state.h"

struct hate2d_window* hate2d_window_create(char* title, int w, int h) {
  if (title == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Please provide a valid title for window!\n");
    return NULL;
  }

  struct hate2d_window* it = malloc(sizeof(struct hate2d_window));
  if (it == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create hate2d_window");
    return NULL;
  }

  // create sdl window
  it->raw = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
  if (it->raw == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create SDL_Window: %s\n", SDL_GetError());
    free(it);
    return NULL;
  }
  it->w = w;
  it->h = h;
  return it;
}

void hate2d_window_destroy(struct hate2d_window* self) {
  if (self == NULL)
    return;
  if (self->raw != NULL)
    SDL_DestroyWindow(self->raw);
  free(self);
}

int hate2d_lua_window_get_dimens(lua_State* L) {
  lua_pushinteger(L, gbl_state->window->w);
  lua_pushinteger(L, gbl_state->window->h);
  return 2;
}

void hate2d_lua_window_register(lua_State* L) {
  {
    hate2d_lua_ibegin(L);

    lua_pushcfunction(L, hate2d_lua_window_get_dimens);
    lua_setfield(L, -2, "get_dimensions");

    hate2d_lua_iend(L, "window");
  }
}