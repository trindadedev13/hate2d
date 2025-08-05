#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>

#include "hate2d/bindings.h"
#include "hate2d/lua.h"
#include "hate2d/state.h"

int main() {
  hate2d_state_initgbl();
  hate2d_lua_register_bindings(gbl_state->lua_state);

  if (luaL_dofile(gbl_state->lua_state, "main.lua")) {
    fprintf(stderr, "Error: %s\n", lua_tostring(gbl_state->lua_state, -1));
  }

  hate2d_lua_call_hate2d_func(gbl_state->lua_state, "load");

  SDL_Event e;
  while (gbl_state->running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        gbl_state->running = false;
      }
    }
    if (!hate2d_lua_call_hate2d_func(gbl_state->lua_state, "draw")) {
      break;
    }
    SDL_RenderPresent(gbl_state->renderer);
  }

  SDL_Quit();
  return 0;
}