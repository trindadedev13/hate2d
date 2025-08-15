#ifndef __HATE2D_FONT_H__
#define __HATE2D_FONT_H__

#include <SDL3_ttf/SDL_ttf.h>

#define JET_FONTSIZE 35

// from $ROOT/font/jetbrainsmono_regular.c
extern unsigned char jetbrainsmono_regular_ttf[];
extern unsigned int jetbrainsmono_regular_ttf_len;

struct hate2d_font {
  TTF_Font* raw;
};

// load font
struct hate2d_font* hate2d_font_new(const char*, float);

struct hate2d_font* hate2d_font_new_from_mem(unsigned char bytes[],
                                             unsigned int,
                                             float);

// destroys font "instance"
void hate2d_font_destroy(struct hate2d_font*);

#endif