#ifndef __HATE2D_RUNTIME_H__
#define __HATE2D_RUNTIME_H__

#include <stdbool.h>

#include "hate2d/lua.h"

int hate2d_lua_runtime_stop(lua_State*);

void hate2d_lua_runtime_register(lua_State*);

#endif