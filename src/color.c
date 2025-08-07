#include "hate2d/color.h"

#include <stdint.h>

#include "hate2d/lua.h"

void hate2d_lua_color_add(lua_State* L,
                          char* name,
                          uint8_t R,
                          uint8_t G,
                          uint8_t B,
                          uint8_t A) {
  lua_newtable(L);  // stack: hate2d.color.name
  // R
  lua_pushnumber(L, R);
  lua_rawseti(L, -2, 1);
  // G
  lua_pushnumber(L, G);
  lua_rawseti(L, -2, 2);
  // B
  lua_pushnumber(L, B);
  lua_rawseti(L, -2, 3);
  // A
  lua_pushnumber(L, A);
  lua_rawseti(L, -2, 4);

  lua_setfield(L, -2, name);
}

void hate2d_lua_color_register(lua_State* L) {
  hate2d_lua_ibegin(L);  // hate2d.color = {}

  hate2d_lua_color_add(L, "WHITE", 255, 255, 255, 255);
  hate2d_lua_color_add(L, "BLACK", 0, 0, 0, 255);
  hate2d_lua_color_add(L, "RED", 255, 0, 0, 255);
  hate2d_lua_color_add(L, "GREEN", 0, 255, 0, 255);
  hate2d_lua_color_add(L, "BLUE", 0, 0, 255, 255);

  hate2d_lua_iend(L,
                  "color");  // hate2d.color = { WHITE = ..., BLACK = ..., ... }
}