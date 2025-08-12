#ifndef __HATE2D_COLOR_H__
#define __HATE2D_COLOR_H__

#include <stdint.h>

struct hate2d_color {
  uint8_t r, g, b, a;
};

typedef void (*color_exporter_func)(void* script_state,
                                    const char* name,
                                    struct hate2d_color color);

struct hate2d_color hate2d_color_new(uint8_t, uint8_t, uint8_t, uint8_t);

void hate2d_register_colors(void*, color_exporter_func);

#endif