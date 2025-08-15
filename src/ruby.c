#include "hate2d/ruby.h"

#include <stdbool.h>
#include <stdint.h>

#include <SDL3/SDL.h>
#include <ruby.h>

#include "hate2d/color.h"
#include "hate2d/font.h"
#include "hate2d/graphics.h"
#include "hate2d/image.h"
#include "hate2d/runtime.h"
#include "hate2d/state.h"
#include "hate2d/util.h"

VALUE rb_module_hate2d = Qnil;
VALUE rb_class_image = Qnil;
VALUE rb_class_font = Qnil;
VALUE rb_default_font = Qnil;

bool hate2d_ruby_init() {
  if (ruby_setup())
    return false;
  ruby_init_loadpath();
  hate2d_ruby_register_all();
  return true;
}

void hate2d_ruby_getcolor(VALUE rb_array,
                          uint8_t* r,
                          uint8_t* g,
                          uint8_t* b,
                          uint8_t* a) {
  Check_Type(rb_array, T_ARRAY);
  if (RARRAY_LEN(rb_array) < 4)
    rb_raise(rb_eArgError, "Expected array with 4 elements");
  *r = NUM2UINT(rb_ary_entry(rb_array, 0));
  *g = NUM2UINT(rb_ary_entry(rb_array, 1));
  *b = NUM2UINT(rb_ary_entry(rb_array, 2));
  *a = NUM2UINT(rb_ary_entry(rb_array, 3));
}

void hate2d_ruby_getrect(VALUE rb_array,
                         float* x,
                         float* y,
                         float* w,
                         float* h) {
  Check_Type(rb_array, T_ARRAY);
  *x = NUM2DBL(rb_ary_entry(rb_array, 0));
  *y = NUM2DBL(rb_ary_entry(rb_array, 1));
  *w = NUM2DBL(rb_ary_entry(rb_array, 2));
  *h = NUM2DBL(rb_ary_entry(rb_array, 3));
}

VALUE hate2d_ruby_call_hate2d_func(const char* func_name) {
  VALUE top_self = rb_eval_string("self");
  return rb_funcall(top_self, rb_intern(func_name), 0);
}

char* hate2d_ruby_get_path(VALUE rb_filename) {
  const char* filename = StringValueCStr(rb_filename);
  char* first_expand = hate2d_util_str_concat("/assets/", filename);
  if (!first_expand)
    return NULL;
  char* filepath =
      hate2d_util_str_concat(gbl_state->project_root, first_expand);
  free(first_expand);
  return filepath;
}

void hate2d_ruby_register_all() {
  rb_module_hate2d = rb_define_module("Hate2D");

  VALUE rb_module_graphics =
      rb_define_module_under(rb_module_hate2d, "Graphics");
  VALUE rb_module_window = rb_define_module_under(rb_module_hate2d, "Window");
  VALUE rb_module_runtime = rb_define_module_under(rb_module_hate2d, "Runtime");
  VALUE rb_module_color = rb_define_module_under(rb_module_hate2d, "Color");

  rb_class_image = rb_define_class_under(rb_module_hate2d, "Image", rb_cObject);
  rb_class_font = rb_define_class_under(rb_module_hate2d, "Font", rb_cObject);

  rb_define_const(rb_module_graphics, "STYLE_FILLED",
                  rb_str_new_cstr("filled"));
  rb_define_const(rb_module_graphics, "STYLE_OUTLINED",
                  rb_str_new_cstr("outlined"));

  // COLOR
  hate2d_register_colors(&rb_module_color, hate2d_ruby_color_export);

  // GRAPHICS
  rb_define_singleton_method(rb_module_graphics, "draw_text",
                             hate2d_ruby_graphics_draw_text, 5);
  rb_define_singleton_method(rb_module_graphics, "draw_rect",
                             hate2d_ruby_graphics_draw_rect, 3);
  rb_define_singleton_method(rb_module_graphics, "draw_pixel",
                             hate2d_ruby_graphics_draw_pixel, 3);
  rb_define_singleton_method(rb_module_graphics, "draw_circle",
                             hate2d_ruby_graphics_draw_circle, 5);
  rb_define_singleton_method(rb_module_graphics, "draw_image",
                             hate2d_ruby_graphics_draw_image, 1);
  rb_define_singleton_method(rb_module_graphics, "clear",
                             hate2d_ruby_graphics_clear, 1);

  // IMAGE
  rb_define_alloc_func(rb_class_image, hate2d_ruby_graphics_image_alloc);
  rb_define_singleton_method(rb_class_image, "load",
                             hate2d_ruby_graphics_image_load, 5);

  // FONT
  rb_define_alloc_func(rb_class_font, hate2d_ruby_graphics_font_alloc);
  rb_define_singleton_method(rb_class_font, "load",
                             hate2d_ruby_graphics_font_load, 2);

  hate2d_ruby_graphics_font_default();
  rb_define_const(rb_class_font, "DEFAULT_FONT", rb_default_font);

  // RUNTIME
  rb_define_singleton_method(rb_module_runtime, "stop",
                             hate2d_ruby_runtime_stop, 0);
  rb_define_singleton_method(rb_module_runtime, "delay",
                             hate2d_ruby_runtime_delay, 1);

  // WINDOW
  rb_define_singleton_method(rb_module_window, "get_dimensions",
                             hate2d_ruby_window_get_dimensions, 0);
}

// ================= COLOR =================
VALUE hate2d_ruby_color_push(VALUE self, VALUE r, VALUE g, VALUE b, VALUE a) {
  VALUE arr = rb_ary_new();
  rb_ary_push(arr, r);
  rb_ary_push(arr, g);
  rb_ary_push(arr, b);
  rb_ary_push(arr, a);
  return arr;
}

void hate2d_ruby_color_export(void* ctx,
                              const char* name,
                              struct hate2d_color color) {
  VALUE mColor = *(VALUE*)ctx;
  VALUE arr = hate2d_ruby_color_push(Qnil, INT2NUM(color.r), INT2NUM(color.g),
                                     INT2NUM(color.b), INT2NUM(color.a));
  rb_define_const(mColor, name, arr);
}

// ================= GRAPHICS =================
static const rb_data_type_t hate2d_image_type = {
    .wrap_struct_name = "hate2d_image",
    .function =
        {
            .dmark = NULL,
            .dfree = hate2d_ruby_graphics_image_free,
            .dsize = NULL,
        },
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

static const rb_data_type_t hate2d_font_type = {
    .wrap_struct_name = "hate2d_font",
    .function =
        {
            .dmark = NULL,
            .dfree = hate2d_ruby_graphics_font_free,
            .dsize = NULL,
        },
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

VALUE hate2d_ruby_graphics_clear(VALUE self, VALUE rb_color) {
  uint8_t r, g, b, a;
  hate2d_ruby_getcolor(rb_color, &r, &g, &b, &a);
  return INT2NUM(hate2d_graphics_clear(r, g, b, a));
}

VALUE hate2d_ruby_graphics_draw_text(VALUE self,
                                     VALUE rb_text,
                                     VALUE rb_x,
                                     VALUE rb_y,
                                     VALUE rb_color,
                                     VALUE rb_font) {
  Check_Type(rb_text, T_STRING);
  int x = NUM2INT(rb_x);
  int y = NUM2INT(rb_y);

  struct hate2d_font** font_ud;
  TypedData_Get_Struct(rb_font, struct hate2d_font*, &hate2d_font_type,
                       font_ud);
  if (!font_ud || !*font_ud)
    rb_raise(rb_eArgError, "Expected hate2d_font");

  uint8_t r, g, b, a;
  hate2d_ruby_getcolor(rb_color, &r, &g, &b, &a);

  return INT2NUM(hate2d_graphics_draw_text(*font_ud, StringValueCStr(rb_text),
                                           x, y, r, g, b, a));
}

VALUE hate2d_ruby_graphics_draw_rect(VALUE self,
                                     VALUE rb_type,
                                     VALUE rb_rect,
                                     VALUE rb_color) {
  Check_Type(rb_type, T_STRING);
  float x, y, w, h;
  hate2d_ruby_getrect(rb_rect, &x, &y, &w, &h);

  uint8_t r, g, b, a;
  hate2d_ruby_getcolor(rb_color, &r, &g, &b, &a);

  return INT2NUM(hate2d_graphics_draw_rect(StringValueCStr(rb_type), x, y, w, h,
                                           r, g, b, a));
}

VALUE hate2d_ruby_graphics_draw_pixel(VALUE self,
                                      VALUE rb_x,
                                      VALUE rb_y,
                                      VALUE rb_color) {
  int x = NUM2INT(rb_x);
  int y = NUM2INT(rb_y);

  uint8_t r, g, b, a;
  hate2d_ruby_getcolor(rb_color, &r, &g, &b, &a);

  return INT2NUM(hate2d_graphics_draw_pixel(x, y, r, g, b, a));
}

VALUE hate2d_ruby_graphics_draw_circle(VALUE self,
                                       VALUE rb_type,
                                       VALUE rb_cx,
                                       VALUE rb_cy,
                                       VALUE rb_radius,
                                       VALUE rb_color) {
  const char* type = StringValueCStr(rb_type);
  int cx = NUM2INT(rb_cx);
  int cy = NUM2INT(rb_cy);
  int radius = NUM2INT(rb_radius);

  uint8_t r, g, b, a;
  hate2d_ruby_getcolor(rb_color, &r, &g, &b, &a);

  return INT2NUM(hate2d_graphics_draw_circle(type, cx, cy, radius, r, g, b, a));
}

VALUE hate2d_ruby_graphics_draw_image(VALUE self, VALUE rb_image) {
  struct hate2d_image** ptr;
  TypedData_Get_Struct(rb_image, struct hate2d_image*, &hate2d_image_type, ptr);
  if (!ptr || !*ptr)
    rb_raise(rb_eArgError, "Expected hate2d_image");
  hate2d_image_draw(*ptr);
  return Qnil;
}

VALUE hate2d_ruby_graphics_image_alloc(VALUE klass) {
  struct hate2d_image** ptr = ALLOC(struct hate2d_image*);
  *ptr = NULL;
  return TypedData_Wrap_Struct(klass, &hate2d_image_type, ptr);
}

VALUE hate2d_ruby_graphics_image_load(VALUE self,
                                      VALUE rb_path,
                                      VALUE rb_x,
                                      VALUE rb_y,
                                      VALUE rb_w,
                                      VALUE rb_h) {
  const char* path = hate2d_ruby_get_path(rb_path);
  int x = NUM2INT(rb_x);
  int y = NUM2INT(rb_y);
  int w = NUM2INT(rb_w);
  int h = NUM2INT(rb_h);

  struct hate2d_image* img = hate2d_image_new(path, x, y, w, h);
  if (!img) {
    RAISE_AND_LOG("Failed to load image: %s\n", path);
    return Qnil;
  }

  struct hate2d_image** ptr;
  VALUE obj = hate2d_ruby_graphics_image_alloc(rb_class_image);
  TypedData_Get_Struct(obj, struct hate2d_image*, &hate2d_image_type, ptr);
  *ptr = img;
  return obj;
}

void hate2d_ruby_graphics_image_free(void* ptr) {
  struct hate2d_image* img = *(struct hate2d_image**)ptr;
  if (img)
    hate2d_image_destroy(img);
}

VALUE hate2d_ruby_graphics_font_alloc(VALUE klass) {
  struct hate2d_font** ptr = ALLOC(struct hate2d_font*);
  *ptr = NULL;
  return TypedData_Wrap_Struct(klass, &hate2d_font_type, ptr);
}

VALUE hate2d_ruby_graphics_font_load(VALUE self, VALUE rb_path, VALUE rb_size) {
  const char* path = hate2d_ruby_get_path(rb_path);
  int size = NUM2INT(rb_size);
  struct hate2d_font* font = hate2d_font_new(path, size);
  if (!font) {
    RAISE_AND_LOG("Failed to load font: %s\n", path);
    return Qnil;
  }

  struct hate2d_font** ptr;
  VALUE obj = hate2d_ruby_graphics_font_alloc(rb_class_font);
  TypedData_Get_Struct(obj, struct hate2d_font*, &hate2d_font_type, ptr);
  *ptr = font;
  return obj;
}

void hate2d_ruby_graphics_font_free(void* ptr) {
  struct hate2d_font* font = *(struct hate2d_font**)ptr;
  if (font)
    hate2d_font_destroy(font);
}

void hate2d_ruby_graphics_font_default() {
  struct hate2d_font** font_ud;
  VALUE font_obj = hate2d_ruby_graphics_font_alloc(rb_class_font);
  TypedData_Get_Struct(font_obj, struct hate2d_font*, &hate2d_font_type,
                       font_ud);
  *font_ud = hate2d_font_new_from_mem(
      jetbrainsmono_regular_ttf, jetbrainsmono_regular_ttf_len, JET_FONTSIZE);

  if (!*font_ud) {
    RAISE_AND_LOG("Failed to allocate default font.\n");
  }

  rb_default_font = font_obj;
  rb_gc_register_address(&rb_default_font);
}

// ================= RUNTIME =================
VALUE hate2d_ruby_runtime_stop(VALUE self) {
  return INT2NUM(hate2d_runtime_stop());
}

VALUE hate2d_ruby_runtime_delay(VALUE self, VALUE ms) {
  return INT2NUM(hate2d_runtime_delay(NUM2INT(ms)));
}

// ================= WINDOW =================
VALUE hate2d_ruby_window_get_dimensions(VALUE self) {
  VALUE arr = rb_ary_new();
  rb_ary_push(arr, INT2NUM(gbl_state->window->w));
  rb_ary_push(arr, INT2NUM(gbl_state->window->h));
  return arr;
}