#ifndef __HATE2D_UTIL__
#define __HATE2D_UTIL__

#include <stdbool.h>

char* hate2d_util_str_concat(const char*, const char*);

bool hate2d_util_mkdir(const char*);

bool hate2d_util_havedir(const char*);

bool hate2d_util_mkdir_recursive(const char*);

char* hate2d_util_get_cwd();

#endif