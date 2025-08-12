#include "hate2d/state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "hate2d/font.h"
#include "hate2d/lua.h"

struct hate2d_state* gbl_state = NULL;

bool hate2d_state_initgbl(char* project_root) {
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
  if (!gbl_state) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to allocate memory for global state: %s\n",
                 SDL_GetError());
    return false;
  }

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

  gbl_state->running = true;
  gbl_state->project_root = project_root;

  gbl_state->fonts = hate2d_fonts_loadall();
  if (gbl_state->fonts == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load fonts: %s\n",
                 SDL_GetError());
    return false;
  }

  hate2d_lua_init();

  return true;
}

bool hate2d_state_run_file(char* file) {
  if (strstr(file, ".lua")) {
    return luaL_dofile(lua_state, file);
  }
  // add ruby at v2👀
  return false;
}

char* hate2d_state_getcurerr(char* file) {
  if (strstr(file, ".lua")) {
    return lua_tostring(lua_state, -1);
  }
  // add ruby at v2👀
  return NULL;
}

bool hate2d_state_call_func(char* file, char* name) {
  if (strstr(file, ".lua")) {
    return hate2d_lua_call_hate2d_func(lua_state, name);
  }
  // add ruby at v2👀
  return NULL;
}