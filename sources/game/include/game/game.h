#pragma once

#include <optional>

#include <cstdint>
#include "error.h"

enum SDL_AppResult;
union SDL_Event;

struct SDL_Window;

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

  private:
    static auto setup() -> std::optional<AppError>;
    void printFrameTimings();

  private:
    SDL_Window* window;
    uint64_t frameStartTime;
  };
} // namespace sdlgame
