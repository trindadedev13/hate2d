#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/state.h"
#include "hate2d/util.h"

#define HATE2D_MAJOR 1
#define HATE2D_MINOR 0
#define HATE2D_PATCH 0

char* get_main_from_str(const char* project_path, char** project_root) {
  size_t len = strlen(project_path);
  char* root_copy = malloc(len + 1);
  if (!root_copy)
    return NULL;
  strcpy(root_copy, project_path);

  if (len > 0 && root_copy[len - 1] == '/') {
    root_copy[len - 1] = '\0';
  }

  char* main = hate2d_util_str_concat(root_copy, "/src/main.lua");
  *project_root = root_copy;

  return main;
}

bool run() {
  char* project_root = hate2d_util_get_cwd();
  char* main = hate2d_util_str_concat(project_root, "/src/main.lua");
  if (!main) {
    fprintf(stderr, "Error: Failed to get current dir.\n");
    return false;
  }

  if (!hate2d_state_initgbl(project_root)) {
    return false;
  }

  if (hate2d_state_run_file(main)) {
    fprintf(stderr, "Error: %s\n", hate2d_state_getcurerr(main));
  }

  hate2d_state_call_func(main, "load");

  SDL_Event e;
  while (gbl_state->running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        gbl_state->running = false;
      }
    }
    if (!hate2d_state_call_func(main, "draw")) {
      break;
    }
    SDL_RenderPresent(gbl_state->renderer);
  }

  SDL_Quit();
  free(main);
  free(project_root);
  return true;
}

bool new(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Error: Please provide the name of new project.\n");
    return false;
  }

  bool success = false;
  char* project_root;
  char* main = get_main_from_str(argv[2], &project_root);
  char* project_src_dir = hate2d_util_str_concat(project_root, "/src/");

  if (hate2d_util_havedir(project_root)) {
    fprintf(stderr, "Error: Folder %s Already exists\n", project_root);
    goto free;
    success = false;
  }

  if (hate2d_util_mkdir_recursive(project_src_dir)) {
    FILE* f = fopen(main, "w");
    if (!f) {
      fprintf(stderr, "Error: Failed create file %s\n", main);
      goto free;
      success = false;
    }
    fprintf(f, "function hate2d.load\n\n");
    fprintf(f, "end\n\n");
    fprintf(f, "function hate2d.draw\n\n");
    fprintf(f, "end\n");
    fclose(f);
    goto free;
    success = true;
  }
  fprintf(stderr, "Error: Failed to create %s\n", project_root);

free:
  free(main);
  free(project_root);
  free(project_src_dir);
  return success;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr,
            "Error: Please provide the path of your hate2d project containing "
            "the src/main.lua\n");
    return 1;
  }

  char* op = argv[1];
  if (strcmp(op, "run") == 0) {
    return run();
  } else if (strcmp(op, "new") == 0) {
    return new(argc, argv);
  } else if (strcmp(op, "help") == 0) {
    printf(
        "hate2d framework v%d.%d.%d\n"
        "Options:\n"
        "  %s run: Runs the game. Should be called inside the project folder.\n"
        "  %s new <name>: Creates a new hate2d game project structure with "
        "provided name.\n"
        "  %s help: Prints help.\n",
        HATE2D_MAJOR, HATE2D_MINOR, HATE2D_PATCH, argv[0], argv[0], argv[0]);
    return true;
  }

  fprintf(stderr, "Invalid option %s, use help to see options\n", op);

  return 0;
}