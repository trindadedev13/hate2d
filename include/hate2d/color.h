#ifndef __HATE2D_COLOR_H__
#define __HATE2D_COLOR_H__

#include <stdint.h>

#include "hate2d/lua.h"

void hate2d_lua_color_add(lua_State*,
                          char*,
                          uint8_t,
                          uint8_t,
                          uint8_t,
                          uint8_t);

void hate2d_lua_color_register(lua_State*);

#endif