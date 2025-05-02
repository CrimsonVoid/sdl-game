#include "game.h"

#include <cstdint>
#include <optional>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
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

    frameStartTime = SDL_GetTicksNS();
  }

  Game::~Game() {
    sdl::log::debug("quit sdl");
    sdl::video::destroyWindow(window);
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
          done = ev.event.key.scancode == SDL_SCANCODE_Q || ev.event.key.key == SDL_SCANCODE_ESCAPE;
          if (done)
            sdl::log::info("got quit");
          break;
        default: break;
        }
      }
    }
  }

  SDL_AppResult Game::render() {
    printFrameTimings();
    return SDL_APP_CONTINUE;
  }

  SDL_AppResult Game::handleEvent(SDL_Event* event) {
    auto ev = sdl::events::Event(*event);
    auto ret = SDL_APP_CONTINUE;

    switch (ev.type()) {
      using namespace sdl::events::EventType;

    case Quit: ret = SDL_APP_SUCCESS; break;
    case KeyUp:
      auto key = ev.event.key;
      if (key.scancode == SDL_SCANCODE_Q || key.key == SDLK_ESCAPE) {
        ret = SDL_APP_SUCCESS;
        sdl::log::info("got quit");
      }
      break;
    default: break;
    }

    return ret;
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

  void Game::printFrameTimings() {
    constexpr auto fps = 30.0;
    constexpr auto frameTimeNs = 1'000'000'000 / fps;

    const auto frameEndTime = SDL_GetTicksNS();
    const auto deltaT = frameEndTime - frameStartTime;
    frameStartTime = frameEndTime;
    const auto delay = (uint64_t)frameTimeNs - deltaT;

    const auto deltaTMs = static_cast<double>(deltaT) / 1'000'000;
    const auto delayMs = static_cast<double>(delay) / 1'000'000;
    sdl::log::debug("frame time: %0.2f ms, sleep %0.2f ms (%d sleep, %d ns)", deltaTMs, delayMs, delay, deltaT);

    if (delay > 0)
      SDL_DelayNS(delay);
  }
} // namespace sdlgame
