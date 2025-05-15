#pragma once

#include <chrono>
#include <ratio>

#include <SDL3/SDL_timer.h>

namespace sdl::timer {
  using f64Milliseconds = std::chrono::duration<double, std::milli>;

  inline auto getTicksNS() -> std::chrono::nanoseconds {
    return std::chrono::nanoseconds{SDL_GetTicksNS()};
  }

  inline auto getTicks() -> std::chrono::nanoseconds {
    return std::chrono::milliseconds{SDL_GetTicks()};
  }

  template <typename T, typename U>
  constexpr auto f64Ms(std::chrono::duration<T, U> ns) -> f64Milliseconds {
    return std::chrono::duration_cast<f64Milliseconds>(ns);
  }
} // namespace sdl::timer

// todo
// SDL_AddTimer
// SDL_AddTimerNS
// SDL_Delay
// SDL_DelayNS
// SDL_DelayPrecise
// SDL_GetPerformanceCounter
// SDL_GetPerformanceFrequency
// SDL_RemoveTimer
