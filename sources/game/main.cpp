#include <SDL3/SDL_version.h>
#include <sdlpp/log.h>

#include "error.h"
#include "game.h"

void printSdlVersion();

int main(int argc, char* argv[]) {
  // silence unused variable warnings
  void(argc), void(argv);

  sdl::log::debug.setAll();
  printSdlVersion();

  try {
    auto g = sdlgame::Game(sdlgame::GfxBackend::Metal);
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
