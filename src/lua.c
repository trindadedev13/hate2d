#include "hate2d/lua.h"

#include <SDL3/SDL.h>

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