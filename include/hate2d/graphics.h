#ifndef __HATE2D_GRAPHICS_H__
#define __HATE2D_GRAPHICS_H__

#include <stdint.h>

int hate2d_graphics_draw_text(const char*,
                              int,
                              int,
                              uint8_t,
                              uint8_t,
                              uint8_t,
                              uint8_t);
int hate2d_graphics_draw_rect(const char*,
                              float,
                              float,
                              float,
                              float,
                              uint8_t,
                              uint8_t,
                              uint8_t,
                              uint8_t);
int hate2d_graphics_draw_pixel(int, int, uint8_t, uint8_t, uint8_t, uint8_t);
int hate2d_graphics_draw_circle(const char*,
                                int,
                                int,
                                int,
                                uint8_t,
                                uint8_t,
                                uint8_t,
                                uint8_t);

int hate2d_graphics_clear(uint8_t, uint8_t, uint8_t, uint8_t);

#endif