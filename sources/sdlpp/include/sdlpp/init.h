#pragma once

#include <cstdint>
#include <type_traits>

#include <SDL3/SDL_init.h>

namespace sdl::init {
  enum struct MetadataProperty : uint8_t {
    Name,
    Version,
    Identifier,
    Creator,
    Copyright,
    Url,
    Type,
  };

  constexpr auto mstr(MetadataProperty p) noexcept -> const char* {
    using enum MetadataProperty;

    switch (p) {
    case Name: return SDL_PROP_APP_METADATA_NAME_STRING;
    case Version: return SDL_PROP_APP_METADATA_VERSION_STRING;
    case Identifier: return SDL_PROP_APP_METADATA_IDENTIFIER_STRING;
    case Creator: return SDL_PROP_APP_METADATA_CREATOR_STRING;
    case Copyright: return SDL_PROP_APP_METADATA_COPYRIGHT_STRING;
    case Url: return SDL_PROP_APP_METADATA_URL_STRING;
    case Type: return SDL_PROP_APP_METADATA_TYPE_STRING;
    default: return nullptr;
    }
  }

  enum struct flags : SDL_InitFlags {
    Audio = SDL_INIT_AUDIO,
    Video = SDL_INIT_VIDEO,
    Joystick = SDL_INIT_JOYSTICK,
    Haptic = SDL_INIT_HAPTIC,
    Gamepad = SDL_INIT_GAMEPAD,
    Events = SDL_INIT_EVENTS,
    Sensor = SDL_INIT_SENSOR,
    Camera = SDL_INIT_CAMERA,
  };

  constexpr auto flags_t(flags f) noexcept -> SDL_InitFlags {
    return static_cast<SDL_InitFlags>(f);
  };

  constexpr auto operator|(flags a, flags b) noexcept -> flags {
    return static_cast<flags>(flags_t(a) | flags_t(b));
  };

  inline auto init(flags f) -> bool { return SDL_Init(flags_t(f)); }

  inline auto quit() -> void { return SDL_Quit(); }

  inline auto quitSubSystem(flags f) -> void { return SDL_QuitSubSystem(flags_t(f)); }

  inline auto isMainThread() -> bool { return SDL_IsMainThread(); }

  inline auto setAppMetadata(const char* name, const char* ver, const char* indentifier) -> bool {
    return SDL_SetAppMetadata(name, ver, indentifier);
  }

  inline auto setAppMetadataProperty(MetadataProperty p, const char* val) -> bool {
    return SDL_SetAppMetadataProperty(mstr(p), val);
  }

  inline auto getAppMetadataProperty(MetadataProperty p) -> const char* {
    return SDL_GetAppMetadataProperty(mstr(p));
  }

  inline auto wasInit(flags f) -> flags { return static_cast<flags>(SDL_WasInit(flags_t(f))); }

} // namespace sdl::init

// todo: unimplemented
// SDL_RunOnMainThread
