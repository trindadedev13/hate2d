#include "hate2d/graphics.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/circle.h"
#include "hate2d/image.h"
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

int hate2d_lua_graphics_draw_rect(lua_State* L) {
  const char* type = luaL_checkstring(L, 1);
  float x, y, w, h;
  hate2d_lua_getrect(L, 2, &x, &y, &w, &h);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 3, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_FRect rect = {x, y, w, h};
  if (strcmp(type, "fill") == 0) {
    SDL_RenderFillRect(gbl_state->renderer, &rect);
  } else {
    SDL_RenderRect(gbl_state->renderer, &rect);
  }
  return 0;
}

int hate2d_lua_graphics_draw_pixel(lua_State* L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 3, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoint(gbl_state->renderer, x, y);
  return 0;
}

int hate2d_lua_graphics_draw_circle(lua_State* L) {
  const char* type = luaL_checkstring(L, 1);
  int cx = luaL_checkinteger(L, 2);
  int cy = luaL_checkinteger(L, 3);
  int radius = luaL_checkinteger(L, 4);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 5, &r, &g, &b, &a);

  struct hate2d_circle* points = hate2d_circle_new();
  if (strcmp(type, "fill") == 0) {
    hate2d_circle_filled_points(points, cx, cy, radius);
  } else {
    hate2d_circle_outlined_points(points, cx, cy, radius);
  }

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoints(gbl_state->renderer, points->spoints, points->size);

  hate2d_circle_destroy(points);
  return 0;
}

int hate2d_lua_graphics_draw_image(lua_State* L) {
  struct hate2d_image** udata = luaL_checkudata(L, 1, "hate2d_image_mt");
  if (!udata || !*udata) {
    return luaL_error(L, "Expected hate2d_image userdata");
  }

  hate2d_image_draw(*udata);
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

  // consts
  lua_pushstring(L, "filled");
  lua_setfield(L, -2, "STYLE_FILLED");

  lua_pushstring(L, "outlined");
  lua_setfield(L, -2, "STYLE_OUTLINED");

  // functions
  lua_pushcfunction(L, hate2d_lua_graphics_draw_text);
  lua_setfield(L, -2, "draw_text");

  lua_pushcfunction(L, hate2d_lua_graphics_clear);
  lua_setfield(L, -2, "clear");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_rect);
  lua_setfield(L, -2, "draw_rect");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_pixel);
  lua_setfield(L, -2, "draw_pixel");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_circle);
  lua_setfield(L, -2, "draw_circle");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_image);
  lua_setfield(L, -2, "draw_image");

  hate2d_lua_iend(L, "graphics");
}