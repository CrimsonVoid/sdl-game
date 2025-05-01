#pragma once

#include <array>
#include <tuple>

#include <sdlpp/init.h>

namespace sdlgame::meta {
  using enum sdl::init::MetadataProperty;

  constexpr auto name = "sdl-game";
  constexpr auto version = "0.1.0";
  constexpr auto identifier = "com.example.sdl-game";

  constexpr auto properties = std::array{
      std::tuple{Type, "game"},
      // std::tuple{Creator, nullptr},
      // std::tuple{Copyright, nullptr},
      // std::tuple{Url, nullptr},
  };
} // namespace sdlgame::meta
