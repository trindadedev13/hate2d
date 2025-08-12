#include "hate2d/graphics.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "hate2d/circle.h"
#include "hate2d/state.h"
#include "hate2d/text.h"

int hate2d_graphics_draw_text(const char* text,
                              int x,
                              int y,
                              uint8_t r,
                              uint8_t g,
                              uint8_t b,
                              uint8_t a) {
  struct hate2d_text* text_t = hate2d_text_new(text, x, y, r, g, b, a);
  if (!hate2d_text_draw(text_t)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to draw text: %s, SDL: %s\n", text, SDL_GetError());
    return 0;
  }
  hate2d_text_destroy(text_t);
  return 0;
}

int hate2d_graphics_draw_rect(const char* type,
                              float x,
                              float y,
                              float w,
                              float h,
                              uint8_t r,
                              uint8_t g,
                              uint8_t b,
                              uint8_t a) {
  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_FRect rect = {x, y, w, h};
  if (strcmp(type, "fill") == 0) {
    SDL_RenderFillRect(gbl_state->renderer, &rect);
  } else {
    SDL_RenderRect(gbl_state->renderer, &rect);
  }
  return 0;
}

int hate2d_graphics_draw_pixel(int x,
                               int y,
                               uint8_t r,
                               uint8_t g,
                               uint8_t b,
                               uint8_t a) {
  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoint(gbl_state->renderer, x, y);
  return 0;
}

int hate2d_graphics_draw_circle(const char* type,
                                int cx,
                                int cy,
                                int radius,
                                uint8_t r,
                                uint8_t g,
                                uint8_t b,
                                uint8_t a) {
  struct hate2d_circle* points = hate2d_circle_new();
  if (strcmp(type, "fill") == 0) {
    hate2d_circle_filled_points(points, cx, cy, radius);
  } else {
    hate2d_circle_outlined_points(points, cx, cy, radius);
  }

  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderPoints(gbl_state->renderer, points->spoints, points->size);

  hate2d_circle_destroy(points);
  return 0;
}

int hate2d_graphics_clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(gbl_state->renderer, r, g, b, a);
  SDL_RenderClear(gbl_state->renderer);
  return 0;
}