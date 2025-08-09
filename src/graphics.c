#include "hate2d/graphics.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/circle.h"
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
  float x, y, w, h;
  hate2d_lua_getrect(L, 1, &x, &y, &w, &h);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 2, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_FRect rect = { x, y, w, h };
  SDL_RenderRect(gbl_state->renderer, &rect);
  return 0;
}

int hate2d_lua_graphics_fill_rect(lua_State* L) {
  float x, y, w, h;
  hate2d_lua_getrect(L, 1, &x, &y, &w, &h);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 2, &r, &g, &b, &a);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_FRect rect = { x, y, w, h };
  SDL_RenderFillRect(gbl_state->renderer, &rect);
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
  int cx = luaL_checkinteger(L, 1);
  int cy = luaL_checkinteger(L, 2);
  int radius = luaL_checkinteger(L, 3);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 4, &r, &g, &b, &a);

  struct hate2d_point_arr* points = hate2d_point_arr_new();
  hate2d_point_arr_circle_points(points, cx, cy, radius);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoints(gbl_state->renderer, points->spoints, points->size);
  return 0;
}

int hate2d_lua_graphics_fill_circle(lua_State* L) {
  int cx = luaL_checkinteger(L, 1);
  int cy = luaL_checkinteger(L, 2);
  int radius = luaL_checkinteger(L, 3);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 4, &r, &g, &b, &a);

  struct hate2d_point_arr* points = hate2d_point_arr_new();
  hate2d_point_arr_filled_circle_points(points, cx, cy, radius);

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoints(gbl_state->renderer, points->spoints, points->size);
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

  lua_pushcfunction(L, hate2d_lua_graphics_draw_rect);
  lua_setfield(L, -2, "draw_rect");

  lua_pushcfunction(L, hate2d_lua_graphics_fill_rect);
  lua_setfield(L, -2, "fill_rect");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_pixel);
  lua_setfield(L, -2, "draw_pixel");

  lua_pushcfunction(L, hate2d_lua_graphics_draw_circle);
  lua_setfield(L, -2, "draw_circle");

  lua_pushcfunction(L, hate2d_lua_graphics_fill_circle);
  lua_setfield(L, -2, "fill_circle");

  hate2d_lua_iend(L, "graphics");
}