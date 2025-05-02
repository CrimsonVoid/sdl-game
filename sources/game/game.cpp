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
      throw AppError(Tag::CreateWindow, sdl::error::get());
    }

    setFps(fps);
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
    frameStartTime = SDL_GetTicksNS();
    return SDL_APP_CONTINUE;
  }

  SDL_AppResult Game::handleEvent(SDL_Event* event) {
    const auto start = SDL_GetTicksNS();
    const auto ev = sdl::events::Event(*event);
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
      return AppError(Tag::Setup, sdl::error::get());
    }

    return {};
  }

  void Game::printFrameTimings() {
    const auto frameEndTime = SDL_GetTicksNS();
    const auto deltaT = frameEndTime - frameStartTime;
    const auto deltaTMs = static_cast<double>(deltaT) / 1'000'000.0;

    const auto avgEventTime =
        static_cast<float64_t>(eventTime) / (numEvents ? static_cast<float64_t>(numEvents) : 1.0);
    const auto avgEventTimeMs = static_cast<double>(avgEventTime) / 1'000'000.0;

    sdl::log::debug("frame time: %0.2f ms; avgEventTime: %f (%d / %d)", deltaTMs, avgEventTimeMs,
                    eventTime, numEvents);

    eventTime = 0, numEvents = 0;
  }
} // namespace sdlgame
