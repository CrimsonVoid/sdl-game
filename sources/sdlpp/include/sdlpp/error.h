#pragma once

#include <utility>

#include <SDL3/SDL_error.h>

namespace sdl::error {
  inline auto get() -> const char* { return SDL_GetError(); }

  inline auto clear() -> bool { return SDL_ClearError(); }

  template <typename... Args>
  inline auto set(const char* fmt, Args&&... args) -> bool {
    return SDL_SetError(fmt, std::forward<Args>(args)...);
  }

  inline auto setIsOOM() -> bool { return SDL_OutOfMemory(); }
} // namespace sdl::error
