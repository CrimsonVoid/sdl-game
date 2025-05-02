#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_version.h>
#include <sdlpp/log.h>

#include "error.h"
#include "game.h"

void printSdlVersion();

SDL_AppResult SDL_AppInit(void** appState, int argc, char* argv[]) {
  void(argc), void(argv);

  sdl::log::debug.setAll();
  printSdlVersion();

  try {
    auto g = new sdlgame::Game();
    *appState = g;
  } catch (const sdlgame::AppError& e) {
    sdl::log::critical("uncaught app error (%s): %s", e.tag_s(), e.what());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appState) {
  auto g = static_cast<sdlgame::Game*>(appState);
  return g->render();
}

SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event) {
  auto g = static_cast<sdlgame::Game*>(appState);
  return g->handleEvent(event);
}

void SDL_AppQuit(void* appState, SDL_AppResult res) {
  auto g = static_cast<sdlgame::Game*>(appState);
  delete g;
  if (res == SDL_APP_FAILURE) {
    sdl::log::error("SDL_AppQuit: app failed");
  } else {
    sdl::log::info("SDL_AppQuit: app quit successfully");
  }
}

#ifdef SDL_MAIN_USE_CALLBACKS
int main2(int argc, char* argv[]) {
#else
int main(int argc, char* argv[]) {
#endif
  // silence unused variable warnings
  void(argc), void(argv);

  sdl::log::debug.setAll();
  printSdlVersion();

  try {
    auto g = sdlgame::Game();
    g.runLoop();
  } catch (const sdlgame::AppError& e) {
    sdl::log::critical("uncaught app error (%s): %s", e.tag_s(), e.what());
  }

  return 0;
}

void printSdlVersion() {
  const auto linkVer = SDL_GetVersion();
  sdl::log::debug("SDL Compile Version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
                  SDL_MICRO_VERSION);
  sdl::log::debug("SDL Link Version:    %d.%d.%d", SDL_VERSIONNUM_MAJOR(linkVer),
                  SDL_VERSIONNUM_MINOR(linkVer), SDL_VERSIONNUM_MICRO(linkVer));
}
