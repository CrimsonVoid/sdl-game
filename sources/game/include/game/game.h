#pragma once

#include <cstdint>
#include <optional>

#include <SDL3/SDL_init.h>

#include "error.h"

union SDL_Event;

struct SDL_Window;

using float64_t = double;

namespace sdlgame {
  enum struct GfxBackend { DX, Vulkan, Metal, OpenGL };

  struct Game {
    Game() = delete;
    Game(GfxBackend);
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) noexcept = delete;
    Game& operator=(Game&&) noexcept = delete;
    ~Game();

    void runLoop(this const Game&);
    SDL_AppResult render();
    SDL_AppResult handleEvent(SDL_Event*);
    bool setFps(int fps);

  private:
    static auto setup() -> std::optional<AppError>;
    void printFrameTimings();

  private:
    SDL_Window* window;
    int16_t fps = 999;

    uint64_t frameStartTime;
    uint64_t eventTime = 0;
    uint64_t numEvents = 0;
  };
} // namespace sdlgame
