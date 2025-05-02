#include <SDL3/SDL_version.h>
#include <sdlpp/log.h>

#include "error.h"
#include "game.h"

void printSdlVersion();
constexpr auto osDefaultBacked() -> sdlgame::GfxBackend;

int main(int argc, char* argv[]) {
  // silence unused variable warnings
  void(argc), void(argv);

  sdl::log::debug.setAll();
  printSdlVersion();

  try {
    auto g = sdlgame::Game(osDefaultBacked());
    g.runLoop();
  } catch (const sdlgame::AppError& e) {
    sdl::log::critical("uncaught app error (%s): %s", e.tag_s(), e.what());
  }

  return 0;
}

inline constexpr auto osDefaultBacked() -> sdlgame::GfxBackend {
#ifdef _WIN64
  return sdlgame::GfxBackend::DX;
#elif defined __APPLE__
  return sdlgame::GfxBackend::Metal;
#elif defined __linux__
  return sdlgame::GfxBackend::Vulkan;
#else
  return sdlgame::GfxBackend::OpenGL;
#endif
}

void printSdlVersion() {
  const auto linkVer = SDL_GetVersion();
  sdl::log::debug("SDL Compile Version: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION,
                  SDL_MICRO_VERSION);
  sdl::log::debug("SDL Link Version:    %d.%d.%d", SDL_VERSIONNUM_MAJOR(linkVer),
                  SDL_VERSIONNUM_MINOR(linkVer), SDL_VERSIONNUM_MICRO(linkVer));
}
