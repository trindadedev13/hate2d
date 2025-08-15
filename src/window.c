#include "hate2d/window.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include "hate2d/ruby.h"
#include "hate2d/state.h"

struct hate2d_window* hate2d_window_create(char* title, int w, int h) {
  if (title == NULL) {
    RAISE_AND_LOG("Please provide a valid title for window!\n");
    return NULL;
  }

  struct hate2d_window* it = malloc(sizeof(struct hate2d_window));
  if (it == NULL) {
    RAISE_AND_LOG("Failed to create hate2d_window");
    return NULL;
  }

  // create sdl window
  it->raw = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
  if (it->raw == NULL) {
    RAISE_AND_LOG("Failed to create SDL_Window: %s\n", SDL_GetError());
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