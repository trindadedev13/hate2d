#include "hate2d/font.h"

#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "hate2d/ruby.h"
#include "hate2d/state.h"

struct hate2d_font* hate2d_font_new(const char* filename, float size) {
  struct hate2d_font* it = malloc(sizeof(struct hate2d_font));
  if (it == NULL) {
    RAISE_AND_LOG("Failed to create hate2d_font %s", filename);
    return NULL;
  }

  it->raw = TTF_OpenFont(filename, size);
  if (it->raw == NULL) {
    RAISE_AND_LOG("Failed to load font %s: %s\n", filename, SDL_GetError());
    return NULL;
  }

  return it;
}

struct hate2d_font* hate2d_font_new_from_mem(unsigned char bytes[],
                                             unsigned int bytes_len,
                                             float size) {
  struct hate2d_font* it = malloc(sizeof(struct hate2d_font));
  if (it == NULL) {
    RAISE_AND_LOG("Failed to create hate2d_font %s", SDL_GetError());
    return NULL;
  }

  SDL_IOStream* stream = SDL_IOFromMem(bytes, bytes_len);
  it->raw = TTF_OpenFontIO(stream, true, size);
  if (it->raw == NULL) {
    RAISE_AND_LOG("Failed to load font: %s\n", SDL_GetError());
    return NULL;
  }

  return it;
}

void hate2d_font_destroy(struct hate2d_font* self) {
  if (self == NULL)
    return;
  if (self->raw != NULL)
    TTF_CloseFont(self->raw);
  free(self);
}