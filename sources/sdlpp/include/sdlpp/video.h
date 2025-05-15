#pragma once

#include <SDL3/SDL_video.h>

namespace sdl::video {
  enum struct WindowFlags : SDL_WindowFlags {
    None = 0,
    Fullscreen = SDL_WINDOW_FULLSCREEN,
    OpenGL = SDL_WINDOW_OPENGL,
    Occluded = SDL_WINDOW_OCCLUDED,
    Hidden = SDL_WINDOW_HIDDEN,
    Borderless = SDL_WINDOW_BORDERLESS,
    Resizable = SDL_WINDOW_RESIZABLE,
    Minimized = SDL_WINDOW_MINIMIZED,
    Maximized = SDL_WINDOW_MAXIMIZED,
    MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED,
    InputFocus = SDL_WINDOW_INPUT_FOCUS,
    MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
    External = SDL_WINDOW_EXTERNAL,
    Modal = SDL_WINDOW_MODAL,
    HighPixelDensity = SDL_WINDOW_HIGH_PIXEL_DENSITY,
    MouseCapture = SDL_WINDOW_MOUSE_CAPTURE,
    MouseRelativeMode = SDL_WINDOW_MOUSE_RELATIVE_MODE,
    AlwaysOnTopop = SDL_WINDOW_ALWAYS_ON_TOP,
    Utility = SDL_WINDOW_UTILITY,
    Tooltip = SDL_WINDOW_TOOLTIP,
    Popup_menu = SDL_WINDOW_POPUP_MENU,
    KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED,
    Vulkan = SDL_WINDOW_VULKAN,
    Metal = SDL_WINDOW_METAL,
    Transparent = SDL_WINDOW_TRANSPARENT,
    NotFocusable = SDL_WINDOW_NOT_FOCUSABLE,
  };

  constexpr auto windowFlags_t(WindowFlags f) noexcept -> SDL_WindowFlags {
    return static_cast<SDL_WindowFlags>(f);
  };

  constexpr auto operator|(WindowFlags a, WindowFlags b) noexcept -> WindowFlags {
    return static_cast<WindowFlags>(windowFlags_t(a) | windowFlags_t(b));
  };

  inline auto createWindow(const char* title, int w, int h, WindowFlags f) -> SDL_Window* {
    return SDL_CreateWindow(title, w, h, windowFlags_t(f));
  }

  inline void destroyWindow(SDL_Window* w) { SDL_DestroyWindow(w); }
} // namespace sdl::video
