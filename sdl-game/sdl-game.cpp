// sdl-game.cpp : Defines the entry point for the application.
//

#include "sdl-game.h"

#include <print>
#include <tuple>

#include <SDL3/SDL_version.h>

auto getSDLVersion(int version) -> std::tuple<int, int, int> {
    return {
        SDL_VERSIONNUM_MAJOR(version),
        SDL_VERSIONNUM_MINOR(version),
        SDL_VERSIONNUM_MICRO(version),
    };
}

int main() {
    auto printSdlVersion = [](auto kind, auto ver) {
        const auto [major, minor, micro] = getSDLVersion(ver);
        std::println("SDL {} Version: {}.{}.{}", kind, major, minor, micro);
    };

    printSdlVersion("Compile", SDL_VERSION);
    printSdlVersion("Link", SDL_GetVersion());

    return 0;
}
