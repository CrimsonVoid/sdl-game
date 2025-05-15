#pragma once

#include <cstdint>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>

namespace sdl::events {
  struct Type {
    SDL_EventType ty;

    constexpr Type(uint32_t t) noexcept : ty(static_cast<SDL_EventType>(t)) {}

    constexpr operator SDL_EventType() const noexcept { return ty; }

    auto isEnabled(this Type self) -> bool { return SDL_EventEnabled(self.ty); }

    auto setEnabled(this Type self, bool enabled) -> void {
      SDL_SetEventEnabled(self.ty, enabled);
    };

    auto flush(this Type self) -> void { return SDL_FlushEvent(self.ty); }

    auto flushRange(this Type min, Type max) -> void { SDL_FlushEvents(min.ty, max.ty); }

    auto hasEvent(this Type self) -> bool { return SDL_HasEvent(self.ty); }

    auto hasEvents(this Type min, Type max) -> bool { return SDL_HasEvents(min.ty, max.ty); }
  };

  struct Event {
    SDL_Event* event;

    auto poll() -> bool { return SDL_PollEvent(event); }

    auto wait() -> bool { return SDL_WaitEvent(event); };

    auto waitTimeout(int32_t timeoutMS) -> bool { return SDL_WaitEventTimeout(event, timeoutMS); };

    [[nodiscard]] constexpr auto type() const noexcept -> Type { return event->type; }

    [[nodiscard]] auto getWindow() const -> SDL_Window* { return SDL_GetWindowFromEvent(event); }

    auto push() -> bool { return SDL_PushEvent(event); }

    static auto push(SDL_Event* event) -> bool { return SDL_PushEvent(event); }
  };

  inline void pump() { SDL_PumpEvents(); }

  inline auto push(SDL_Event* event) -> bool { return SDL_PushEvent(event); }

  inline auto registerEvents(int numevents) -> uint32_t { return SDL_RegisterEvents(numevents); }

  struct keyCode {
    SDL_Keycode code;
    constexpr keyCode(SDL_Keycode c) noexcept : code(c) {}
    constexpr operator SDL_Keycode() const noexcept { return code; }
  };

  struct scanCode {
    SDL_Scancode code;
    constexpr scanCode(SDL_Scancode c) noexcept : code(c) {}
    constexpr operator SDL_Scancode() const noexcept { return code; }
  };
} // namespace sdl::events

// todo: unimplemented
// SDL_AddEventWatch
// SDL_FilterEvents
// SDL_GetEventDescription
// SDL_GetEventFilter
// SDL_PeepEvents
// SDL_RemoveEventWatch
// SDL_SetEventFilter

namespace sdl::events {
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

  namespace ScanCode {
    static constexpr scanCode Unknown{SDL_SCANCODE_UNKNOWN};
    static constexpr scanCode A{SDL_SCANCODE_A};
    static constexpr scanCode B{SDL_SCANCODE_B};
    static constexpr scanCode C{SDL_SCANCODE_C};
    static constexpr scanCode D{SDL_SCANCODE_D};
    static constexpr scanCode E{SDL_SCANCODE_E};
    static constexpr scanCode F{SDL_SCANCODE_F};
    static constexpr scanCode G{SDL_SCANCODE_G};
    static constexpr scanCode H{SDL_SCANCODE_H};
    static constexpr scanCode I{SDL_SCANCODE_I};
    static constexpr scanCode J{SDL_SCANCODE_J};
    static constexpr scanCode K{SDL_SCANCODE_K};
    static constexpr scanCode L{SDL_SCANCODE_L};
    static constexpr scanCode M{SDL_SCANCODE_M};
    static constexpr scanCode N{SDL_SCANCODE_N};
    static constexpr scanCode O{SDL_SCANCODE_O};
    static constexpr scanCode P{SDL_SCANCODE_P};
    static constexpr scanCode Q{SDL_SCANCODE_Q};
    static constexpr scanCode R{SDL_SCANCODE_R};
    static constexpr scanCode S{SDL_SCANCODE_S};
    static constexpr scanCode T{SDL_SCANCODE_T};
    static constexpr scanCode U{SDL_SCANCODE_U};
    static constexpr scanCode V{SDL_SCANCODE_V};
    static constexpr scanCode W{SDL_SCANCODE_W};
    static constexpr scanCode X{SDL_SCANCODE_X};
    static constexpr scanCode Y{SDL_SCANCODE_Y};
    static constexpr scanCode Z{SDL_SCANCODE_Z};
    static constexpr scanCode _1{SDL_SCANCODE_1};
    static constexpr scanCode _2{SDL_SCANCODE_2};
    static constexpr scanCode _3{SDL_SCANCODE_3};
    static constexpr scanCode _4{SDL_SCANCODE_4};
    static constexpr scanCode _5{SDL_SCANCODE_5};
    static constexpr scanCode _6{SDL_SCANCODE_6};
    static constexpr scanCode _7{SDL_SCANCODE_7};
    static constexpr scanCode _8{SDL_SCANCODE_8};
    static constexpr scanCode _9{SDL_SCANCODE_9};
    static constexpr scanCode _0{SDL_SCANCODE_0};
    static constexpr scanCode Return{SDL_SCANCODE_RETURN};
    static constexpr scanCode Escape{SDL_SCANCODE_ESCAPE};
    static constexpr scanCode Backspace{SDL_SCANCODE_BACKSPACE};
    static constexpr scanCode Tab{SDL_SCANCODE_TAB};
    static constexpr scanCode Space{SDL_SCANCODE_SPACE};
    static constexpr scanCode Minus{SDL_SCANCODE_MINUS};
    static constexpr scanCode Equals{SDL_SCANCODE_EQUALS};
    static constexpr scanCode LeftBracket{SDL_SCANCODE_LEFTBRACKET};
    static constexpr scanCode RightBracket{SDL_SCANCODE_RIGHTBRACKET};
    static constexpr scanCode BackSlash{SDL_SCANCODE_BACKSLASH};
    static constexpr scanCode NonUsHash{SDL_SCANCODE_NONUSHASH};
    static constexpr scanCode Semicolon{SDL_SCANCODE_SEMICOLON};
    static constexpr scanCode Apostrophe{SDL_SCANCODE_APOSTROPHE};
    static constexpr scanCode Grave{SDL_SCANCODE_GRAVE};
    static constexpr scanCode Comma{SDL_SCANCODE_COMMA};
    static constexpr scanCode Period{SDL_SCANCODE_PERIOD};
    static constexpr scanCode Slash{SDL_SCANCODE_SLASH};
    static constexpr scanCode CapsLock{SDL_SCANCODE_CAPSLOCK};
    static constexpr scanCode F1{SDL_SCANCODE_F1};
    static constexpr scanCode F2{SDL_SCANCODE_F2};
    static constexpr scanCode F3{SDL_SCANCODE_F3};
    static constexpr scanCode F4{SDL_SCANCODE_F4};
    static constexpr scanCode F5{SDL_SCANCODE_F5};
    static constexpr scanCode F6{SDL_SCANCODE_F6};
    static constexpr scanCode F7{SDL_SCANCODE_F7};
    static constexpr scanCode F8{SDL_SCANCODE_F8};
    static constexpr scanCode F9{SDL_SCANCODE_F9};
    static constexpr scanCode F10{SDL_SCANCODE_F10};
    static constexpr scanCode F11{SDL_SCANCODE_F11};
    static constexpr scanCode F12{SDL_SCANCODE_F12};
    static constexpr scanCode PrintScreen{SDL_SCANCODE_PRINTSCREEN};
    static constexpr scanCode ScrollLock{SDL_SCANCODE_SCROLLLOCK};
    static constexpr scanCode Pause{SDL_SCANCODE_PAUSE};
    static constexpr scanCode Insert{SDL_SCANCODE_INSERT};
    static constexpr scanCode Home{SDL_SCANCODE_HOME};
    static constexpr scanCode Pageup{SDL_SCANCODE_PAGEUP};
    static constexpr scanCode Delete{SDL_SCANCODE_DELETE};
    static constexpr scanCode End{SDL_SCANCODE_END};
    static constexpr scanCode PageDown{SDL_SCANCODE_PAGEDOWN};
    static constexpr scanCode Right{SDL_SCANCODE_RIGHT};
    static constexpr scanCode Left{SDL_SCANCODE_LEFT};
    static constexpr scanCode Down{SDL_SCANCODE_DOWN};
    static constexpr scanCode Up{SDL_SCANCODE_UP};
    static constexpr scanCode NumLockClear{SDL_SCANCODE_NUMLOCKCLEAR};
    static constexpr scanCode KpDivide{SDL_SCANCODE_KP_DIVIDE};
    static constexpr scanCode KpMultiply{SDL_SCANCODE_KP_MULTIPLY};
    static constexpr scanCode KpMinus{SDL_SCANCODE_KP_MINUS};
    static constexpr scanCode KpPlus{SDL_SCANCODE_KP_PLUS};
    static constexpr scanCode KpEnter{SDL_SCANCODE_KP_ENTER};
    static constexpr scanCode Kp1{SDL_SCANCODE_KP_1};
    static constexpr scanCode Kp2{SDL_SCANCODE_KP_2};
    static constexpr scanCode Kp3{SDL_SCANCODE_KP_3};
    static constexpr scanCode Kp4{SDL_SCANCODE_KP_4};
    static constexpr scanCode Kp5{SDL_SCANCODE_KP_5};
    static constexpr scanCode Kp6{SDL_SCANCODE_KP_6};
    static constexpr scanCode Kp7{SDL_SCANCODE_KP_7};
    static constexpr scanCode Kp8{SDL_SCANCODE_KP_8};
    static constexpr scanCode Kp9{SDL_SCANCODE_KP_9};
    static constexpr scanCode Kp0{SDL_SCANCODE_KP_0};
    static constexpr scanCode KpPeriod{SDL_SCANCODE_KP_PERIOD};
    static constexpr scanCode NonUsBackslash{SDL_SCANCODE_NONUSBACKSLASH};
    static constexpr scanCode Application{SDL_SCANCODE_APPLICATION};
    static constexpr scanCode Power{SDL_SCANCODE_POWER};
    static constexpr scanCode KpEquals{SDL_SCANCODE_KP_EQUALS};
    static constexpr scanCode F13{SDL_SCANCODE_F13};
    static constexpr scanCode F14{SDL_SCANCODE_F14};
    static constexpr scanCode F15{SDL_SCANCODE_F15};
    static constexpr scanCode F16{SDL_SCANCODE_F16};
    static constexpr scanCode F17{SDL_SCANCODE_F17};
    static constexpr scanCode F18{SDL_SCANCODE_F18};
    static constexpr scanCode F19{SDL_SCANCODE_F19};
    static constexpr scanCode F20{SDL_SCANCODE_F20};
    static constexpr scanCode F21{SDL_SCANCODE_F21};
    static constexpr scanCode F22{SDL_SCANCODE_F22};
    static constexpr scanCode F23{SDL_SCANCODE_F23};
    static constexpr scanCode F24{SDL_SCANCODE_F24};
    static constexpr scanCode Execute{SDL_SCANCODE_EXECUTE};
    static constexpr scanCode Help{SDL_SCANCODE_HELP};
    static constexpr scanCode Menu{SDL_SCANCODE_MENU};
    static constexpr scanCode Select{SDL_SCANCODE_SELECT};
    static constexpr scanCode Stop{SDL_SCANCODE_STOP};
    static constexpr scanCode Again{SDL_SCANCODE_AGAIN};
    static constexpr scanCode Undo{SDL_SCANCODE_UNDO};
    static constexpr scanCode Cut{SDL_SCANCODE_CUT};
    static constexpr scanCode Copy{SDL_SCANCODE_COPY};
    static constexpr scanCode Paste{SDL_SCANCODE_PASTE};
    static constexpr scanCode Find{SDL_SCANCODE_FIND};
    static constexpr scanCode Mute{SDL_SCANCODE_MUTE};
    static constexpr scanCode Volumeup{SDL_SCANCODE_VOLUMEUP};
    static constexpr scanCode Volumedown{SDL_SCANCODE_VOLUMEDOWN};
    // static constexpr scanCode LockingCapsLock{SDL_SCANCODE_LOCKINGCAPSLOCK};
    // static constexpr scanCode LockingNumLock{SDL_SCANCODE_LOCKINGNUMLOCK};
    // static constexpr scanCode LockingScrollLock{SDL_SCANCODE_LOCKINGSCROLLLOCK};
    static constexpr scanCode KpComma{SDL_SCANCODE_KP_COMMA};
    static constexpr scanCode KpEqualsAs400{SDL_SCANCODE_KP_EQUALSAS400};
    static constexpr scanCode International1{SDL_SCANCODE_INTERNATIONAL1};
    static constexpr scanCode International2{SDL_SCANCODE_INTERNATIONAL2};
    static constexpr scanCode International3{SDL_SCANCODE_INTERNATIONAL3};
    static constexpr scanCode International4{SDL_SCANCODE_INTERNATIONAL4};
    static constexpr scanCode International5{SDL_SCANCODE_INTERNATIONAL5};
    static constexpr scanCode International6{SDL_SCANCODE_INTERNATIONAL6};
    static constexpr scanCode International7{SDL_SCANCODE_INTERNATIONAL7};
    static constexpr scanCode International8{SDL_SCANCODE_INTERNATIONAL8};
    static constexpr scanCode International9{SDL_SCANCODE_INTERNATIONAL9};
    static constexpr scanCode Lang1{SDL_SCANCODE_LANG1};
    static constexpr scanCode Lang2{SDL_SCANCODE_LANG2};
    static constexpr scanCode Lang3{SDL_SCANCODE_LANG3};
    static constexpr scanCode Lang4{SDL_SCANCODE_LANG4};
    static constexpr scanCode Lang5{SDL_SCANCODE_LANG5};
    static constexpr scanCode Lang6{SDL_SCANCODE_LANG6};
    static constexpr scanCode Lang7{SDL_SCANCODE_LANG7};
    static constexpr scanCode Lang8{SDL_SCANCODE_LANG8};
    static constexpr scanCode Lang9{SDL_SCANCODE_LANG9};
    static constexpr scanCode AltErase{SDL_SCANCODE_ALTERASE};
    static constexpr scanCode SysReq{SDL_SCANCODE_SYSREQ};
    static constexpr scanCode Cancel{SDL_SCANCODE_CANCEL};
    static constexpr scanCode Clear{SDL_SCANCODE_CLEAR};
    static constexpr scanCode Prior{SDL_SCANCODE_PRIOR};
    static constexpr scanCode Return2{SDL_SCANCODE_RETURN2};
    static constexpr scanCode Separator{SDL_SCANCODE_SEPARATOR};
    static constexpr scanCode Out{SDL_SCANCODE_OUT};
    static constexpr scanCode Oper{SDL_SCANCODE_OPER};
    static constexpr scanCode ClearAgain{SDL_SCANCODE_CLEARAGAIN};
    static constexpr scanCode Crsel{SDL_SCANCODE_CRSEL};
    static constexpr scanCode Exsel{SDL_SCANCODE_EXSEL};
    static constexpr scanCode Kp00{SDL_SCANCODE_KP_00};
    static constexpr scanCode Kp000{SDL_SCANCODE_KP_000};
    static constexpr scanCode ThousandsSeparator{SDL_SCANCODE_THOUSANDSSEPARATOR};
    static constexpr scanCode DecimalSeparator{SDL_SCANCODE_DECIMALSEPARATOR};
    static constexpr scanCode CurrencyUnit{SDL_SCANCODE_CURRENCYUNIT};
    static constexpr scanCode CurrencySubUnit{SDL_SCANCODE_CURRENCYSUBUNIT};
    static constexpr scanCode KpLeftParen{SDL_SCANCODE_KP_LEFTPAREN};
    static constexpr scanCode KpRightParen{SDL_SCANCODE_KP_RIGHTPAREN};
    static constexpr scanCode KpLeftBrace{SDL_SCANCODE_KP_LEFTBRACE};
    static constexpr scanCode KpRightBrace{SDL_SCANCODE_KP_RIGHTBRACE};
    static constexpr scanCode KpTab{SDL_SCANCODE_KP_TAB};
    static constexpr scanCode KpBackspace{SDL_SCANCODE_KP_BACKSPACE};
    static constexpr scanCode KpA{SDL_SCANCODE_KP_A};
    static constexpr scanCode KpB{SDL_SCANCODE_KP_B};
    static constexpr scanCode KpC{SDL_SCANCODE_KP_C};
    static constexpr scanCode KpD{SDL_SCANCODE_KP_D};
    static constexpr scanCode KpE{SDL_SCANCODE_KP_E};
    static constexpr scanCode KpF{SDL_SCANCODE_KP_F};
    static constexpr scanCode KpXor{SDL_SCANCODE_KP_XOR};
    static constexpr scanCode KpPower{SDL_SCANCODE_KP_POWER};
    static constexpr scanCode KpPercent{SDL_SCANCODE_KP_PERCENT};
    static constexpr scanCode KpLess{SDL_SCANCODE_KP_LESS};
    static constexpr scanCode KpGreater{SDL_SCANCODE_KP_GREATER};
    static constexpr scanCode KpAmpersand{SDL_SCANCODE_KP_AMPERSAND};
    static constexpr scanCode KpDblAmpersand{SDL_SCANCODE_KP_DBLAMPERSAND};
    static constexpr scanCode KpVerticalBar{SDL_SCANCODE_KP_VERTICALBAR};
    static constexpr scanCode KpDblverticalBar{SDL_SCANCODE_KP_DBLVERTICALBAR};
    static constexpr scanCode KpColon{SDL_SCANCODE_KP_COLON};
    static constexpr scanCode KpHash{SDL_SCANCODE_KP_HASH};
    static constexpr scanCode KpSpace{SDL_SCANCODE_KP_SPACE};
    static constexpr scanCode KpAt{SDL_SCANCODE_KP_AT};
    static constexpr scanCode KpExclam{SDL_SCANCODE_KP_EXCLAM};
    static constexpr scanCode KpMemStore{SDL_SCANCODE_KP_MEMSTORE};
    static constexpr scanCode KpMemRecall{SDL_SCANCODE_KP_MEMRECALL};
    static constexpr scanCode KpMemClear{SDL_SCANCODE_KP_MEMCLEAR};
    static constexpr scanCode KpMemAdd{SDL_SCANCODE_KP_MEMADD};
    static constexpr scanCode KpMemSubtract{SDL_SCANCODE_KP_MEMSUBTRACT};
    static constexpr scanCode KpMemMultiply{SDL_SCANCODE_KP_MEMMULTIPLY};
    static constexpr scanCode KpMemDivide{SDL_SCANCODE_KP_MEMDIVIDE};
    static constexpr scanCode KpPlusMinus{SDL_SCANCODE_KP_PLUSMINUS};
    static constexpr scanCode KpClear{SDL_SCANCODE_KP_CLEAR};
    static constexpr scanCode KpClearEntry{SDL_SCANCODE_KP_CLEARENTRY};
    static constexpr scanCode KpBinary{SDL_SCANCODE_KP_BINARY};
    static constexpr scanCode KpOctal{SDL_SCANCODE_KP_OCTAL};
    static constexpr scanCode KpDecimal{SDL_SCANCODE_KP_DECIMAL};
    static constexpr scanCode KpHexadecimal{SDL_SCANCODE_KP_HEXADECIMAL};
    static constexpr scanCode LCtrl{SDL_SCANCODE_LCTRL};
    static constexpr scanCode LShift{SDL_SCANCODE_LSHIFT};
    static constexpr scanCode LAlt{SDL_SCANCODE_LALT};
    static constexpr scanCode LGui{SDL_SCANCODE_LGUI};
    static constexpr scanCode RCtrl{SDL_SCANCODE_RCTRL};
    static constexpr scanCode RShift{SDL_SCANCODE_RSHIFT};
    static constexpr scanCode RAlt{SDL_SCANCODE_RALT};
    static constexpr scanCode RGui{SDL_SCANCODE_RGUI};
    static constexpr scanCode Mode{SDL_SCANCODE_MODE};
    static constexpr scanCode Sleep{SDL_SCANCODE_SLEEP};
    static constexpr scanCode Wake{SDL_SCANCODE_WAKE};
    static constexpr scanCode ChannelIncrement{SDL_SCANCODE_CHANNEL_INCREMENT};
    static constexpr scanCode ChannelDecrement{SDL_SCANCODE_CHANNEL_DECREMENT};
    static constexpr scanCode MediaPlay{SDL_SCANCODE_MEDIA_PLAY};
    static constexpr scanCode MediaPause{SDL_SCANCODE_MEDIA_PAUSE};
    static constexpr scanCode MediaRecord{SDL_SCANCODE_MEDIA_RECORD};
    static constexpr scanCode MediaFastForward{SDL_SCANCODE_MEDIA_FAST_FORWARD};
    static constexpr scanCode MediaRewind{SDL_SCANCODE_MEDIA_REWIND};
    static constexpr scanCode MediaNextTrack{SDL_SCANCODE_MEDIA_NEXT_TRACK};
    static constexpr scanCode MediaPreviousTrack{SDL_SCANCODE_MEDIA_PREVIOUS_TRACK};
    static constexpr scanCode MediaStop{SDL_SCANCODE_MEDIA_STOP};
    static constexpr scanCode MediaEject{SDL_SCANCODE_MEDIA_EJECT};
    static constexpr scanCode MediaPlayPause{SDL_SCANCODE_MEDIA_PLAY_PAUSE};
    static constexpr scanCode MediaSelect{SDL_SCANCODE_MEDIA_SELECT};
    static constexpr scanCode AcNew{SDL_SCANCODE_AC_NEW};
    static constexpr scanCode AcOpen{SDL_SCANCODE_AC_OPEN};
    static constexpr scanCode AcClose{SDL_SCANCODE_AC_CLOSE};
    static constexpr scanCode AcExit{SDL_SCANCODE_AC_EXIT};
    static constexpr scanCode AcSave{SDL_SCANCODE_AC_SAVE};
    static constexpr scanCode AcPrint{SDL_SCANCODE_AC_PRINT};
    static constexpr scanCode AcProperties{SDL_SCANCODE_AC_PROPERTIES};
    static constexpr scanCode AcSearch{SDL_SCANCODE_AC_SEARCH};
    static constexpr scanCode AcHome{SDL_SCANCODE_AC_HOME};
    static constexpr scanCode AcBack{SDL_SCANCODE_AC_BACK};
    static constexpr scanCode AcForward{SDL_SCANCODE_AC_FORWARD};
    static constexpr scanCode AcStop{SDL_SCANCODE_AC_STOP};
    static constexpr scanCode AcRefresh{SDL_SCANCODE_AC_REFRESH};
    static constexpr scanCode AcBookmarks{SDL_SCANCODE_AC_BOOKMARKS};
    static constexpr scanCode SoftLeft{SDL_SCANCODE_SOFTLEFT};
    static constexpr scanCode SoftRight{SDL_SCANCODE_SOFTRIGHT};
    static constexpr scanCode Call{SDL_SCANCODE_CALL};
    static constexpr scanCode EndCall{SDL_SCANCODE_ENDCALL};
    static constexpr scanCode Reserved{SDL_SCANCODE_RESERVED};
    static constexpr scanCode Count{SDL_SCANCODE_COUNT};
  }; // namespace ScanCode

  namespace KeyCode {
    static constexpr keyCode Unknown{SDLK_UNKNOWN};
    static constexpr keyCode Return{SDLK_RETURN};
    static constexpr keyCode Escape{SDLK_ESCAPE};
    static constexpr keyCode Backspace{SDLK_BACKSPACE};
    static constexpr keyCode Tab{SDLK_TAB};
    static constexpr keyCode Space{SDLK_SPACE};
    static constexpr keyCode Exclaim{SDLK_EXCLAIM};
    static constexpr keyCode DblApostrophe{SDLK_DBLAPOSTROPHE};
    static constexpr keyCode Hash{SDLK_HASH};
    static constexpr keyCode Dollar{SDLK_DOLLAR};
    static constexpr keyCode Percent{SDLK_PERCENT};
    static constexpr keyCode Ampersand{SDLK_AMPERSAND};
    static constexpr keyCode Apostrophe{SDLK_APOSTROPHE};
    static constexpr keyCode LeftParen{SDLK_LEFTPAREN};
    static constexpr keyCode RightParen{SDLK_RIGHTPAREN};
    static constexpr keyCode Asterisk{SDLK_ASTERISK};
    static constexpr keyCode Plus{SDLK_PLUS};
    static constexpr keyCode Comma{SDLK_COMMA};
    static constexpr keyCode Minus{SDLK_MINUS};
    static constexpr keyCode Period{SDLK_PERIOD};
    static constexpr keyCode Slash{SDLK_SLASH};
    static constexpr keyCode _0{SDLK_0};
    static constexpr keyCode _1{SDLK_1};
    static constexpr keyCode _2{SDLK_2};
    static constexpr keyCode _3{SDLK_3};
    static constexpr keyCode _4{SDLK_4};
    static constexpr keyCode _5{SDLK_5};
    static constexpr keyCode _6{SDLK_6};
    static constexpr keyCode _7{SDLK_7};
    static constexpr keyCode _8{SDLK_8};
    static constexpr keyCode _9{SDLK_9};
    static constexpr keyCode Colon{SDLK_COLON};
    static constexpr keyCode Semicolon{SDLK_SEMICOLON};
    static constexpr keyCode Less{SDLK_LESS};
    static constexpr keyCode Equals{SDLK_EQUALS};
    static constexpr keyCode Greater{SDLK_GREATER};
    static constexpr keyCode Question{SDLK_QUESTION};
    static constexpr keyCode At{SDLK_AT};
    static constexpr keyCode LeftBracket{SDLK_LEFTBRACKET};
    static constexpr keyCode Backslash{SDLK_BACKSLASH};
    static constexpr keyCode RightBracket{SDLK_RIGHTBRACKET};
    static constexpr keyCode Caret{SDLK_CARET};
    static constexpr keyCode Underscore{SDLK_UNDERSCORE};
    static constexpr keyCode Grave{SDLK_GRAVE};
    static constexpr keyCode A{SDLK_A};
    static constexpr keyCode B{SDLK_B};
    static constexpr keyCode C{SDLK_C};
    static constexpr keyCode D{SDLK_D};
    static constexpr keyCode E{SDLK_E};
    static constexpr keyCode F{SDLK_F};
    static constexpr keyCode G{SDLK_G};
    static constexpr keyCode H{SDLK_H};
    static constexpr keyCode I{SDLK_I};
    static constexpr keyCode J{SDLK_J};
    static constexpr keyCode K{SDLK_K};
    static constexpr keyCode L{SDLK_L};
    static constexpr keyCode M{SDLK_M};
    static constexpr keyCode N{SDLK_N};
    static constexpr keyCode O{SDLK_O};
    static constexpr keyCode P{SDLK_P};
    static constexpr keyCode Q{SDLK_Q};
    static constexpr keyCode R{SDLK_R};
    static constexpr keyCode S{SDLK_S};
    static constexpr keyCode T{SDLK_T};
    static constexpr keyCode U{SDLK_U};
    static constexpr keyCode V{SDLK_V};
    static constexpr keyCode W{SDLK_W};
    static constexpr keyCode X{SDLK_X};
    static constexpr keyCode Y{SDLK_Y};
    static constexpr keyCode Z{SDLK_Z};
    static constexpr keyCode LeftBrace{SDLK_LEFTBRACE};
    static constexpr keyCode Pipe{SDLK_PIPE};
    static constexpr keyCode RightBrace{SDLK_RIGHTBRACE};
    static constexpr keyCode Tilde{SDLK_TILDE};
    static constexpr keyCode Delete{SDLK_DELETE};
    static constexpr keyCode PlusMinus{SDLK_PLUSMINUS};
    static constexpr keyCode CapsMock{SDLK_CAPSLOCK};
    static constexpr keyCode F1{SDLK_F1};
    static constexpr keyCode F2{SDLK_F2};
    static constexpr keyCode F3{SDLK_F3};
    static constexpr keyCode F4{SDLK_F4};
    static constexpr keyCode F5{SDLK_F5};
    static constexpr keyCode F6{SDLK_F6};
    static constexpr keyCode F7{SDLK_F7};
    static constexpr keyCode F8{SDLK_F8};
    static constexpr keyCode F9{SDLK_F9};
    static constexpr keyCode F10{SDLK_F10};
    static constexpr keyCode F11{SDLK_F11};
    static constexpr keyCode F12{SDLK_F12};
    static constexpr keyCode PrintScreen{SDLK_PRINTSCREEN};
    static constexpr keyCode ScrollLock{SDLK_SCROLLLOCK};
    static constexpr keyCode Pause{SDLK_PAUSE};
    static constexpr keyCode Insert{SDLK_INSERT};
    static constexpr keyCode Home{SDLK_HOME};
    static constexpr keyCode Pageup{SDLK_PAGEUP};
    static constexpr keyCode End{SDLK_END};
    static constexpr keyCode PageDown{SDLK_PAGEDOWN};
    static constexpr keyCode Right{SDLK_RIGHT};
    static constexpr keyCode Left{SDLK_LEFT};
    static constexpr keyCode Down{SDLK_DOWN};
    static constexpr keyCode Up{SDLK_UP};
    static constexpr keyCode NumLockClear{SDLK_NUMLOCKCLEAR};
    static constexpr keyCode KpDivide{SDLK_KP_DIVIDE};
    static constexpr keyCode KpMultiply{SDLK_KP_MULTIPLY};
    static constexpr keyCode KpMinus{SDLK_KP_MINUS};
    static constexpr keyCode KpPlus{SDLK_KP_PLUS};
    static constexpr keyCode KpEnter{SDLK_KP_ENTER};
    static constexpr keyCode Kp1{SDLK_KP_1};
    static constexpr keyCode Kp2{SDLK_KP_2};
    static constexpr keyCode Kp3{SDLK_KP_3};
    static constexpr keyCode Kp4{SDLK_KP_4};
    static constexpr keyCode Kp5{SDLK_KP_5};
    static constexpr keyCode Kp6{SDLK_KP_6};
    static constexpr keyCode Kp7{SDLK_KP_7};
    static constexpr keyCode Kp8{SDLK_KP_8};
    static constexpr keyCode Kp9{SDLK_KP_9};
    static constexpr keyCode Kp0{SDLK_KP_0};
    static constexpr keyCode KpPeriod{SDLK_KP_PERIOD};
    static constexpr keyCode Application{SDLK_APPLICATION};
    static constexpr keyCode Power{SDLK_POWER};
    static constexpr keyCode KpEquals{SDLK_KP_EQUALS};
    static constexpr keyCode F13{SDLK_F13};
    static constexpr keyCode F14{SDLK_F14};
    static constexpr keyCode F15{SDLK_F15};
    static constexpr keyCode F16{SDLK_F16};
    static constexpr keyCode F17{SDLK_F17};
    static constexpr keyCode F18{SDLK_F18};
    static constexpr keyCode F19{SDLK_F19};
    static constexpr keyCode F20{SDLK_F20};
    static constexpr keyCode F21{SDLK_F21};
    static constexpr keyCode F22{SDLK_F22};
    static constexpr keyCode F23{SDLK_F23};
    static constexpr keyCode F24{SDLK_F24};
    static constexpr keyCode Execute{SDLK_EXECUTE};
    static constexpr keyCode Help{SDLK_HELP};
    static constexpr keyCode Menu{SDLK_MENU};
    static constexpr keyCode Select{SDLK_SELECT};
    static constexpr keyCode Stop{SDLK_STOP};
    static constexpr keyCode Again{SDLK_AGAIN};
    static constexpr keyCode Undo{SDLK_UNDO};
    static constexpr keyCode Cut{SDLK_CUT};
    static constexpr keyCode Copy{SDLK_COPY};
    static constexpr keyCode Paste{SDLK_PASTE};
    static constexpr keyCode Find{SDLK_FIND};
    static constexpr keyCode Mute{SDLK_MUTE};
    static constexpr keyCode VolumeUp{SDLK_VOLUMEUP};
    static constexpr keyCode VolumeDown{SDLK_VOLUMEDOWN};
    static constexpr keyCode KpComma{SDLK_KP_COMMA};
    static constexpr keyCode KpEqualsAs400{SDLK_KP_EQUALSAS400};
    static constexpr keyCode AltErase{SDLK_ALTERASE};
    static constexpr keyCode SysReq{SDLK_SYSREQ};
    static constexpr keyCode Cancel{SDLK_CANCEL};
    static constexpr keyCode Clear{SDLK_CLEAR};
    static constexpr keyCode Prior{SDLK_PRIOR};
    static constexpr keyCode Return2{SDLK_RETURN2};
    static constexpr keyCode Separator{SDLK_SEPARATOR};
    static constexpr keyCode Out{SDLK_OUT};
    static constexpr keyCode Oper{SDLK_OPER};
    static constexpr keyCode ClearAgain{SDLK_CLEARAGAIN};
    static constexpr keyCode Crsel{SDLK_CRSEL};
    static constexpr keyCode Exsel{SDLK_EXSEL};
    static constexpr keyCode Kp00{SDLK_KP_00};
    static constexpr keyCode Kp000{SDLK_KP_000};
    static constexpr keyCode ThousandsSeparator{SDLK_THOUSANDSSEPARATOR};
    static constexpr keyCode DecimalSeparator{SDLK_DECIMALSEPARATOR};
    static constexpr keyCode CurrencyUnit{SDLK_CURRENCYUNIT};
    static constexpr keyCode CurrencySubunit{SDLK_CURRENCYSUBUNIT};
    static constexpr keyCode KpLeftparen{SDLK_KP_LEFTPAREN};
    static constexpr keyCode KpRightparen{SDLK_KP_RIGHTPAREN};
    static constexpr keyCode KpLeftbrace{SDLK_KP_LEFTBRACE};
    static constexpr keyCode KpRightbrace{SDLK_KP_RIGHTBRACE};
    static constexpr keyCode KpTab{SDLK_KP_TAB};
    static constexpr keyCode KpBackspace{SDLK_KP_BACKSPACE};
    static constexpr keyCode KpA{SDLK_KP_A};
    static constexpr keyCode KpB{SDLK_KP_B};
    static constexpr keyCode KpC{SDLK_KP_C};
    static constexpr keyCode KpD{SDLK_KP_D};
    static constexpr keyCode KpE{SDLK_KP_E};
    static constexpr keyCode KpF{SDLK_KP_F};
    static constexpr keyCode KpXor{SDLK_KP_XOR};
    static constexpr keyCode KpPower{SDLK_KP_POWER};
    static constexpr keyCode KpPercent{SDLK_KP_PERCENT};
    static constexpr keyCode KpLess{SDLK_KP_LESS};
    static constexpr keyCode KpGreater{SDLK_KP_GREATER};
    static constexpr keyCode KpAmpersand{SDLK_KP_AMPERSAND};
    static constexpr keyCode KpDblAmpersand{SDLK_KP_DBLAMPERSAND};
    static constexpr keyCode KpVerticalBar{SDLK_KP_VERTICALBAR};
    static constexpr keyCode KpDblverticalBar{SDLK_KP_DBLVERTICALBAR};
    static constexpr keyCode KpColon{SDLK_KP_COLON};
    static constexpr keyCode KpHash{SDLK_KP_HASH};
    static constexpr keyCode KpSpace{SDLK_KP_SPACE};
    static constexpr keyCode KpAt{SDLK_KP_AT};
    static constexpr keyCode KpExclam{SDLK_KP_EXCLAM};
    static constexpr keyCode KpMemStore{SDLK_KP_MEMSTORE};
    static constexpr keyCode KpMemRecall{SDLK_KP_MEMRECALL};
    static constexpr keyCode KpMemClear{SDLK_KP_MEMCLEAR};
    static constexpr keyCode KpMemAdd{SDLK_KP_MEMADD};
    static constexpr keyCode KpMemSubtract{SDLK_KP_MEMSUBTRACT};
    static constexpr keyCode KpMemMultiply{SDLK_KP_MEMMULTIPLY};
    static constexpr keyCode KpMemDivide{SDLK_KP_MEMDIVIDE};
    static constexpr keyCode KpPlusMinus{SDLK_KP_PLUSMINUS};
    static constexpr keyCode KpClear{SDLK_KP_CLEAR};
    static constexpr keyCode KpClearEntry{SDLK_KP_CLEARENTRY};
    static constexpr keyCode KpBinary{SDLK_KP_BINARY};
    static constexpr keyCode KpOctal{SDLK_KP_OCTAL};
    static constexpr keyCode KpDecimal{SDLK_KP_DECIMAL};
    static constexpr keyCode KpHexadecimal{SDLK_KP_HEXADECIMAL};
    static constexpr keyCode LCtrl{SDLK_LCTRL};
    static constexpr keyCode LShift{SDLK_LSHIFT};
    static constexpr keyCode LAlt{SDLK_LALT};
    static constexpr keyCode LGui{SDLK_LGUI};
    static constexpr keyCode RCtrl{SDLK_RCTRL};
    static constexpr keyCode RShift{SDLK_RSHIFT};
    static constexpr keyCode RAlt{SDLK_RALT};
    static constexpr keyCode RGui{SDLK_RGUI};
    static constexpr keyCode Mode{SDLK_MODE};
    static constexpr keyCode Sleep{SDLK_SLEEP};
    static constexpr keyCode Wake{SDLK_WAKE};
    static constexpr keyCode ChannelIncrement{SDLK_CHANNEL_INCREMENT};
    static constexpr keyCode ChannelDecrement{SDLK_CHANNEL_DECREMENT};
    static constexpr keyCode MediaPlay{SDLK_MEDIA_PLAY};
    static constexpr keyCode MediaPause{SDLK_MEDIA_PAUSE};
    static constexpr keyCode MediaRecord{SDLK_MEDIA_RECORD};
    static constexpr keyCode MediaFastForward{SDLK_MEDIA_FAST_FORWARD};
    static constexpr keyCode MediaRewind{SDLK_MEDIA_REWIND};
    static constexpr keyCode MediaNextTrack{SDLK_MEDIA_NEXT_TRACK};
    static constexpr keyCode MediaPreviousTrack{SDLK_MEDIA_PREVIOUS_TRACK};
    static constexpr keyCode MediaStop{SDLK_MEDIA_STOP};
    static constexpr keyCode MediaEject{SDLK_MEDIA_EJECT};
    static constexpr keyCode MediaPlayPause{SDLK_MEDIA_PLAY_PAUSE};
    static constexpr keyCode MediaSelect{SDLK_MEDIA_SELECT};
    static constexpr keyCode AcNew{SDLK_AC_NEW};
    static constexpr keyCode AcOpen{SDLK_AC_OPEN};
    static constexpr keyCode AcClose{SDLK_AC_CLOSE};
    static constexpr keyCode AcExit{SDLK_AC_EXIT};
    static constexpr keyCode AcSave{SDLK_AC_SAVE};
    static constexpr keyCode AcPrint{SDLK_AC_PRINT};
    static constexpr keyCode AcProperties{SDLK_AC_PROPERTIES};
    static constexpr keyCode AcSearch{SDLK_AC_SEARCH};
    static constexpr keyCode AcHome{SDLK_AC_HOME};
    static constexpr keyCode AcHack{SDLK_AC_BACK};
    static constexpr keyCode AcForward{SDLK_AC_FORWARD};
    static constexpr keyCode AcStop{SDLK_AC_STOP};
    static constexpr keyCode AcRefresh{SDLK_AC_REFRESH};
    static constexpr keyCode AcBookmarks{SDLK_AC_BOOKMARKS};
    static constexpr keyCode SoftLeft{SDLK_SOFTLEFT};
    static constexpr keyCode SoftRight{SDLK_SOFTRIGHT};
    static constexpr keyCode Call{SDLK_CALL};
    static constexpr keyCode EndCall{SDLK_ENDCALL};
    static constexpr keyCode LeftTab{SDLK_LEFT_TAB};
    static constexpr keyCode Level5Shift{SDLK_LEVEL5_SHIFT};
    static constexpr keyCode MultiKeyCompose{SDLK_MULTI_KEY_COMPOSE};
    static constexpr keyCode LMeta{SDLK_LMETA};
    static constexpr keyCode RMeta{SDLK_RMETA};
    static constexpr keyCode LHyper{SDLK_LHYPER};
    static constexpr keyCode RHyper{SDLK_RHYPER};
  }; // namespace KeyCode
} // namespace sdl::events
