#pragma once

#include <cstdint>
#include <string>

#include <sdlpp/init.h>

namespace sdlgame {
  struct NoAssociatedData {};

  struct SetupAppMetadataErr {
    sdl::init::MetadataProperty prop;
    const char* value;
  };

  enum struct ErrTag : uint8_t {
    SetupSetAppMetadata,
    SetupInitSubSystem,
    CreateWindow,
    // marker to find where exhaustive matching is needed
    // rename and find/fix compiler errors
    _exhaustive_unused,
  };

  union ErrorData {
    NoAssociatedData noData;
    SetupAppMetadataErr appMetadata;
  };

  struct AppError {
    ErrTag tag;
    ErrorData data;
    std::string message;

    AppError(ErrTag tag, const char* msg);
    AppError(ErrTag tag, ErrorData data, const char* msg);

    [[nodiscard]] auto tag_s() const noexcept -> const char*;

    [[nodiscard]] auto what() const noexcept -> const char*;
  };

} // namespace sdlgame
