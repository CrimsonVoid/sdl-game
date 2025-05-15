#pragma once

#include <array>
#include <tuple>

#include <sdlpp/init.h>

namespace sdlgame::meta {
  constexpr auto name = "sdl-game";
  constexpr auto version = "0.1.0";
  constexpr auto identifier = "com.example.sdl-game";

  constexpr auto properties = std::array{
      std::tuple{sdl::init::MetadataProperty::Name, name},
      std::tuple{sdl::init::MetadataProperty::Version, version},
      std::tuple{sdl::init::MetadataProperty::Identifier, identifier},
      std::tuple{sdl::init::MetadataProperty::Type, "game"},
      // std::tuple{sdl::init::MetadataProperty::Creator, nullptr},
      // std::tuple{sdl::init::MetadataProperty::Copyright, nullptr},
      // std::tuple{sdl::init::MetadataProperty::Url, nullptr},
  };
} // namespace sdlgame::meta
