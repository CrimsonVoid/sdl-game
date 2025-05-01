#pragma once

#include <type_traits>

#include <SDL3/SDL_init.h>

namespace sdl::init {
  enum struct MetadataProperty {
    Name,
    Version,
    Identifier,
    Creator,
    Copyright,
    Url,
    Type,
  };

  inline constexpr const char* mstr(MetadataProperty p) noexcept {
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

  inline constexpr SDL_InitFlags flags_t(flags f) noexcept {
    return static_cast<SDL_InitFlags>(f);
  };

  inline constexpr flags operator|(flags a, flags b) noexcept {
    return static_cast<flags>(flags_t(a) | flags_t(b));
  };

  inline bool init(flags f) { return SDL_Init(flags_t(f)); }

  inline void quit() { return SDL_Quit(); }

  inline void quitSubSystem(flags f) { return SDL_QuitSubSystem(flags_t(f)); }

  inline bool isMainThread() { return SDL_IsMainThread(); }

  inline bool setAppMetadata(const char* name, const char* ver, const char* indentifier) {
    return SDL_SetAppMetadata(name, ver, indentifier);
  }

  inline bool setAppMetadataProperty(MetadataProperty p, const char* val) {
    return SDL_SetAppMetadataProperty(mstr(p), val);
  }

  inline flags wasInit(flags f) { return static_cast<flags>(SDL_WasInit(flags_t(f))); }

} // namespace sdl::init

// todo: unimplemented
// SDL_GetAppMetadataProperty
// SDL_RunOnMainThread
