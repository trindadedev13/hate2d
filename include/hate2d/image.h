#ifndef __HATE2D_IMAGE_H__
#define __HATE2D_IMAGE_H__

#include <stdbool.h>

#include <SDL3/SDL.h>

#include "hate2d/lua.h"

struct hate2d_image {
  char* filename;
  SDL_Texture* texture;
  SDL_FRect rect;
};

struct hate2d_image* hate2d_image_new(char*, int, int, int, int);

bool hate2d_image_draw(struct hate2d_image*);

void hate2d_image_destroy(struct hate2d_image*);

int hate2d_lua_image_new(lua_State*);

int hate2d_lua_image_destroy(lua_State*);

void hate2d_lua_image_register(lua_State*);

#endif