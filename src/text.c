#include "hate2d/text.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "hate2d/state.h"

struct hate2d_text* hate2d_text_new(const char* text,
                                    int x,
                                    int y,
                                    uint8_t r,
                                    uint8_t g,
                                    uint8_t b,
                                    uint8_t a) {
  if (!text) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Invalid text to draw!\n");
    return false;
  }
  struct hate2d_text* it = malloc(sizeof(struct hate2d_text));
  if (!it) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to allocate memory for text: %s : %s\n", text,
                 SDL_GetError());
    return false;
  }
  it->text = strdup(text);
  it->x = x;
  it->y = y;
  it->color = (SDL_Color){r, g, b, a};
  return it;
}

bool hate2d_text_draw(struct hate2d_text* self) {
  if (!self)
    return false;
  if (!self->text)
    return false;

  // text surface
  SDL_Surface* surface =
      TTF_RenderText_Blended(gbl_state->fonts->jetbrainsmono_regular,
                             self->text, strlen(self->text), self->color);
  if (!surface) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text: %s\n",
                 SDL_GetError());
    return 0;
  }

  // text texture
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(gbl_state->renderer, surface);
  if (!texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create texture from surface: %s\n", SDL_GetError());
    SDL_DestroySurface(surface);
    return 0;
  }

  // text position
  SDL_FRect dst = {.x = (float)self->x,
                   .y = (float)self->y,
                   .w = (float)surface->w,
                   .h = (float)surface->h};

  // render texture in renderer
  SDL_RenderTexture(gbl_state->renderer, texture, NULL, &dst);

  // clear
  SDL_DestroyTexture(texture);
  SDL_DestroySurface(surface);
  return true;
}

void hate2d_text_destroy(struct hate2d_text* self) {
  if (!self)
    return;
  if (!self->text)
    return;
  free(self->text);
  free(self);
}