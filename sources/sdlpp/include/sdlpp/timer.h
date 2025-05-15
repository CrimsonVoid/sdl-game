#pragma once

#include <chrono>
#include <ratio>

#include <SDL3/SDL_timer.h>

namespace sdl::timer {
  inline std::chrono::nanoseconds getTicksNS() {
    return std::chrono::nanoseconds{SDL_GetTicksNS()};
  }

  inline std::chrono::milliseconds getTicks() { return std::chrono::milliseconds{SDL_GetTicks()}; }

  template <typename T, typename U>
  inline std::chrono::duration<double, std::milli> f64Ms(std::chrono::duration<T, U> ns) {
    using f64Milli = std::chrono::duration<double, std::milli>;
    return std::chrono::duration_cast<f64Milli>(ns);
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
