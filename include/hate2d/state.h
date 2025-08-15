#ifndef __HATE2D_STATE_H__
#define __HATE2D_STATE_H__

#include "hate2d/window.h"

struct hate2d_state {
  struct hate2d_window* window;  // main window
  SDL_Renderer* renderer;        // main renderer
  bool running;                  // indicates if game is running
  char* project_root;            // the project root path
};

extern struct hate2d_state* gbl_state;

bool hate2d_state_initgbl(char*);

// first param is always the filename
bool hate2d_state_run_file(char*);
const char* hate2d_state_getcurerr();
bool hate2d_state_call_func(char*);

#endif