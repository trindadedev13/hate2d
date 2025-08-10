#ifndef __HATE2D_STR__
#define __HATE2D_STR__

#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

static char* hate2d_str_concat(const char* f1, const char* f2) {
  if (!f1 || !f2) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Cannot concatenate invalid strings.\n");
    return NULL;
  }
  char* final = malloc(strlen(f1) + strlen(f2) + 1);
  if (!final) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to allocate memory to concatenate %s + %s.\n", f1, f2);
    return NULL;
  }
  strcpy(final, f1);
  strcat(final, f2);
  return final;
}

#endif