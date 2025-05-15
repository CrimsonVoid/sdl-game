#pragma once

#include <string>

#include <sdlpp/init.h>

namespace sdlgame {
  struct NoAssociatedData {};

  struct SetupAppMetadataErr {
    sdl::init::MetadataProperty prop;
    const char* value;
  };

  enum struct ErrTag {
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

    const char* tag_s() const noexcept;

    const char* what() const noexcept;
  };

} // namespace sdlgame
