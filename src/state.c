#include "hate2d/state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "hate2d/font.h"

struct hate2d_state* gbl_state = NULL;

bool hate2d_state_initgbl() {
  // initialize sdl video
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s\n",
                 SDL_GetError());
    return false;
  }

  // initialize sdl ttf
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to initialize SDL TTF: %s\n", SDL_GetError());
    return false;
  }

  gbl_state = malloc(sizeof(struct hate2d_state));

  // calculate width and height based on display
  const SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
  const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(display_id);

  // create window
  gbl_state->window = hate2d_window_create("hate2d", mode->w, mode->h);
  if (gbl_state->window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window: %s\n",
                 SDL_GetError());
    return false;
  }

  gbl_state->renderer = SDL_CreateRenderer(gbl_state->window->raw, NULL);
  if (gbl_state->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create SDL_Renderer: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawBlendMode(gbl_state->renderer, SDL_BLENDMODE_BLEND);

  gbl_state->lua_state = luaL_newstate();
  luaL_openlibs(gbl_state->lua_state);

  gbl_state->running = true;

  // creates a empty global table
  // hate2d = {}
  lua_newtable(gbl_state->lua_state);
  lua_setglobal(gbl_state->lua_state, "hate2d");

  gbl_state->fonts = hate2d_fonts_loadall();
  if (gbl_state->fonts == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load fonts: %s\n",
                 SDL_GetError());
    return false;
  }

  return true;
}