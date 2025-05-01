#pragma once

#include <optional>

#include <SDL3/SDL_video.h>

#include "error.h"

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

  private:
    static auto setup() -> std::optional<AppError>;

  private:
    SDL_Window* window;
  };
} // namespace sdlgame
