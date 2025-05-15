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
    auto operator=(const Game&) noexcept -> Game& = delete;
    auto operator=(Game&&) noexcept -> Game& = delete;
    ~Game();

    auto render() -> SDL_AppResult;
    auto handleEvent(SDL_Event*) -> SDL_AppResult;
    auto setFps(uint16_t fps) -> bool;

  private:
    static auto setup() -> std::optional<AppError>;
    auto printFrameTimings() -> void;

  private:
    SDL_Window* window;
    uint16_t fps = 60;

    std::chrono::nanoseconds frameStartTime{};
    std::chrono::nanoseconds eventTime{0};
    uint64_t numEvents = 0;
  };
} // namespace sdlgame
