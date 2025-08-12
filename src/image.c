#include "hate2d/image.h"

#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "hate2d/state.h"
#include "hate2d/util.h"

struct hate2d_image* hate2d_image_new(char* filename,
                                      int x,
                                      int y,
                                      int w,
                                      int h) {
  if (!filename) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Invalid filename for hate2d image");
    return NULL;
  }

  struct hate2d_image* it = malloc(sizeof(struct hate2d_image));
  if (!it) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create hate2d image %s", filename);
    return NULL;
  }

  it->rect = (SDL_FRect){(float)x, (float)y, (float)w, (float)h};
  it->texture = IMG_LoadTexture(gbl_state->renderer, filename);
  if (!it->texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to load hate2d image %s texture: %s", filename,
                 SDL_GetError());
    free(it);
    return NULL;
  }

  return it;
}

bool hate2d_image_draw(struct hate2d_image* self) {
  if (!self || !self->texture)
    return false;

  SDL_RenderTexture(gbl_state->renderer, self->texture, NULL, &self->rect);
  return true;
}

void hate2d_image_destroy(struct hate2d_image* self) {
  if (!self)
    return;
  if (self->texture)
    SDL_DestroyTexture(self->texture);
  free(self);
}