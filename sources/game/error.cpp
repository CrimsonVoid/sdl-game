#include "error.h"

namespace sdlgame {
  AppError::AppError(ErrTag tag, const char* msg) : AppError(tag, ErrorData{.noData{}}, msg) {}

  AppError::AppError(ErrTag tag, ErrorData data, const char* msg)
      : tag(tag), data(data), message(msg) {}

  const char* AppError::tag_s() const noexcept {
    using enum ErrTag;
    switch (tag) {
    case SetupSetAppMetadata: return "SetupSetAppMetadata";
    case SetupInitSubSystem: return "SetupInitSubSystem";
    case CreateWindow: return "CreateWindow";
    case _exhaustive_unused: return "error: should never be used";
    default: return "Unknown";
    }
  }

  const char* AppError::what() const noexcept { return message.c_str(); }
} // namespace sdlgame
