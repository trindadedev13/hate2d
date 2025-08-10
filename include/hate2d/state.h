#ifndef __HATE2D_STATE_H__
#define __HATE2D_STATE_H__

#include "hate2d/font.h"
#include "hate2d/lua.h"
#include "hate2d/window.h"

#define ASSETS_ROOT assets

struct hate2d_state {
  struct hate2d_window* window;  // main window
  struct hate2d_fonts* fonts;    // all fonts
  SDL_Renderer* renderer;        // main renderer
  lua_State* lua_state;          // lua c state
  bool running;                  // indicates if game is running
  char* project_root;            // the project root path
};

extern struct hate2d_state* gbl_state;

bool hate2d_state_initgbl(char*);

#endif