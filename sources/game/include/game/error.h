#pragma once

#include <string>

namespace sdlgame {
  enum struct Tag { Setup, CreateWindow };

  struct AppError {
    std::string message;
    Tag tag;

    AppError(Tag tag, const char* msg);

    const char* tag_s() const noexcept;

    const char* what() const noexcept;
  };

} // namespace sdlgame
