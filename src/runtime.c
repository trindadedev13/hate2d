#include "hate2d/runtime.h"

#include <stdbool.h>

#include "hate2d/lua.h"
#include "hate2d/state.h"

int hate2d_lua_runtime_stop(lua_State* _L) {
  gbl_state->running = false;
  return 0;
}

int hate2d_lua_runtime_delay(lua_State* L) {
  int ms = luaL_checkinteger(L, 1);
  SDL_Delay(ms);
  return 0;
}

void hate2d_lua_runtime_register(lua_State* L) {
  hate2d_lua_ibegin(L);

  lua_pushcfunction(L, hate2d_lua_runtime_stop);
  lua_setfield(L, -2, "stop");

  lua_pushcfunction(L, hate2d_lua_runtime_delay);
  lua_setfield(L, -2, "delay");

  hate2d_lua_iend(L, "runtime");
}