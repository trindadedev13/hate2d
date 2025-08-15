#include "hate2d/state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <ruby.h>

#include "hate2d/ruby.h"

struct hate2d_state* gbl_state = NULL;

bool hate2d_state_initgbl(char* project_root) {
  // initialize sdl video
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    RAISE_AND_LOG("Failed to initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // initialize sdl ttf
  if (!TTF_Init()) {
    RAISE_AND_LOG("Failed to initialize SDL TTF: %s\n", SDL_GetError());
    return false;
  }

  gbl_state = malloc(sizeof(struct hate2d_state));
  if (!gbl_state) {
    RAISE_AND_LOG("Failed to allocate memory for global state: %s\n",
                  SDL_GetError());
    return false;
  }

  // calculate width and height based on display
  const SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(display_id);

  // create window
  gbl_state->window = hate2d_window_create("hate2d", mode->w, mode->h);
  if (gbl_state->window == NULL) {
    RAISE_AND_LOG("Failed to create window: %s\n", SDL_GetError());
    return false;
  }

  gbl_state->renderer = SDL_CreateRenderer(gbl_state->window->raw, NULL);
  if (gbl_state->renderer == NULL) {
    RAISE_AND_LOG("Failed to create SDL_Renderer: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawBlendMode(gbl_state->renderer, SDL_BLENDMODE_BLEND);

  gbl_state->running = true;
  gbl_state->project_root = project_root;

  if (!hate2d_ruby_init()) {
    RAISE_AND_LOG("Failed to initialize ruby.\n");
    return false;
  }

  return true;
}

bool hate2d_state_run_file(char* file) {
  return rb_require(file);
}

const char* hate2d_state_getcurerr() {
  VALUE err_msg = rb_funcall(rb_errinfo(), rb_intern("message"), 0);
  return RSTRING_PTR(err_msg);
}

bool hate2d_state_call_func(char* name) {
  return hate2d_ruby_call_hate2d_func(name);
}