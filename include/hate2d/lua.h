#ifndef __HATE2D_LUA_H__
#define __HATE2D_LUA_H__

#include <stdbool.h>
#include <stdint.h>

#include <lua5.1/lauxlib.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>

void hate2d_lua_ibegin(lua_State*);
void hate2d_lua_iend(lua_State*, char*);

void hate2d_lua_getcolor(lua_State*,
                         int,
                         uint8_t*,
                         uint8_t*,
                         uint8_t*,
                         uint8_t*);

/**
 * calls a function like:
 *  function hate2d.draw
 *    ...
 *  end
 */
bool hate2d_lua_call_hate2d_func(lua_State*, char*);

#endif