cmake_minimum_required(VERSION 3.22)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../extern"
                 "${CMAKE_BINARY_DIR}/extern_build")

set(CORE_DEPS
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    liblua_static)