#include "hate2d/graphics.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/lua.h"
#include "hate2d/state.h"
#include "hate2d/text.h"

int hate2d_lua_graphics_draw_text(lua_State* L) {
  const char* text = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 4, &r, &g, &b, &a);

  struct hate2d_text* text_t = hate2d_text_new(text, x, y, r, g, b, a);
  if (!hate2d_text_draw(text_t)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to draw text: %s, SDL: %s\n", text, SDL_GetError());
    return 0;
  }
  hate2d_text_destroy(text_t);
  return 0;
}

int hate2d_lua_graphics_clear(lua_State* L) {
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 1, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderClear(gbl_state->renderer);
  return 0;
}

void hate2d_lua_graphics_register(lua_State* L) {
  hate2d_lua_ibegin(L);

  lua_pushcfunction(L, hate2d_lua_graphics_draw_text);
  lua_setfield(L, -2, "draw_text");

  lua_pushcfunction(L, hate2d_lua_graphics_clear);
  lua_setfield(L, -2, "clear");

  hate2d_lua_iend(L, "graphics");
}