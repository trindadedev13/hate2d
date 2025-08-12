// ================= lua.c ===================== //
// This file contains the exports for Lua        //
// This file is only focused on translating      //
// The Lua C Api Calls to Hate2D C Compatible    //
// Please don't write logics about graphics here //
// ============================================= //

#include "hate2d/lua.h"

#include <stdint.h>

#include <SDL3/SDL.h>

#include "hate2d/color.h"
#include "hate2d/graphics.h"
#include "hate2d/image.h"
#include "hate2d/runtime.h"
#include "hate2d/state.h"
#include "hate2d/util.h"

lua_State* lua_state = NULL;

lua_State* hate2d_lua_init() {
  // creates a empty global table
  // hate2d = {}
  lua_State* l_state = luaL_newstate();
  luaL_openlibs(l_state);
  lua_newtable(l_state);
  lua_setglobal(l_state, "hate2d");

  hate2d_lua_register_all(l_state);

  lua_state = l_state;

  return l_state;
}

void hate2d_lua_ibegin(lua_State* L) {
  // stack: [hate2d]
  lua_getglobal(L, "hate2d");
  // stack: [hate2d, ???]
  lua_newtable(L);
}

void hate2d_lua_iend(lua_State* L, char* name) {
  // hate2d["name"] = name
  lua_setfield(L, -2, name);
  // pop easy 2d
  lua_pop(L, 1);
}

void hate2d_lua_getcolor(lua_State* L,
                         int wh,
                         uint8_t* r,
                         uint8_t* g,
                         uint8_t* b,
                         uint8_t* a) {
  luaL_checktype(L, wh, LUA_TTABLE);

  lua_rawgeti(L, wh, 1);
  *r = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 2);
  *g = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 3);
  *b = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 4);
  *a = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

void hate2d_lua_getrect(lua_State* L,
                        int wh,
                        float* x,
                        float* y,
                        float* w,
                        float* h) {
  luaL_checktype(L, wh, LUA_TTABLE);

  lua_rawgeti(L, wh, 1);
  *x = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 2);
  *y = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 3);
  *w = lua_tonumber(L, -1);
  lua_pop(L, 1);

  lua_rawgeti(L, wh, 4);
  *h = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

bool hate2d_lua_call_hate2d_func(lua_State* L, char* func_name) {
  lua_getglobal(L, "hate2d");  // get hate2d table
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "hate2d table not found");
    return false;
  }

  lua_getfield(L, -1, func_name);  // get hate2d[func_name]
  if (lua_isfunction(L, -1)) {
    lua_remove(L, -2);
    if (lua_pcall(L, 0, 0, 0) != 0) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to call hate2d.%s: %s",
                   func_name, lua_tostring(L, -1));
      lua_pop(L, 1);
      return false;
    }
    return true;
  } else {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Function hate2d.%s not found",
                 func_name);
    lua_pop(L, 2);
    return false;
  }
}

void hate2d_lua_register_all(lua_State* L) {
  hate2d_lua_runtime_register(L);
  hate2d_lua_graphics_register(L);
  hate2d_lua_window_register(L);
  hate2d_lua_color_register(L);
}

// ============ COLOR =============== //
void hate2d_lua_color_register(lua_State* L) {
  hate2d_lua_ibegin(L);
  hate2d_register_colors(L, hate2d_lua_color_export_color);
  hate2d_lua_iend(L, "color");
}

void hate2d_lua_color_push_color(lua_State* L, struct hate2d_color color) {
  lua_newtable(L);
  lua_pushinteger(L, color.r);
  lua_rawseti(L, -2, 1);
  lua_pushinteger(L, color.g);
  lua_rawseti(L, -2, 2);
  lua_pushinteger(L, color.b);
  lua_rawseti(L, -2, 3);
  lua_pushinteger(L, color.a);
  lua_rawseti(L, -2, 4);
}

void hate2d_lua_color_export_color(void* L,
                                   const char* name,
                                   struct hate2d_color color) {
  lua_State* state = (lua_State*)L;
  hate2d_lua_color_push_color(state, color);
  lua_setfield(state, -2, name);
}
// ============ COLOR =============== //

// ============ GRAPHICS ============= //
int hate2d_lua_graphics_draw_text(lua_State* L) {
  const char* text = luaL_checkstring(L, 1);
  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 4, &r, &g, &b, &a);
  return hate2d_graphics_draw_text(text, x, y, r, g, b, a);
}

int hate2d_lua_graphics_draw_rect(lua_State* L) {
  const char* type = luaL_checkstring(L, 1);
  float x, y, w, h;
  hate2d_lua_getrect(L, 2, &x, &y, &w, &h);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 3, &r, &g, &b, &a);

  return hate2d_graphics_draw_rect(type, x, y, w, h, r, g, b, a);
}

int hate2d_lua_graphics_draw_pixel(lua_State* L) {
  int x = luaL_checkinteger(L, 1);
  int y = luaL_checkinteger(L, 2);

  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 3, &r, &g, &b, &a);

  return hate2d_graphics_draw_pixel(x, y, r, g, b, a);
}

int hate2d_lua_graphics_draw_circle(lua_State* L) {
  const char* type = luaL_checkstring(L, 1);
  int cx = luaL_checkinteger(L, 2);
  int cy = luaL_checkinteger(L, 3);
  int radius = luaL_checkinteger(L, 4);
  uint8_t r, g, b, a;
  hate2d_lua_getcolor(L, 5, &r, &g, &b, &a);

  return hate2d_graphics_draw_circle(type, cx, cy, radius, r, g, b, a);
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
  return hate2d_graphics_clear(r, g, b, a);
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

  luaL_newmetatable(L, "hate2d_image_mt");

  lua_pushcfunction(L, hate2d_lua_graphics_image_destroy);
  lua_setfield(L, -2, "__gc");

  lua_pop(L, 1);

  // register new in hate2d.graphics.Image
  lua_getfield(L, -1, "Image");
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    lua_newtable(L);
    lua_setfield(L, -2, "Image");
    lua_getfield(L, -1, "Image");
  }

  lua_pushcfunction(L, hate2d_lua_graphics_image_new);
  lua_setfield(L, -2, "new");

  lua_pop(L, 1);

  hate2d_lua_iend(L, "graphics");
}

int hate2d_lua_graphics_image_new(lua_State* L) {
  // expand file path
  // entry bg.png
  // ex1: assets/bg.png
  // filepath: %project_root%/assets/bg.png
  const char* filename = luaL_checkstring(L, 1);
  char* first_expand = hate2d_util_str_concat("/assets/", filename);
  if (!first_expand) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to concatenate /assets/ with %s", filename);
    return 0;
  }
  char* filepath =
      hate2d_util_str_concat(gbl_state->project_root, first_expand);
  if (!filepath) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to concatenate %s with %s", gbl_state->project_root,
                 first_expand);
    return 0;
  }

  int x = luaL_checkinteger(L, 2);
  int y = luaL_checkinteger(L, 3);
  int w = luaL_checkinteger(L, 4);
  int h = luaL_checkinteger(L, 5);

  struct hate2d_image* img = hate2d_image_new(filepath, x, y, w, h);
  if (!img) {
    lua_pushnil(L);
    return 1;
  }

  struct hate2d_image** udata =
      lua_newuserdata(L, sizeof(struct hate2d_image*));
  *udata = img;

  luaL_getmetatable(L, "hate2d_image_mt");
  lua_setmetatable(L, -2);

  return 1;
}

int hate2d_lua_graphics_image_destroy(lua_State* L) {
  struct hate2d_image** udata = luaL_checkudata(L, 1, "hate2d_image_mt");
  if (udata && *udata) {
    hate2d_image_destroy(*udata);
    *udata = NULL;
  }
  return 0;
}

// ============ GRAPHICS ============= //

// ============ RUNTIME ============== //

int hate2d_lua_runtime_stop(lua_State* L) {
  return hate2d_runtime_stop();
}

int hate2d_lua_runtime_delay(lua_State* L) {
  int ms = luaL_checkinteger(L, 1);
  return hate2d_runtime_delay(ms);
}

void hate2d_lua_runtime_register(lua_State* L) {
  hate2d_lua_ibegin(L);

  lua_pushcfunction(L, hate2d_lua_runtime_stop);
  lua_setfield(L, -2, "stop");

  lua_pushcfunction(L, hate2d_lua_runtime_delay);
  lua_setfield(L, -2, "delay");

  hate2d_lua_iend(L, "runtime");
}

// ============ RUNTIME ============== //

// ============ WINDOW =============== //
int hate2d_lua_window_get_dimens(lua_State* L) {
  lua_pushinteger(L, gbl_state->window->w);
  lua_pushinteger(L, gbl_state->window->h);
  return 2;
}

void hate2d_lua_window_register(lua_State* L) {
  hate2d_lua_ibegin(L);

  lua_pushcfunction(L, hate2d_lua_window_get_dimens);
  lua_setfield(L, -2, "get_dimensions");

  hate2d_lua_iend(L, "window");
}
// ============ WINDOW =============== //