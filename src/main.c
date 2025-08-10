#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/bindings.h"
#include "hate2d/lua.h"
#include "hate2d/state.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr,
            "Error: Please provide the path of your hate2d project containing "
            "the src/main.c\n");
    return 1;
  }


  char* path = argv[1];
  if (path[strlen(path) - 1] == '/') {
    path[strlen(path)] = '\0';
  }
  char* main_file_path = malloc(strlen(path) + strlen("/src/main.lua") + 1);
  strcpy(main_file_path, path);
  strcat(main_file_path, "/src/main.lua");

  if (!hate2d_state_initgbl(path)) {
    return 1;
  }
  hate2d_lua_register_bindings(gbl_state->lua_state);

  if (luaL_dofile(gbl_state->lua_state, main_file_path)) {
    fprintf(stderr, "Error: %s\n", lua_tostring(gbl_state->lua_state, -1));
  }

  free(main_file_path);

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