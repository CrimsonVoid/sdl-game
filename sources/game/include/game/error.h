#pragma once

#include <string>

namespace sdlgame {
  enum struct ErrTag { Setup, CreateWindow };

  struct AppError {
    std::string message;
    ErrTag tag;

    AppError(ErrTag tag, const char* msg);

    const char* tag_s() const noexcept;

    const char* what() const noexcept;
  };

} // namespace sdlgame
