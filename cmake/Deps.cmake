cmake_minimum_required(VERSION 3.22)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../extern"
                 "${CMAKE_BINARY_DIR}/extern_build")

find_package(Ruby REQUIRED)

set(DEPS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    ${RUBY_LIBRARY})

set(INCLUDE
    ${RUBY_INCLUDE_DIRS})