cmake_minimum_required(VERSION 3.22)

project(hate2d)

option(ASAN "Enable Address Sanitizer" OFF)

add_compile_options(-Wall -Wextra -Wunused)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

if(ASAN)
  message(STATUS "AddressSanitizer enabled")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

file(GLOB_RECURSE
    SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckPackages.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CoreDeps.cmake)

# concatenate font bytes in SOURCES
set(S ${SOURCES})
set(SOURCES
    ${S}
    font/jetbrainsmono_regular.c)

add_executable(hate2d
    ${SOURCES})

target_include_directories(hate2d
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(hate2d
    PUBLIC
    ${CORE_DEPS}
    m)

install(TARGETS hate2d
  RUNTIME DESTINATION bin)