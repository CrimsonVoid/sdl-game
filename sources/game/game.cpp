#include "game.h"

#include <optional>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <sdlpp/error.h>
#include <sdlpp/events.h>
#include <sdlpp/init.h>
#include <sdlpp/log.h>
#include <sdlpp/video.h>

#include "error.h"
#include "metadata.h"

namespace sdlgame {
  Game::Game(GfxBackend gfx) {
    using enum sdl::video::WindowFlags;

    if (const auto res = setup(); res)
      throw *res;

    auto gfxBackend = gfx == GfxBackend::Vulkan   ? Vulkan
                      : gfx == GfxBackend::Metal  ? Metal
                      : gfx == GfxBackend::OpenGL ? OpenGL
                                                  : None;
    auto windowFlags = Resizable | HighPixelDensity | gfxBackend;

    if (window = sdl::video::createWindow(meta::name, 800, 600, windowFlags); !window) {
      throw AppError(Tag::CreateWindow, sdl::error::get());
    }
  }

  Game::~Game() {
    sdl::log::debug("destroy window");
    sdl::video::destroyWindow(window);
    sdl::log::info("quit sdl");
    sdl::init::quit();
  }

  void Game::runLoop(this const Game&) {
    auto done = false;

    while (!done) {
      auto ev = sdl::events::Event{};

      while (ev.poll()) {
        using namespace sdl::events::EventType;

        switch (ev.type()) {
        case Quit: done = true; break;
        case KeyUp:
          done = ev.event.key.key == SDLK_Q || ev.event.key.key == SDLK_ESCAPE;
          if (done)
            sdl::log::info("got quit");
          break;
        default: break;
        }
      }
    }
  }

  auto Game::setup() -> std::optional<AppError> {
    using enum sdl::init::flags;

    sdl::init::setAppMetadata(meta::name, meta::version, meta::identifier);
    for (const auto& [prop, val] : meta::properties) {
      sdl::init::setAppMetadataProperty(prop, val);
    }

    auto flags = Audio | Video | Haptic | Gamepad | Events;
    if (!sdl::init::init(flags)) {
      return AppError(Tag::Setup, sdl::error::get());
    }

    return {};
  }

} // namespace sdlgame
