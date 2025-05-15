#include "game.h"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <optional>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <sdlpp/error.h>
#include <sdlpp/events.h>
#include <sdlpp/hints.h>
#include <sdlpp/init.h>
#include <sdlpp/log.h>
#include <sdlpp/timer.h>
#include <sdlpp/video.h>

#include "error.h"
#include "metadata.h"

namespace sdlgame {
  Game::Game(GfxBackend gfx) {
    using enum sdl::video::WindowFlags;

    if (const auto res = setup(); res) {
      throw *res;
    }

    auto gfxBackend = gfx == GfxBackend::Vulkan   ? Vulkan
                      : gfx == GfxBackend::Metal  ? Metal
                      : gfx == GfxBackend::OpenGL ? OpenGL
                                                  : None;
    auto windowFlags = Resizable | HighPixelDensity | gfxBackend;

    if (window = sdl::video::createWindow(meta::name, 800, 600, windowFlags); window == nullptr) {
      throw AppError(ErrTag::CreateWindow, sdl::error::get());
    }

    setFps(fps);
    frameStartTime = sdl::timer::getTicksNS();
  }

  Game::~Game() {
    sdl::log::debug("quit sdl");
    sdl::video::destroyWindow(window);
    sdl::init::quit();
  }

  auto Game::render() -> SDL_AppResult {
    printFrameTimings();
    frameStartTime = sdl::timer::getTicksNS();
    return SDL_APP_CONTINUE;
  }

  auto Game::handleEvent(SDL_Event* event) -> SDL_AppResult {
    namespace events = sdl::events;
    using namespace sdl::events::EventType;

    const auto start = sdl::timer::getTicksNS();
    const auto ev = sdl::events::Event(event);
    auto ret = SDL_APP_CONTINUE;

    switch (ev.type()) {
    case Quit: {
      ret = SDL_APP_SUCCESS;
      break;
    }
    case KeyUp: {
      const auto& key = ev.event->key;
      if (key.scancode == events::ScanCode::Q || key.key == events::KeyCode::Escape) {
        ret = SDL_APP_SUCCESS;
        sdl::log::info("got quit");
      }
      break;
    }
    default: {
      break;
    }
    }

    eventTime += sdl::timer::getTicksNS() - start;
    numEvents++;

    return ret;
  }

  auto Game::setFps(uint16_t newFps) -> bool {
    char fpsStr[4] = {'\0'};

    newFps = std::min<int>(newFps, 999);

    if (newFps < 10) {
      fpsStr[0] = '0' + static_cast<char>(newFps);
    } else if (newFps < 100) {
      fpsStr[0] = '0' + static_cast<char>(newFps / 10);
      fpsStr[1] = '0' + static_cast<char>(newFps % 10);
    } else {
      fpsStr[0] = '0' + static_cast<char>(newFps / 100);
      fpsStr[1] = '0' + static_cast<char>((newFps / 10) % 10);
      fpsStr[2] = '0' + static_cast<char>(newFps % 10);
    }

    const auto ok = sdl::hints::MainCallbackRate.set(fpsStr);
    if (ok) {
      fps = newFps;
    }

    return ok;
  }

  auto Game::setup() -> std::optional<AppError> {
    using enum sdl::init::flags;

    for (const auto& [prop, val] : meta::properties) {
      if (!sdl::init::setAppMetadataProperty(prop, val)) {
        return AppError(ErrTag::SetupSetAppMetadata, {.appMetadata{prop, val}}, sdl::error::get());
      }
    }

    auto flags = Audio | Video | Haptic | Gamepad | Events;
    if (!sdl::init::init(flags)) {
      return AppError(ErrTag::SetupInitSubSystem, sdl::error::get());
    }

    return {};
  }

  void Game::printFrameTimings() {
    const auto endTime = sdl::timer::getTicksNS();
    const auto deltaT = sdl::timer::f64Ms(endTime - frameStartTime);

    const auto numEvts = numEvents != 0 ? static_cast<double>(numEvents) : 1.0;
    const auto avgEventTime = eventTime / numEvts;

    sdl::log::debug("frame time: {} ms; avgEventTime: {} ({} / {})", deltaT, avgEventTime,
                    eventTime, numEvents);

    eventTime = std::chrono::nanoseconds{0}, numEvents = 0;
  }
} // namespace sdlgame
