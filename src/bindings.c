#include "hate2d/bindings.h"

#include "hate2d/color.h"
#include "hate2d/graphics.h"
#include "hate2d/lua.h"
#include "hate2d/runtime.h"
#include "hate2d/window.h"

void hate2d_lua_register_bindings(lua_State* L) {
  hate2d_lua_runtime_register(L);
  hate2d_lua_graphics_register(L);
  hate2d_lua_window_register(L);
  hate2d_lua_color_register(L);
}