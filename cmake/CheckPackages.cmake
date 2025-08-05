### Checks if the device have SDL3 and glm installed.

cmake_minimum_required(VERSION 3.22)

find_package(SDL3 QUIET)
if(SDL3_FOUND)
  set(SDL_FOUND TRUE CACHE BOOL "SDL3 found")
else()
  set(SDL_FOUND FALSE CACHE BOOL "SDL3 not found")
endif()

find_package(SDL3_ttf QUIET)
if(SDL3_ttf_FOUND)
  set(SDL_TTF_FOUND TRUE CACHE BOOL "SDL3 TTF found")
else()
  set(SDL_TTF_FOUND FALSE CACHE BOOL "SDL3 TTF not found")
endif()

find_package(SDL3_image QUIET)
if(SDL3_image_FOUND)
  set(SDL_IMAGE_FOUND TRUE CACHE BOOL "SDL3 Image found")
else()
  set(SDL_IMAGE_FOUND FALSE CACHE BOOL "SDL3 Image not found")
endif()