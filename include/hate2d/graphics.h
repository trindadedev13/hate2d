#ifndef __HATE2D_GRAPHICS_H__
#define __HATE2D_GRAPHICS_H__

#include "hate2d/lua.h"

int hate2d_lua_graphics_draw_text(lua_State*);

int hate2d_lua_graphics_draw_rect(lua_State*);
int hate2d_lua_graphics_fill_rect(lua_State*);

int hate2d_lua_graphics_draw_pixel(lua_State*);

int hate2d_lua_graphics_clear(lua_State*);

void hate2d_lua_graphics_register(lua_State*);

#endif