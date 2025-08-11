#include "hate2d/util.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <sys/stat.h>

#ifdef _WIN32

#include <direct.h>
#include <windows.h>
#ifndef getcwd
#define getcwd _getcwd
#endif
#ifndef S_ISDIR
#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif
#else
#include <dirent.h>
#include <unistd.h>

#endif

char* hate2d_util_str_concat(const char* f1, const char* f2) {
  if (!f1 || !f2) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Cannot concatenate invalid strings.\n");
    return NULL;
  }
  char* final = malloc(strlen(f1) + strlen(f2) + 1);
  if (!final) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to allocate memory to concatenate %s + %s.\n", f1, f2);
    return NULL;
  }
  strcpy(final, f1);
  strcat(final, f2);
  return final;
}

bool hate2d_util_havedir(const char* dir) {
  struct stat info;
  return stat(dir, &info) == 0 && S_ISDIR(info.st_mode);
}

bool hate2d_util_mkdir(const char* dir) {
#ifdef _WIN32
  return _mkdir(dir) == 0;
#else
  return mkdir(dir, 0755) == 0;
#endif
}

bool hate2d_util_mkdir_recursive(const char* path) {
  char* tmp = strdup(path);
  if (!tmp)
    return false;

  size_t len = strlen(tmp);
  if (len == 0) {
    free(tmp);
    return false;
  }

  if (tmp[len - 1] == '/' || tmp[len - 1] == '\\') {
    tmp[len - 1] = '\0';
  }

  for (char* p = tmp + 1; *p; p++) {
    if (*p == '/' || *p == '\\') {
      *p = '\0';
      hate2d_util_mkdir(tmp);
      *p = '/';
    }
  }
  bool ok = hate2d_util_mkdir(tmp);
  free(tmp);
  return ok;
}

char* hate2d_util_get_cwd() {
  char* cwd = malloc(PATH_MAX);
  if (cwd == NULL)
    return NULL;
  if (getcwd(cwd, PATH_MAX) != NULL) {
    return cwd;
  }
  free(cwd);
  return NULL;
}