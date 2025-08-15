#ifndef __HATE2D_RUBY_H__
#define __HATE2D_RUBY_H__

#include <stdbool.h>
#include <stdint.h>

#include <ruby.h>

#include "hate2d/color.h"

#define RAISE_AND_LOG(fmt, ...)                                     \
  do {                                                              \
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, fmt, ##__VA_ARGS__); \
    rb_raise(rb_eRuntimeError, fmt, ##__VA_ARGS__);                 \
  } while (0)

extern VALUE rb_module_hate2d;
extern VALUE rb_class_image;
extern VALUE rb_class_font;
extern VALUE rb_default_font;

bool hate2d_ruby_init();
void hate2d_ruby_getcolor(VALUE, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
void hate2d_ruby_getrect(VALUE rb_array, float*, float*, float*, float*);
VALUE hate2d_ruby_call_hate2d_func(const char*);
char* hate2d_ruby_get_path(VALUE);
void hate2d_ruby_register_all();

// ================= COLOR =================
VALUE hate2d_ruby_color_push(VALUE, VALUE, VALUE, VALUE, VALUE);
void hate2d_ruby_color_export(void*, const char*, struct hate2d_color);
// ================= COLOR =================

// ================= GRAPHICS =================
VALUE hate2d_ruby_graphics_draw_text(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
VALUE hate2d_ruby_graphics_draw_rect(VALUE, VALUE, VALUE, VALUE);
VALUE hate2d_ruby_graphics_draw_pixel(VALUE, VALUE, VALUE, VALUE);
VALUE hate2d_ruby_graphics_draw_circle(VALUE,
                                       VALUE,
                                       VALUE,
                                       VALUE,
                                       VALUE,
                                       VALUE);
VALUE hate2d_ruby_graphics_draw_image(VALUE, VALUE);

VALUE hate2d_ruby_graphics_image_alloc(VALUE);
VALUE hate2d_ruby_graphics_image_load(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
void hate2d_ruby_graphics_image_free(void*);

VALUE hate2d_ruby_graphics_font_alloc(VALUE);
VALUE hate2d_ruby_graphics_font_load(VALUE, VALUE, VALUE);
void hate2d_ruby_graphics_font_free(void*);
void hate2d_ruby_graphics_font_default();

VALUE hate2d_ruby_graphics_clear(VALUE, VALUE);
// ================= GRAPHICS =================

// ================= RUNTIME =================
VALUE hate2d_ruby_runtime_stop(VALUE);
VALUE hate2d_ruby_runtime_delay(VALUE, VALUE);
// ================= RUNTIME =================

// ================= WINDOW =================
VALUE hate2d_ruby_window_get_dimensions(VALUE);
// ================= WINDOW =================

#endif