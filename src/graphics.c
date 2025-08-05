#include "hate2d/graphics.h"

#include <stdbool.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/lua.h"
#include "hate2d/state.h"

int hate2d_lua_graphics_print(lua_State* L) {
  const char* text = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);

  SDL_Color white = {255, 255, 255, 255};

  // text surface
  SDL_Surface* surface = TTF_RenderText_Blended(
      gbl_state->fonts->jetbrainsmono_regular, text, strlen(text), white);
  if (!surface) {
    fprintf(stderr, "Failed to render text: %s\n", SDL_GetError());
    return 0;
  }

  // text texture
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(gbl_state->renderer, surface);
  if (!texture) {
    fprintf(stderr, "Failed to create texture from surface: %s\n",
            SDL_GetError());
    SDL_DestroySurface(surface);
    return 0;
  }

  // text position
  SDL_FRect dst = {.x = (float)x,
                   .y = (float)y,
                   .w = (float)surface->w,
                   .h = (float)surface->h};

  // render texture in renderer
  SDL_RenderTexture(gbl_state->renderer, texture, NULL, &dst);

  // clear
  SDL_DestroyTexture(texture);
  SDL_DestroySurface(surface);

  return 0;
}

void hate2d_lua_graphics_register(lua_State* L) {
  {
    hate2d_lua_ibegin(L);

    lua_pushcfunction(L, hate2d_lua_graphics_print);
    lua_setfield(L, -2, "print");

    hate2d_lua_iend(L, "graphics");
  }
}