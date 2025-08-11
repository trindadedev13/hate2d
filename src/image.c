#include "hate2d/image.h"

#include <stdbool.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "hate2d/lua.h"
#include "hate2d/state.h"
#include "hate2d/str.h"

struct hate2d_image* hate2d_image_new(char* filename,
                                      int x,
                                      int y,
                                      int w,
                                      int h) {
  if (!filename) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Invalid filename for hate2d image");
    return NULL;
  }

  struct hate2d_image* it = malloc(sizeof(struct hate2d_image));
  if (!it) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to create hate2d image %s", filename);
    return NULL;
  }

  it->rect = (SDL_FRect){(float)x, (float)y, (float)w, (float)h};
  it->texture = IMG_LoadTexture(gbl_state->renderer, filename);
  if (!it->texture) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to load hate2d image %s texture: %s", filename,
                 SDL_GetError());
    free(it);
    return NULL;
  }

  return it;
}

bool hate2d_image_draw(struct hate2d_image* self) {
  if (!self || !self->texture)
    return false;

  SDL_RenderTexture(gbl_state->renderer, self->texture, NULL, &self->rect);
  return true;
}

void hate2d_image_destroy(struct hate2d_image* self) {
  if (!self)
    return;
  if (self->texture)
    SDL_DestroyTexture(self->texture);
  free(self);
}

int hate2d_lua_image_new(lua_State* L) {
  // expand file path
  // entry bg.png
  // ex1: assets/bg.png
  // filepath: %project_root%/assets/bg.png
  const char* filename = luaL_checkstring(L, 1);
  char* first_expand = hate2d_str_concat("/assets/", filename);
  if (!first_expand) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to concatenate /assets/ with %s", filename);
    return 0;
  }
  char* filepath = hate2d_str_concat(gbl_state->project_root, first_expand);
  if (!filepath) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to concatenate $s with %s", gbl_state->project_root,
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

int hate2d_lua_image_destroy(lua_State* L) {
  struct hate2d_image** udata = luaL_checkudata(L, 1, "hate2d_image_mt");
  if (udata && *udata) {
    hate2d_image_destroy(*udata);
    *udata = NULL;
  }
  return 0;
}

void hate2d_lua_image_register(lua_State* L) {
  luaL_newmetatable(L, "hate2d_image_mt");

  lua_pushcfunction(L, hate2d_lua_image_destroy);
  lua_setfield(L, -2, "__gc");

  lua_pop(L, 1);

  // register new in hate2d.
  lua_getglobal(L, "hate2d");
  lua_getfield(L, -1, "Image");
  if (lua_isnil(L, -1)) {
    lua_pop(L, 1);
    lua_newtable(L);
    lua_setfield(L, -2, "Image");
    lua_getfield(L, -1, "Image");
  }

  lua_pushcfunction(L, hate2d_lua_image_new);
  lua_setfield(L, -2, "new");

  lua_pop(L, 2);
}