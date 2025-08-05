#ifndef __HATE2D_FONT_H__
#define __HATE2D_FONT_H__

#include <SDL3_ttf/SDL_ttf.h>

#define FONTSIZE 35

// from $ROOT/font/jetbrainsmono_regular.c
extern unsigned char jetbrainsmono_regular_ttf[];
extern unsigned int jetbrainsmono_regular_ttf_len;

// represents the fonts used in hate2d
struct hate2d_fonts {
  TTF_Font* jetbrainsmono_regular;
};

// load all fonts used in hate2d
struct hate2d_fonts* hate2d_fonts_loadall();

// destroys all loaded fonts "instances"
void hate2d_fonts_destroy(struct hate2d_fonts*);

#endif