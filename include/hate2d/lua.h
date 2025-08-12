#ifndef __HATE2D_LUA_H__
#define __HATE2D_LUA_H__

#include <stdbool.h>
#include <stdint.h>

#include <lua5.1/lauxlib.h>
#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>

#include "hate2d/color.h"

extern lua_State* lua_state;

lua_State* hate2d_lua_init();

void hate2d_lua_ibegin(lua_State*);
void hate2d_lua_iend(lua_State*, char*);

void hate2d_lua_getcolor(lua_State*,
                         int,
                         uint8_t* r,
                         uint8_t* g,
                         uint8_t* b,
                         uint8_t* a);

void hate2d_lua_getrect(lua_State*,
                        int,
                        float* x,
                        float* y,
                        float* w,
                        float* h);

/**
 * calls a function like:
 *  function hate2d.draw
 *    ...
 *  end
 */
bool hate2d_lua_call_hate2d_func(lua_State*, char*);

void hate2d_lua_register_all(lua_State*);

// ============ COLOR =============== //
void hate2d_lua_color_register(lua_State*);
void hate2d_lua_color_push_color(lua_State*, struct hate2d_color);
void hate2d_lua_color_export_color(void*, const char*, struct hate2d_color);
// ============ COLOR =============== //

// ============ GRAPHICS ============= //
void hate2d_lua_graphics_register(lua_State*);
int hate2d_lua_graphics_draw_text(lua_State*);
int hate2d_lua_graphics_draw_rect(lua_State*);
int hate2d_lua_graphics_draw_pixel(lua_State*);
int hate2d_lua_graphics_draw_circle(lua_State*);
int hate2d_lua_graphics_draw_image(lua_State*);
int hate2d_lua_graphics_image_new(lua_State*);
int hate2d_lua_graphics_image_destroy(lua_State*);
// ============ GRAPHICS ============= //

// ============ RUNTIME ============== //
void hate2d_lua_runtime_register(lua_State*);
int hate2d_lua_runtime_stop(lua_State*);
int hate2d_lua_runtime_delay(lua_State*);
// ============ RUNTIME ============== //

// ============ WINDOW =============== //
int hate2d_lua_window_get_dimens(lua_State*);
void hate2d_lua_window_register(lua_State*);
// ============ WINDOW =============== //

#endif