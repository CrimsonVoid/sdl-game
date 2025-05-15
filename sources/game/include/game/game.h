#pragma once

#include <chrono>
#include <cstdint>
#include <optional>

#include <SDL3/SDL_init.h>

#include "error.h"

union SDL_Event;
struct SDL_Window;

namespace sdlgame {
  enum struct GfxBackend { DX, Vulkan, Metal, OpenGL };

  constexpr GfxBackend OsDefaultBackend =
#ifdef _WIN64
      GfxBackend::DX;
#elif defined __APPLE__
      GfxBackend::Metal;
#elif defined __linux__
      GfxBackend::Vulkan;
#else
      GfxBackend::OpenGL;
#endif

  struct Game {
    Game(GfxBackend = OsDefaultBackend);
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) noexcept = delete;
    Game& operator=(Game&&) noexcept = delete;
    ~Game();

    SDL_AppResult render();
    SDL_AppResult handleEvent(SDL_Event*);
    bool setFps(uint16_t fps);

  private:
    static auto setup() -> std::optional<AppError>;
    void printFrameTimings();

  private:
    SDL_Window* window;
    uint16_t fps = 60;

    std::chrono::nanoseconds frameStartTime;
    std::chrono::nanoseconds eventTime{0};
    uint64_t numEvents = 0;
  };
} // namespace sdlgame
