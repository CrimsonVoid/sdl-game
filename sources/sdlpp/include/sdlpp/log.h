#pragma once

#include <initializer_list>
#include <type_traits>
#include <utility>

#include <SDL3/SDL_log.h>

namespace sdl::log {
  enum struct category : std::underlying_type_t<SDL_LogCategory> {
    Application = SDL_LOG_CATEGORY_APPLICATION,
    Error = SDL_LOG_CATEGORY_ERROR,
    Assert = SDL_LOG_CATEGORY_ASSERT,
    System = SDL_LOG_CATEGORY_SYSTEM,
    Audio = SDL_LOG_CATEGORY_AUDIO,
    Video = SDL_LOG_CATEGORY_VIDEO,
    Render = SDL_LOG_CATEGORY_RENDER,
    Input = SDL_LOG_CATEGORY_INPUT,
    Test = SDL_LOG_CATEGORY_TEST,
    Gpu = SDL_LOG_CATEGORY_GPU,

    /* Reserved for future SDL library use */
    Reserved2 = SDL_LOG_CATEGORY_RESERVED2,
    Reserved3 = SDL_LOG_CATEGORY_RESERVED3,
    Reserved4 = SDL_LOG_CATEGORY_RESERVED4,
    Reserved5 = SDL_LOG_CATEGORY_RESERVED5,
    Reserved6 = SDL_LOG_CATEGORY_RESERVED6,
    Reserved7 = SDL_LOG_CATEGORY_RESERVED7,
    Reserved8 = SDL_LOG_CATEGORY_RESERVED8,
    Reserved9 = SDL_LOG_CATEGORY_RESERVED9,
    Reserved10 = SDL_LOG_CATEGORY_RESERVED10,

    /* Beyond this point is reserved for application use, e.g.
       enum {
           MYAPP_CATEGORY_AWESOME1 = SDL_LOG_CATEGORY_CUSTOM,
           MYAPP_CATEGORY_AWESOME2,
           MYAPP_CATEGORY_AWESOME3,
           ...
       };
     */
    Custom = SDL_LOG_CATEGORY_CUSTOM,
  };

  inline constexpr SDL_LogCategory category_t(category c) noexcept {
    return static_cast<SDL_LogCategory>(c);
  }

  struct priority {
    inline void setAll(this priority self) {
      return SDL_SetLogPriorities(static_cast<SDL_LogPriority>(self.prio));
    }

    inline void setFor(this priority self, std::initializer_list<category> cats) {
      for (const auto cat : cats) {
        SDL_SetLogPriority(category_t(cat), self.prio);
      }
    }

    template <typename... Args>
    inline void operator()(this priority self, category cat, const char* fmt, Args&&... args) {
      return message(cat, self, fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    inline void operator()(this priority self, const char* fmt, Args&&... args) {
      return self(category::Application, fmt, std::forward<Args>(args)...);
    }

    inline constexpr bool operator==(this priority self, priority other) noexcept {
      return self.prio == other.prio;
    }
    inline constexpr bool operator==(this priority self, SDL_LogPriority other) noexcept {
      return self.prio == other;
    }

    SDL_LogPriority prio;
  };

  static constexpr priority invalid{SDL_LOG_PRIORITY_INVALID};
  static constexpr priority trace{SDL_LOG_PRIORITY_TRACE};
  static constexpr priority verbose{SDL_LOG_PRIORITY_VERBOSE};
  static constexpr priority debug{SDL_LOG_PRIORITY_DEBUG};
  static constexpr priority info{SDL_LOG_PRIORITY_INFO};
  static constexpr priority warn{SDL_LOG_PRIORITY_WARN};
  static constexpr priority error{SDL_LOG_PRIORITY_ERROR};
  static constexpr priority critical{SDL_LOG_PRIORITY_CRITICAL};
  static constexpr priority count{SDL_LOG_PRIORITY_COUNT};

  template <typename... Args>
  inline void message(category cat, priority prio, const char* fmt, Args&&... args) {
    return SDL_LogMessage(category_t(cat), prio.prio, fmt, std::forward<Args>(args)...);
  }

  inline void resetPriorities() { return SDL_ResetLogPriorities(); }

  inline priority getPriority(category cat) { return {SDL_GetLogPriority(category_t(cat))}; }
} // namespace sdl::log

// todo: unimplemented
// SDL_GetDefaultLogOutputFunction
// SDL_GetLogOutputFunction
// SDL_SetLogOutputFunction
// SDL_SetLogPriorityPrefix