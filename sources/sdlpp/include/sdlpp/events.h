#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_stdinc.h>

namespace sdl::events {
  struct Type {
    SDL_EventType ty;

    inline constexpr Type(Uint32 t) noexcept : ty(static_cast<SDL_EventType>(t)) {}

    inline constexpr operator SDL_EventType() const noexcept { return ty; }

    inline bool isEnabled(this Type self) { return SDL_EventEnabled(self.ty); }

    inline void setEnabled(Uint32 ty, bool enabled) { return SDL_SetEventEnabled(ty, enabled); };

    inline void flush(this Type self) { return SDL_FlushEvent(self.ty); }

    inline void flushRange(this Type min, Type max) { return SDL_FlushEvents(min.ty, max.ty); }

    inline bool hasEvent(this Type self) { return SDL_HasEvent(self.ty); }

    inline bool hasEvents(this Type min, Type max) { return SDL_HasEvents(min.ty, max.ty); }
  };

  namespace EventType {
    static constexpr Type First{SDL_EVENT_FIRST};

    // Application events
    static constexpr Type Quit{SDL_EVENT_QUIT};
    static constexpr Type Terminating{SDL_EVENT_TERMINATING};
    static constexpr Type LowMemory{SDL_EVENT_LOW_MEMORY};
    static constexpr Type WillEnterBackground{SDL_EVENT_WILL_ENTER_BACKGROUND};
    static constexpr Type DidEnterBackground{SDL_EVENT_DID_ENTER_BACKGROUND};
    static constexpr Type WillEnterForeground{SDL_EVENT_WILL_ENTER_FOREGROUND};
    static constexpr Type DidEnterForeground{SDL_EVENT_DID_ENTER_FOREGROUND};
    static constexpr Type LocaleChanged{SDL_EVENT_LOCALE_CHANGED};
    static constexpr Type SystemThemeChanged{SDL_EVENT_SYSTEM_THEME_CHANGED};
    static constexpr Type DisplayOrientation{SDL_EVENT_DISPLAY_ORIENTATION};
    static constexpr Type DisplayAdded{SDL_EVENT_DISPLAY_ADDED};
    static constexpr Type DisplayRemoved{SDL_EVENT_DISPLAY_REMOVED};
    static constexpr Type DisplayMoved{SDL_EVENT_DISPLAY_MOVED};

    // Display events
    static constexpr Type DisplayDesktopModeChanged{SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED};
    static constexpr Type DisplayCurrentModeChanged{SDL_EVENT_DISPLAY_CURRENT_MODE_CHANGED};
    static constexpr Type DisplayContentScaleChanged{SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED};
    static constexpr Type DisplayFirst{SDL_EVENT_DISPLAY_FIRST};
    static constexpr Type DisplayLast{SDL_EVENT_DISPLAY_LAST};

    // Window events
    static constexpr Type WindowShown{SDL_EVENT_WINDOW_SHOWN};
    static constexpr Type WindowHidden{SDL_EVENT_WINDOW_HIDDEN};
    static constexpr Type WindowExposed{SDL_EVENT_WINDOW_EXPOSED};
    static constexpr Type WindowMoved{SDL_EVENT_WINDOW_MOVED};
    static constexpr Type WindowResized{SDL_EVENT_WINDOW_RESIZED};
    static constexpr Type WindowPixelSizeChanged{SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED};
    static constexpr Type WindowMetalViewResized{SDL_EVENT_WINDOW_METAL_VIEW_RESIZED};
    static constexpr Type WindowMinimized{SDL_EVENT_WINDOW_MINIMIZED};
    static constexpr Type WindowMaximized{SDL_EVENT_WINDOW_MAXIMIZED};
    static constexpr Type WindowRestored{SDL_EVENT_WINDOW_RESTORED};
    static constexpr Type WindowMouseEnter{SDL_EVENT_WINDOW_MOUSE_ENTER};
    static constexpr Type WindowMouseLeave{SDL_EVENT_WINDOW_MOUSE_LEAVE};
    static constexpr Type WindowFocusGained{SDL_EVENT_WINDOW_FOCUS_GAINED};
    static constexpr Type WindowFocusLost{SDL_EVENT_WINDOW_FOCUS_LOST};
    static constexpr Type WindowCloseRequested{SDL_EVENT_WINDOW_CLOSE_REQUESTED};
    static constexpr Type WindowHitTest{SDL_EVENT_WINDOW_HIT_TEST};
    static constexpr Type WindowIccprofChanged{SDL_EVENT_WINDOW_ICCPROF_CHANGED};
    static constexpr Type WindowDisplayChanged{SDL_EVENT_WINDOW_DISPLAY_CHANGED};
    static constexpr Type WindowDisplayScaleChanged{SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED};
    static constexpr Type WindowSafeAreaChanged{SDL_EVENT_WINDOW_SAFE_AREA_CHANGED};
    static constexpr Type WindowOccluded{SDL_EVENT_WINDOW_OCCLUDED};
    static constexpr Type WindowEnterFullscreen{SDL_EVENT_WINDOW_ENTER_FULLSCREEN};
    static constexpr Type WindowLeaveFullscreen{SDL_EVENT_WINDOW_LEAVE_FULLSCREEN};
    static constexpr Type WindowDestroyed{SDL_EVENT_WINDOW_DESTROYED};
    static constexpr Type WindowHdrStateChanged{SDL_EVENT_WINDOW_HDR_STATE_CHANGED};
    static constexpr Type WindowFirst{SDL_EVENT_WINDOW_FIRST};
    static constexpr Type WindowLast{SDL_EVENT_WINDOW_LAST};

    // Keyboard events
    static constexpr Type KeyDown{SDL_EVENT_KEY_DOWN};
    static constexpr Type KeyUp{SDL_EVENT_KEY_UP};
    static constexpr Type TextEditing{SDL_EVENT_TEXT_EDITING};
    static constexpr Type TextInput{SDL_EVENT_TEXT_INPUT};
    static constexpr Type KeymapChanged{SDL_EVENT_KEYMAP_CHANGED};
    static constexpr Type KeyboardAdded{SDL_EVENT_KEYBOARD_ADDED};
    static constexpr Type KeyboardRemoved{SDL_EVENT_KEYBOARD_REMOVED};
    static constexpr Type TextEditingCandidates{SDL_EVENT_TEXT_EDITING_CANDIDATES};

    // Mouse events
    static constexpr Type MouseMotion{SDL_EVENT_MOUSE_MOTION};
    static constexpr Type MouseButtonDown{SDL_EVENT_MOUSE_BUTTON_DOWN};
    static constexpr Type MouseButtonUp{SDL_EVENT_MOUSE_BUTTON_UP};
    static constexpr Type MouseWheel{SDL_EVENT_MOUSE_WHEEL};
    static constexpr Type MouseAdded{SDL_EVENT_MOUSE_ADDED};
    static constexpr Type MouseRemoved{SDL_EVENT_MOUSE_REMOVED};

    // Joystick events
    static constexpr Type JoystickAxisMotion{SDL_EVENT_JOYSTICK_AXIS_MOTION};
    static constexpr Type JoystickBallMotion{SDL_EVENT_JOYSTICK_BALL_MOTION};
    static constexpr Type JoystickHatMotion{SDL_EVENT_JOYSTICK_HAT_MOTION};
    static constexpr Type JoystickButtonDown{SDL_EVENT_JOYSTICK_BUTTON_DOWN};
    static constexpr Type JoystickButtonUp{SDL_EVENT_JOYSTICK_BUTTON_UP};
    static constexpr Type JoystickAdded{SDL_EVENT_JOYSTICK_ADDED};
    static constexpr Type JoystickRemoved{SDL_EVENT_JOYSTICK_REMOVED};
    static constexpr Type JoystickBatteryUpdated{SDL_EVENT_JOYSTICK_BATTERY_UPDATED};
    static constexpr Type JoystickUpdateComplete{SDL_EVENT_JOYSTICK_UPDATE_COMPLETE};

    // Gamepad events
    static constexpr Type GamepadAxisMotion{SDL_EVENT_GAMEPAD_AXIS_MOTION};
    static constexpr Type GamepadButtonDown{SDL_EVENT_GAMEPAD_BUTTON_DOWN};
    static constexpr Type GamepadButtonUp{SDL_EVENT_GAMEPAD_BUTTON_UP};
    static constexpr Type GamepadAdded{SDL_EVENT_GAMEPAD_ADDED};
    static constexpr Type GamepadRemoved{SDL_EVENT_GAMEPAD_REMOVED};
    static constexpr Type GamepadRemapped{SDL_EVENT_GAMEPAD_REMAPPED};
    static constexpr Type GamepadTouchpadDown{SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN};
    static constexpr Type GamepadTouchpadMotion{SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION};
    static constexpr Type GamepadTouchpadUp{SDL_EVENT_GAMEPAD_TOUCHPAD_UP};
    static constexpr Type GamepadSensorUpdate{SDL_EVENT_GAMEPAD_SENSOR_UPDATE};
    static constexpr Type GamepadUpdateComplete{SDL_EVENT_GAMEPAD_UPDATE_COMPLETE};
    static constexpr Type GamepadSteamHandleUpdated{SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED};

    // Touch events
    static constexpr Type FingerDown{SDL_EVENT_FINGER_DOWN};
    static constexpr Type FingerUp{SDL_EVENT_FINGER_UP};
    static constexpr Type FingerMotion{SDL_EVENT_FINGER_MOTION};
    static constexpr Type FingerCanceled{SDL_EVENT_FINGER_CANCELED};

    // Clipboard events
    static constexpr Type ClipboardUpdate{SDL_EVENT_CLIPBOARD_UPDATE};

    // Drag and drop events
    static constexpr Type DropFile{SDL_EVENT_DROP_FILE};
    static constexpr Type DropText{SDL_EVENT_DROP_TEXT};
    static constexpr Type DropBegin{SDL_EVENT_DROP_BEGIN};
    static constexpr Type DropComplete{SDL_EVENT_DROP_COMPLETE};
    static constexpr Type DropPosition{SDL_EVENT_DROP_POSITION};

    // Audio hotplug events
    static constexpr Type AudioDeviceAdded{SDL_EVENT_AUDIO_DEVICE_ADDED};
    static constexpr Type AudioDeviceRemoved{SDL_EVENT_AUDIO_DEVICE_REMOVED};
    static constexpr Type AudioDeviceFormatChanged{SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED};

    // Sensor events
    static constexpr Type SensorUpdate{SDL_EVENT_SENSOR_UPDATE};

    // Pressure-sensitive pen events
    static constexpr Type PenProximityIn{SDL_EVENT_PEN_PROXIMITY_IN};
    static constexpr Type PenProximityOut{SDL_EVENT_PEN_PROXIMITY_OUT};
    static constexpr Type PenDown{SDL_EVENT_PEN_DOWN};
    static constexpr Type PenUp{SDL_EVENT_PEN_UP};
    static constexpr Type PenButtonDown{SDL_EVENT_PEN_BUTTON_DOWN};
    static constexpr Type PenButtonUp{SDL_EVENT_PEN_BUTTON_UP};
    static constexpr Type PenMotion{SDL_EVENT_PEN_MOTION};
    static constexpr Type PenAxis{SDL_EVENT_PEN_AXIS};

    // Camera hotplug events
    static constexpr Type CameraDeviceAdded{SDL_EVENT_CAMERA_DEVICE_ADDED};
    static constexpr Type CameraDeviceRemoved{SDL_EVENT_CAMERA_DEVICE_REMOVED};
    static constexpr Type CameraDeviceApproved{SDL_EVENT_CAMERA_DEVICE_APPROVED};
    static constexpr Type CameraDeviceDenied{SDL_EVENT_CAMERA_DEVICE_DENIED};

    // Render events
    static constexpr Type RenderTargetsReset{SDL_EVENT_RENDER_TARGETS_RESET};
    static constexpr Type RenderDeviceReset{SDL_EVENT_RENDER_DEVICE_RESET};
    static constexpr Type RenderDeviceLost{SDL_EVENT_RENDER_DEVICE_LOST};

    // Reserved events for private platforms
    static constexpr Type Private0{SDL_EVENT_PRIVATE0};
    static constexpr Type Private1{SDL_EVENT_PRIVATE1};
    static constexpr Type Private2{SDL_EVENT_PRIVATE2};
    static constexpr Type Private3{SDL_EVENT_PRIVATE3};

    // Internal events
    static constexpr Type PollSentinel{SDL_EVENT_POLL_SENTINEL};

    // Events SDL_EVENT_USER through SDL_EVENT_LAST are for your use,and should
    // be allocated with SDL_RegisterEvents()
    static constexpr Type User{SDL_EVENT_USER};

    // This last event is only for bounding internal arrays
    static constexpr Type Last{SDL_EVENT_LAST};
  }; // namespace EventType

  struct Event {
    SDL_Event event;

    inline bool poll() { return SDL_PollEvent(&event); }

    inline bool wait() { return SDL_WaitEvent(&event); };

    inline bool waitTimeout(Sint32 timeoutMS) { return SDL_WaitEventTimeout(&event, timeoutMS); };

    inline constexpr Type type() const noexcept { return event.type; }

    inline SDL_Window* getWindow() const { return SDL_GetWindowFromEvent(&event); }

    inline bool push() { return SDL_PushEvent(&event); }

    inline static bool push(SDL_Event* event) { return SDL_PushEvent(event); }
  };

  inline void pump() { return SDL_PumpEvents(); }

  inline bool push(SDL_Event* event) { return SDL_PushEvent(event); }

  inline Uint32 registerEvents(int numevents) { return SDL_RegisterEvents(numevents); }

} // namespace sdl::events

// SDL_AddEventWatch
// SDL_FilterEvents
// SDL_GetEventDescription
// SDL_GetEventFilter
// SDL_PeepEvents
// SDL_RemoveEventWatch
// SDL_SetEventFilter
