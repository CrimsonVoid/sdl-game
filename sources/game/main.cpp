#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_version.h>
#include <sdlpp/log.h>

#include "error.h"
#include "game.h"

void printSdlVersion();

auto SDL_AppInit(void** appState, int argc, char* argv[]) -> SDL_AppResult {
  void(argc), void(argv);

  sdl::log::debug.setAll();
  printSdlVersion();

  try {
    auto* g = new sdlgame::Game();
    *appState = g;
  } catch (const sdlgame::AppError& e) {
    sdl::log::critical("uncaught app error ({}): {}", e.tag_s(), e.what());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

auto SDL_AppIterate(void* appState) -> SDL_AppResult {
  auto* g = static_cast<sdlgame::Game*>(appState);
  return g->render();
}

auto SDL_AppEvent(void* appState, SDL_Event* event) -> SDL_AppResult {
  auto* g = static_cast<sdlgame::Game*>(appState);
  return g->handleEvent(event);
}

void SDL_AppQuit(void* appState, SDL_AppResult res) {
  auto* g = static_cast<sdlgame::Game*>(appState);
  delete g;
  if (res == SDL_APP_FAILURE) {
    sdl::log::error("SDL_AppQuit: app failed");
  } else {
    sdl::log::info("SDL_AppQuit: app quit successfully");
  }
}

void printSdlVersion() {
  const auto linkVer = SDL_GetVersion();
  sdl::log::debug("SDL Compile Version: {}.{}.{}", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
                  SDL_MICRO_VERSION);
  sdl::log::debug("SDL Link Version:    {}.{}.{}", SDL_VERSIONNUM_MAJOR(linkVer),
                  SDL_VERSIONNUM_MINOR(linkVer), SDL_VERSIONNUM_MICRO(linkVer));
}
