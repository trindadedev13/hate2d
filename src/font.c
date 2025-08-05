#include "hate2d/font.h"

#include <SDL3_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "hate2d/state.h"

struct hate2d_fonts* hate2d_fonts_loadall() {
  struct hate2d_fonts* it = malloc(sizeof(struct hate2d_fonts));
  if (it == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create hate2d_window");
    return NULL;
  }

  SDL_IOStream* jetbrainsmono_regular_stream =
      SDL_IOFromMem(jetbrainsmono_regular_ttf, jetbrainsmono_regular_ttf_len);

  it->jetbrainsmono_regular =
      TTF_OpenFontIO(jetbrainsmono_regular_stream, true, FONTSIZE);
  if (it->jetbrainsmono_regular == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s\n",
                 SDL_GetError());
    return NULL;
  }

  return it;
}

void hate2d_fonts_destroy(struct hate2d_fonts* self) {
  if (self == NULL)
    return;
  if (self->jetbrainsmono_regular != NULL)
    TTF_CloseFont(self->jetbrainsmono_regular);
  free(self);
}