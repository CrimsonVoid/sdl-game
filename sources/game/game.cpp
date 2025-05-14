#include "game.h"

#include <chrono>
#include <cstdint>
#include <optional>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <sdlpp/error.h>
#include <sdlpp/events.h>
#include <sdlpp/hints.h>
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
      throw AppError(ErrTag::CreateWindow, sdl::error::get());
    }

    setFps(fps);
    frameStartTime = SDL_GetTicksNS();
  }

  Game::~Game() {
    sdl::log::debug("quit sdl");
    sdl::video::destroyWindow(window);
    sdl::init::quit();
  }

  SDL_AppResult Game::render() {
    printFrameTimings();
    frameStartTime = SDL_GetTicksNS();
    return SDL_APP_CONTINUE;
  }

  SDL_AppResult Game::handleEvent(SDL_Event* event) {
    const auto start = SDL_GetTicksNS();
    const auto ev = sdl::events::Event(event);
    auto ret = SDL_APP_CONTINUE;

    switch (ev.type()) {
      using namespace sdl::events::EventType;
    case Quit: {
      ret = SDL_APP_SUCCESS;
      break;
    }
    case KeyUp: {
      auto key = ev.event->key;
      if (key.scancode == SDL_SCANCODE_Q || key.key == SDLK_ESCAPE) {
        ret = SDL_APP_SUCCESS;
        sdl::log::info("got quit");
      }
      break;
    }
    default: {
      break;
    }
    }

    eventTime += SDL_GetTicksNS() - start;
    numEvents++;

    return ret;
  }

  bool Game::setFps(uint16_t newFps) {
    char fpsStr[4] = {'\0'};

    this->fps = newFps > 999 ? 999 : newFps;

    if (fps < 10) {
      fpsStr[0] = '0' + static_cast<char>(fps);
    } else if (fps < 100) {
      fpsStr[0] = '0';
      fpsStr[1] = '0' + static_cast<char>(fps / 10);
      fpsStr[2] = '0' + static_cast<char>(fps % 10);
    } else {
      fpsStr[0] = '0' + static_cast<char>(fps / 100);
      fpsStr[1] = '0' + static_cast<char>((fps / 10) % 10);
      fpsStr[2] = '0' + static_cast<char>(fps % 10);
    }

    return sdl::hints::MainCallbackRate.set(fpsStr);
  }

  auto Game::setup() -> std::optional<AppError> {
    using enum sdl::init::flags;

    sdl::init::setAppMetadata(meta::name, meta::version, meta::identifier);
    for (const auto& [prop, val] : meta::properties) {
      sdl::init::setAppMetadataProperty(prop, val);
    }

    auto flags = Audio | Video | Haptic | Gamepad | Events;
    if (!sdl::init::init(flags)) {
      return AppError(ErrTag::Setup, sdl::error::get());
    }

    return {};
  }

  void Game::printFrameTimings() {
    namespace chrono = std::chrono;
    using doubleMilli = chrono::duration<double, std::milli>;

    const auto frameEndTime = chrono::nanoseconds{SDL_GetTicksNS()};
    const auto startTime = chrono::nanoseconds{frameStartTime};
    const auto deltaT = chrono::duration_cast<doubleMilli>(frameEndTime - startTime);

    const auto eventTimeNs = chrono::nanoseconds{eventTime};
    const auto numEvts = numEvents != 0 ? static_cast<float64_t>(numEvents) : 1.0;
    const auto avgEventTime = eventTimeNs / numEvts;

    sdl::log::debug("frame time: {} ms; avgEventTime: {} ({} / {})", deltaT, avgEventTime,
                    eventTime, numEvents);

    eventTime = 0, numEvents = 0;
  }
} // namespace sdlgame
