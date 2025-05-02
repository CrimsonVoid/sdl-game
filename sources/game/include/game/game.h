#pragma once

#include <optional>

#include "error.h"

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

  private:
    static auto setup() -> std::optional<AppError>;

  private:
    SDL_Window* window;
  };
} // namespace sdlgame
