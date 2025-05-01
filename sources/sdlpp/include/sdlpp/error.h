#pragma once

#include <SDL3/SDL_error.h>

namespace sdl::error {
  inline const char* get() { return SDL_GetError(); }

  inline bool clear() { return SDL_ClearError(); }

  template <typename... Args> inline bool set(const char* fmt, Args&&... args) {
    return SDL_SetError(fmt, std::forward<Args>(args)...);
  }

  inline bool setIsOOM() { return SDL_OutOfMemory(); }
} // namespace sdl::error
