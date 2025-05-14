#include "error.h"

namespace sdlgame {
  AppError::AppError(ErrTag tag, const char* msg) : message(msg), tag(tag) {}

  const char* AppError::tag_s() const noexcept {
    using enum ErrTag;
    switch (tag) {
    case Setup: return "Setup";
    case CreateWindow: return "CreateWindow";
    default: return "Unknown";
    }
  }

  const char* AppError::what() const noexcept { return message.c_str(); }
} // namespace sdlgame
