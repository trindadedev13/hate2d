#include "hate2d/runtime.h"

#include <SDL3/SDL.h>

#include "hate2d/state.h"

int hate2d_runtime_stop() {
  gbl_state->running = false;
  return 0;
}

int hate2d_runtime_delay(int ms) {
  SDL_Delay(ms);
  return 0;
}