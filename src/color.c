#include "hate2d/color.h"

#include <stdint.h>

struct hate2d_color hate2d_color_new(uint8_t R,
                                     uint8_t G,
                                     uint8_t B,
                                     uint8_t A) {
  struct hate2d_color c = {R, G, B, A};
  return c;
}

void hate2d_register_colors(void* ctx, color_exporter_func exporter) {
  exporter(ctx, "WHITE", hate2d_color_new(255, 255, 255, 255));
  exporter(ctx, "BLACK", hate2d_color_new(0, 0, 0, 255));
  exporter(ctx, "RED", hate2d_color_new(255, 0, 0, 255));
  exporter(ctx, "GREEN", hate2d_color_new(0, 255, 0, 255));
  exporter(ctx, "BLUE", hate2d_color_new(0, 0, 255, 255));
}