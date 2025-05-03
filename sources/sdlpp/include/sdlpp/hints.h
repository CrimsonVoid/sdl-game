#pragma once

#include <type_traits>

#include <SDL3/SDL_hints.h>

namespace sdl::hints {
  inline void resetAll() { return SDL_ResetHints(); }

  enum struct Priority : std::underlying_type_t<SDL_HintPriority> {
    Default = SDL_HINT_DEFAULT,
    Normal = SDL_HINT_NORMAL,
    Override = SDL_HINT_OVERRIDE,
  };

  struct Hint {
    const char* name;

    inline const char* get() const { return SDL_GetHint(name); }

    inline bool getBool(bool defaultVal) const { return SDL_GetHintBoolean(name, defaultVal); }

    inline bool reset() const { return SDL_ResetHint(name); }

    inline bool set(const char* val, Priority prio = Priority::Normal) const {
      return SDL_SetHintWithPriority(name, val, static_cast<SDL_HintPriority>(prio));
    }
  };

  // clang-format off
  static constexpr Hint AllowAltTabWhileGrabbed{SDL_HINT_ALLOW_ALT_TAB_WHILE_GRABBED};
  static constexpr Hint AndroidAllowRecreateActivity{SDL_HINT_ANDROID_ALLOW_RECREATE_ACTIVITY};
  static constexpr Hint AndroidBlockOnPause{SDL_HINT_ANDROID_BLOCK_ON_PAUSE};
  static constexpr Hint AndroidLowLatencyAudio{SDL_HINT_ANDROID_LOW_LATENCY_AUDIO};
  static constexpr Hint AndroidTrapBackButton{SDL_HINT_ANDROID_TRAP_BACK_BUTTON};
  static constexpr Hint AppId{SDL_HINT_APP_ID};
  static constexpr Hint AppName{SDL_HINT_APP_NAME};
  static constexpr Hint AppleTvControllerUiEvents{SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS};
  static constexpr Hint AppleTvRemoteAllowRotation{SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION};
  static constexpr Hint Assert{SDL_HINT_ASSERT};
  static constexpr Hint AudioAlsaDefaultDevice{SDL_HINT_AUDIO_ALSA_DEFAULT_DEVICE};
  static constexpr Hint AudioAlsaDefaultPlaybackDevice{SDL_HINT_AUDIO_ALSA_DEFAULT_PLAYBACK_DEVICE};
  static constexpr Hint AudioAlsaDefaultRecordingDevice{SDL_HINT_AUDIO_ALSA_DEFAULT_RECORDING_DEVICE};
  static constexpr Hint AudioCategory{SDL_HINT_AUDIO_CATEGORY};
  static constexpr Hint AudioChannels{SDL_HINT_AUDIO_CHANNELS};
  static constexpr Hint AudioDeviceAppIconName{SDL_HINT_AUDIO_DEVICE_APP_ICON_NAME};
  static constexpr Hint AudioDeviceSampleFrames{SDL_HINT_AUDIO_DEVICE_SAMPLE_FRAMES};
  static constexpr Hint AudioDeviceStreamName{SDL_HINT_AUDIO_DEVICE_STREAM_NAME};
  static constexpr Hint AudioDeviceStreamRole{SDL_HINT_AUDIO_DEVICE_STREAM_ROLE};
  static constexpr Hint AudioDiskInputFile{SDL_HINT_AUDIO_DISK_INPUT_FILE};
  static constexpr Hint AudioDiskOutputFile{SDL_HINT_AUDIO_DISK_OUTPUT_FILE};
  static constexpr Hint AudioDiskTimescale{SDL_HINT_AUDIO_DISK_TIMESCALE};
  static constexpr Hint AudioDriver{SDL_HINT_AUDIO_DRIVER};
  static constexpr Hint AudioDummyTimescale{SDL_HINT_AUDIO_DUMMY_TIMESCALE};
  static constexpr Hint AudioFormat{SDL_HINT_AUDIO_FORMAT};
  static constexpr Hint AudioFrequency{SDL_HINT_AUDIO_FREQUENCY};
  static constexpr Hint AudioIncludeMonitors{SDL_HINT_AUDIO_INCLUDE_MONITORS};
  static constexpr Hint AutoUpdateJoysticks{SDL_HINT_AUTO_UPDATE_JOYSTICKS};
  static constexpr Hint AutoUpdateSensors{SDL_HINT_AUTO_UPDATE_SENSORS};
  static constexpr Hint BmpSaveLegacyFormat{SDL_HINT_BMP_SAVE_LEGACY_FORMAT};
  static constexpr Hint CameraDriver{SDL_HINT_CAMERA_DRIVER};
  static constexpr Hint CpuFeatureMask{SDL_HINT_CPU_FEATURE_MASK};
  static constexpr Hint DisplayUsableBounds{SDL_HINT_DISPLAY_USABLE_BOUNDS};
  static constexpr Hint EglLibrary{SDL_HINT_EGL_LIBRARY};
  static constexpr Hint EmscriptenAsyncify{SDL_HINT_EMSCRIPTEN_ASYNCIFY};
  static constexpr Hint EmscriptenCanvasSelector{SDL_HINT_EMSCRIPTEN_CANVAS_SELECTOR};
  static constexpr Hint EmscriptenKeyboardElement{SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT};
  static constexpr Hint EnableScreenKeyboard{SDL_HINT_ENABLE_SCREEN_KEYBOARD};
  static constexpr Hint EvdevDevices{SDL_HINT_EVDEV_DEVICES};
  static constexpr Hint EventLogging{SDL_HINT_EVENT_LOGGING};
  static constexpr Hint FileDialogDriver{SDL_HINT_FILE_DIALOG_DRIVER};
  static constexpr Hint ForceRaisewindow{SDL_HINT_FORCE_RAISEWINDOW};
  static constexpr Hint FramebufferAcceleration{SDL_HINT_FRAMEBUFFER_ACCELERATION};
  static constexpr Hint GamecontrollerIgnoreDevices{SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES};
  static constexpr Hint GamecontrollerIgnoreDevicesExcept{SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT};
  static constexpr Hint GamecontrollerSensorFusion{SDL_HINT_GAMECONTROLLER_SENSOR_FUSION};
  static constexpr Hint Gamecontrollerconfig{SDL_HINT_GAMECONTROLLERCONFIG};
  static constexpr Hint GamecontrollerconfigFile{SDL_HINT_GAMECONTROLLERCONFIG_FILE};
  static constexpr Hint Gamecontrollertype{SDL_HINT_GAMECONTROLLERTYPE};
  static constexpr Hint GdkTextinputDefaultText{SDL_HINT_GDK_TEXTINPUT_DEFAULT_TEXT};
  static constexpr Hint GdkTextinputDescription{SDL_HINT_GDK_TEXTINPUT_DESCRIPTION};
  static constexpr Hint GdkTextinputMaxLength{SDL_HINT_GDK_TEXTINPUT_MAX_LENGTH};
  static constexpr Hint GdkTextinputScope{SDL_HINT_GDK_TEXTINPUT_SCOPE};
  static constexpr Hint GdkTextinputTitle{SDL_HINT_GDK_TEXTINPUT_TITLE};
  static constexpr Hint GpuDriver{SDL_HINT_GPU_DRIVER};
  static constexpr Hint HidapiEnumerateOnlyControllers{SDL_HINT_HIDAPI_ENUMERATE_ONLY_CONTROLLERS};
  static constexpr Hint HidapiIgnoreDevices{SDL_HINT_HIDAPI_IGNORE_DEVICES};
  static constexpr Hint HidapiLibusb{SDL_HINT_HIDAPI_LIBUSB};
  static constexpr Hint HidapiLibusbWhitelist{SDL_HINT_HIDAPI_LIBUSB_WHITELIST};
  static constexpr Hint HidapiUdev{SDL_HINT_HIDAPI_UDEV};
  static constexpr Hint ImeImplementedUi{SDL_HINT_IME_IMPLEMENTED_UI};
  static constexpr Hint IosHideHomeIndicator{SDL_HINT_IOS_HIDE_HOME_INDICATOR};
  static constexpr Hint JoystickAllowBackgroundEvents{SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS};
  static constexpr Hint JoystickArcadestickDevices{SDL_HINT_JOYSTICK_ARCADESTICK_DEVICES};
  static constexpr Hint JoystickArcadestickDevicesExcluded{SDL_HINT_JOYSTICK_ARCADESTICK_DEVICES_EXCLUDED};
  static constexpr Hint JoystickBlacklistDevices{SDL_HINT_JOYSTICK_BLACKLIST_DEVICES};
  static constexpr Hint JoystickBlacklistDevicesExcluded{SDL_HINT_JOYSTICK_BLACKLIST_DEVICES_EXCLUDED};
  static constexpr Hint JoystickDevice{SDL_HINT_JOYSTICK_DEVICE};
  static constexpr Hint JoystickDirectinput{SDL_HINT_JOYSTICK_DIRECTINPUT};
  static constexpr Hint JoystickEnhancedReports{SDL_HINT_JOYSTICK_ENHANCED_REPORTS};
  static constexpr Hint JoystickFlightstickDevices{SDL_HINT_JOYSTICK_FLIGHTSTICK_DEVICES};
  static constexpr Hint JoystickFlightstickDevicesExcluded{SDL_HINT_JOYSTICK_FLIGHTSTICK_DEVICES_EXCLUDED};
  static constexpr Hint JoystickGamecubeDevices{SDL_HINT_JOYSTICK_GAMECUBE_DEVICES};
  static constexpr Hint JoystickGamecubeDevicesExcluded{SDL_HINT_JOYSTICK_GAMECUBE_DEVICES_EXCLUDED};
  static constexpr Hint JoystickGameinput{SDL_HINT_JOYSTICK_GAMEINPUT};
  static constexpr Hint JoystickHapticAxes{SDL_HINT_JOYSTICK_HAPTIC_AXES};
  static constexpr Hint JoystickHidapi{SDL_HINT_JOYSTICK_HIDAPI};
  // static constexpr Hint JoystickHidapi8bitdo{SDL_HINT_JOYSTICK_HIDAPI_8BITDO};
  static constexpr Hint JoystickHidapiCombineJoyCons{SDL_HINT_JOYSTICK_HIDAPI_COMBINE_JOY_CONS};
  static constexpr Hint JoystickHidapiGamecube{SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE};
  static constexpr Hint JoystickHidapiGamecubeRumbleBrake{SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE_RUMBLE_BRAKE};
  // static constexpr Hint JoystickHidapiGip{SDL_HINT_JOYSTICK_HIDAPI_GIP};
  // static constexpr Hint JoystickHidapiGipResetForMetadata{SDL_HINT_JOYSTICK_HIDAPI_GIP_RESET_FOR_METADATA};
  static constexpr Hint JoystickHidapiJoyCons{SDL_HINT_JOYSTICK_HIDAPI_JOY_CONS};
  static constexpr Hint JoystickHidapiJoyconHomeLed{SDL_HINT_JOYSTICK_HIDAPI_JOYCON_HOME_LED};
  // static constexpr Hint JoystickHidapiLg4ff{SDL_HINT_JOYSTICK_HIDAPI_LG4FF};
  static constexpr Hint JoystickHidapiLuna{SDL_HINT_JOYSTICK_HIDAPI_LUNA};
  static constexpr Hint JoystickHidapiNintendoClassic{SDL_HINT_JOYSTICK_HIDAPI_NINTENDO_CLASSIC};
  static constexpr Hint JoystickHidapiPs3{SDL_HINT_JOYSTICK_HIDAPI_PS3};
  static constexpr Hint JoystickHidapiPs3SixaxisDriver{SDL_HINT_JOYSTICK_HIDAPI_PS3_SIXAXIS_DRIVER};
  static constexpr Hint JoystickHidapiPs4{SDL_HINT_JOYSTICK_HIDAPI_PS4};
  static constexpr Hint JoystickHidapiPs4ReportInterval{SDL_HINT_JOYSTICK_HIDAPI_PS4_REPORT_INTERVAL};
  static constexpr Hint JoystickHidapiPs5{SDL_HINT_JOYSTICK_HIDAPI_PS5};
  static constexpr Hint JoystickHidapiPs5PlayerLed{SDL_HINT_JOYSTICK_HIDAPI_PS5_PLAYER_LED};
  static constexpr Hint JoystickHidapiShield{SDL_HINT_JOYSTICK_HIDAPI_SHIELD};
  static constexpr Hint JoystickHidapiStadia{SDL_HINT_JOYSTICK_HIDAPI_STADIA};
  static constexpr Hint JoystickHidapiSteam{SDL_HINT_JOYSTICK_HIDAPI_STEAM};
  static constexpr Hint JoystickHidapiSteamHomeLed{SDL_HINT_JOYSTICK_HIDAPI_STEAM_HOME_LED};
  static constexpr Hint JoystickHidapiSteamHori{SDL_HINT_JOYSTICK_HIDAPI_STEAM_HORI};
  static constexpr Hint JoystickHidapiSteamdeck{SDL_HINT_JOYSTICK_HIDAPI_STEAMDECK};
  static constexpr Hint JoystickHidapiSwitch{SDL_HINT_JOYSTICK_HIDAPI_SWITCH};
  static constexpr Hint JoystickHidapiSwitchHomeLed{SDL_HINT_JOYSTICK_HIDAPI_SWITCH_HOME_LED};
  static constexpr Hint JoystickHidapiSwitchPlayerLed{SDL_HINT_JOYSTICK_HIDAPI_SWITCH_PLAYER_LED};
  static constexpr Hint JoystickHidapiVerticalJoyCons{SDL_HINT_JOYSTICK_HIDAPI_VERTICAL_JOY_CONS};
  static constexpr Hint JoystickHidapiWii{SDL_HINT_JOYSTICK_HIDAPI_WII};
  static constexpr Hint JoystickHidapiWiiPlayerLed{SDL_HINT_JOYSTICK_HIDAPI_WII_PLAYER_LED};
  static constexpr Hint JoystickHidapiXbox{SDL_HINT_JOYSTICK_HIDAPI_XBOX};
  static constexpr Hint JoystickHidapiXbox360{SDL_HINT_JOYSTICK_HIDAPI_XBOX_360};
  static constexpr Hint JoystickHidapiXbox360PlayerLed{SDL_HINT_JOYSTICK_HIDAPI_XBOX_360_PLAYER_LED};
  static constexpr Hint JoystickHidapiXbox360Wireless{SDL_HINT_JOYSTICK_HIDAPI_XBOX_360_WIRELESS};
  static constexpr Hint JoystickHidapiXboxOne{SDL_HINT_JOYSTICK_HIDAPI_XBOX_ONE};
  static constexpr Hint JoystickHidapiXboxOneHomeLed{SDL_HINT_JOYSTICK_HIDAPI_XBOX_ONE_HOME_LED};
  static constexpr Hint JoystickIokit{SDL_HINT_JOYSTICK_IOKIT};
  static constexpr Hint JoystickLinuxClassic{SDL_HINT_JOYSTICK_LINUX_CLASSIC};
  static constexpr Hint JoystickLinuxDeadzones{SDL_HINT_JOYSTICK_LINUX_DEADZONES};
  static constexpr Hint JoystickLinuxDigitalHats{SDL_HINT_JOYSTICK_LINUX_DIGITAL_HATS};
  static constexpr Hint JoystickLinuxHatDeadzones{SDL_HINT_JOYSTICK_LINUX_HAT_DEADZONES};
  static constexpr Hint JoystickMfi{SDL_HINT_JOYSTICK_MFI};
  static constexpr Hint JoystickRawinput{SDL_HINT_JOYSTICK_RAWINPUT};
  static constexpr Hint JoystickRawinputCorrelateXinput{SDL_HINT_JOYSTICK_RAWINPUT_CORRELATE_XINPUT};
  static constexpr Hint JoystickRogChakram{SDL_HINT_JOYSTICK_ROG_CHAKRAM};
  static constexpr Hint JoystickThread{SDL_HINT_JOYSTICK_THREAD};
  static constexpr Hint JoystickThrottleDevices{SDL_HINT_JOYSTICK_THROTTLE_DEVICES};
  static constexpr Hint JoystickThrottleDevicesExcluded{SDL_HINT_JOYSTICK_THROTTLE_DEVICES_EXCLUDED};
  static constexpr Hint JoystickWgi{SDL_HINT_JOYSTICK_WGI};
  static constexpr Hint JoystickWheelDevices{SDL_HINT_JOYSTICK_WHEEL_DEVICES};
  static constexpr Hint JoystickWheelDevicesExcluded{SDL_HINT_JOYSTICK_WHEEL_DEVICES_EXCLUDED};
  static constexpr Hint JoystickZeroCenteredDevices{SDL_HINT_JOYSTICK_ZERO_CENTERED_DEVICES};
  static constexpr Hint KeycodeOptions{SDL_HINT_KEYCODE_OPTIONS};
  static constexpr Hint KmsdrmDeviceIndex{SDL_HINT_KMSDRM_DEVICE_INDEX};
  static constexpr Hint KmsdrmRequireDrmMaster{SDL_HINT_KMSDRM_REQUIRE_DRM_MASTER};
  static constexpr Hint Logging{SDL_HINT_LOGGING};
  static constexpr Hint MacBackgroundApp{SDL_HINT_MAC_BACKGROUND_APP};
  static constexpr Hint MacCtrlClickEmulateRightClick{SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK};
  static constexpr Hint MacOpenglAsyncDispatch{SDL_HINT_MAC_OPENGL_ASYNC_DISPATCH};
  static constexpr Hint MacOptionAsAlt{SDL_HINT_MAC_OPTION_AS_ALT};
  static constexpr Hint MacScrollMomentum{SDL_HINT_MAC_SCROLL_MOMENTUM};
  static constexpr Hint MainCallbackRate{SDL_HINT_MAIN_CALLBACK_RATE};
  static constexpr Hint MouseAutoCapture{SDL_HINT_MOUSE_AUTO_CAPTURE};
  static constexpr Hint MouseDefaultSystemCursor{SDL_HINT_MOUSE_DEFAULT_SYSTEM_CURSOR};
  static constexpr Hint MouseDoubleClickRadius{SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS};
  static constexpr Hint MouseDoubleClickTime{SDL_HINT_MOUSE_DOUBLE_CLICK_TIME};
  static constexpr Hint MouseEmulateWarpWithRelative{SDL_HINT_MOUSE_EMULATE_WARP_WITH_RELATIVE};
  static constexpr Hint MouseFocusClickthrough{SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH};
  static constexpr Hint MouseNormalSpeedScale{SDL_HINT_MOUSE_NORMAL_SPEED_SCALE};
  static constexpr Hint MouseRelativeCursorVisible{SDL_HINT_MOUSE_RELATIVE_CURSOR_VISIBLE};
  static constexpr Hint MouseRelativeModeCenter{SDL_HINT_MOUSE_RELATIVE_MODE_CENTER};
  static constexpr Hint MouseRelativeSpeedScale{SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE};
  static constexpr Hint MouseRelativeSystemScale{SDL_HINT_MOUSE_RELATIVE_SYSTEM_SCALE};
  static constexpr Hint MouseRelativeWarpMotion{SDL_HINT_MOUSE_RELATIVE_WARP_MOTION};
  static constexpr Hint MouseTouchEvents{SDL_HINT_MOUSE_TOUCH_EVENTS};
  static constexpr Hint MuteConsoleKeyboard{SDL_HINT_MUTE_CONSOLE_KEYBOARD};
  static constexpr Hint NoSignalHandlers{SDL_HINT_NO_SIGNAL_HANDLERS};
  static constexpr Hint OpenglEsDriver{SDL_HINT_OPENGL_ES_DRIVER};
  static constexpr Hint OpenglLibrary{SDL_HINT_OPENGL_LIBRARY};
  static constexpr Hint OpenvrLibrary{SDL_HINT_OPENVR_LIBRARY};
  static constexpr Hint Orientations{SDL_HINT_ORIENTATIONS};
  static constexpr Hint PenMouseEvents{SDL_HINT_PEN_MOUSE_EVENTS};
  static constexpr Hint PenTouchEvents{SDL_HINT_PEN_TOUCH_EVENTS};
  static constexpr Hint PollSentinel{SDL_HINT_POLL_SENTINEL};
  static constexpr Hint PreferredLocales{SDL_HINT_PREFERRED_LOCALES};
  static constexpr Hint QuitOnLastWindowClose{SDL_HINT_QUIT_ON_LAST_WINDOW_CLOSE};
  static constexpr Hint RenderDirect3d11Debug{SDL_HINT_RENDER_DIRECT3D11_DEBUG};
  static constexpr Hint RenderDirect3dThreadsafe{SDL_HINT_RENDER_DIRECT3D_THREADSAFE};
  static constexpr Hint RenderDriver{SDL_HINT_RENDER_DRIVER};
  static constexpr Hint RenderGpuDebug{SDL_HINT_RENDER_GPU_DEBUG};
  static constexpr Hint RenderGpuLowPower{SDL_HINT_RENDER_GPU_LOW_POWER};
  static constexpr Hint RenderLineMethod{SDL_HINT_RENDER_LINE_METHOD};
  static constexpr Hint RenderMetalPreferLowPowerDevice{SDL_HINT_RENDER_METAL_PREFER_LOW_POWER_DEVICE};
  static constexpr Hint RenderVsync{SDL_HINT_RENDER_VSYNC};
  static constexpr Hint RenderVulkanDebug{SDL_HINT_RENDER_VULKAN_DEBUG};
  static constexpr Hint ReturnKeyHidesIme{SDL_HINT_RETURN_KEY_HIDES_IME};
  static constexpr Hint RogGamepadMice{SDL_HINT_ROG_GAMEPAD_MICE};
  static constexpr Hint RogGamepadMiceExcluded{SDL_HINT_ROG_GAMEPAD_MICE_EXCLUDED};
  static constexpr Hint RpiVideoLayer{SDL_HINT_RPI_VIDEO_LAYER};
  static constexpr Hint ScreensaverInhibitActivityName{SDL_HINT_SCREENSAVER_INHIBIT_ACTIVITY_NAME};
  static constexpr Hint ShutdownDbusOnQuit{SDL_HINT_SHUTDOWN_DBUS_ON_QUIT};
  static constexpr Hint StorageTitleDriver{SDL_HINT_STORAGE_TITLE_DRIVER};
  static constexpr Hint StorageUserDriver{SDL_HINT_STORAGE_USER_DRIVER};
  static constexpr Hint ThreadForceRealtimeTimeCritical{SDL_HINT_THREAD_FORCE_REALTIME_TIME_CRITICAL};
  static constexpr Hint ThreadPriorityPolicy{SDL_HINT_THREAD_PRIORITY_POLICY};
  static constexpr Hint TimerResolution{SDL_HINT_TIMER_RESOLUTION};
  static constexpr Hint TouchMouseEvents{SDL_HINT_TOUCH_MOUSE_EVENTS};
  static constexpr Hint TrackpadIsTouchOnly{SDL_HINT_TRACKPAD_IS_TOUCH_ONLY};
  static constexpr Hint TvRemoteAsJoystick{SDL_HINT_TV_REMOTE_AS_JOYSTICK};
  static constexpr Hint VideoAllowScreensaver{SDL_HINT_VIDEO_ALLOW_SCREENSAVER};
  static constexpr Hint VideoDisplayPriority{SDL_HINT_VIDEO_DISPLAY_PRIORITY};
  static constexpr Hint VideoDoubleBuffer{SDL_HINT_VIDEO_DOUBLE_BUFFER};
  static constexpr Hint VideoDriver{SDL_HINT_VIDEO_DRIVER};
  static constexpr Hint VideoDummySaveFrames{SDL_HINT_VIDEO_DUMMY_SAVE_FRAMES};
  static constexpr Hint VideoEglAllowGetdisplayFallback{SDL_HINT_VIDEO_EGL_ALLOW_GETDISPLAY_FALLBACK};
  static constexpr Hint VideoForceEgl{SDL_HINT_VIDEO_FORCE_EGL};
  static constexpr Hint VideoMacFullscreenMenuVisibility{SDL_HINT_VIDEO_MAC_FULLSCREEN_MENU_VISIBILITY};
  static constexpr Hint VideoMacFullscreenSpaces{SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES};
  // static constexpr Hint VideoMatchExclusiveModeOnMove{SDL_HINT_VIDEO_MATCH_EXCLUSIVE_MODE_ON_MOVE};
  static constexpr Hint VideoMinimizeOnFocusLoss{SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS};
  static constexpr Hint VideoOffscreenSaveFrames{SDL_HINT_VIDEO_OFFSCREEN_SAVE_FRAMES};
  static constexpr Hint VideoSyncWindowOperations{SDL_HINT_VIDEO_SYNC_WINDOW_OPERATIONS};
  static constexpr Hint VideoWaylandAllowLibdecor{SDL_HINT_VIDEO_WAYLAND_ALLOW_LIBDECOR};
  static constexpr Hint VideoWaylandModeEmulation{SDL_HINT_VIDEO_WAYLAND_MODE_EMULATION};
  static constexpr Hint VideoWaylandModeScaling{SDL_HINT_VIDEO_WAYLAND_MODE_SCALING};
  static constexpr Hint VideoWaylandPreferLibdecor{SDL_HINT_VIDEO_WAYLAND_PREFER_LIBDECOR};
  static constexpr Hint VideoWaylandScaleToDisplay{SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY};
  static constexpr Hint VideoWinD3dcompiler{SDL_HINT_VIDEO_WIN_D3DCOMPILER};
  static constexpr Hint VideoX11ExternalWindowInput{SDL_HINT_VIDEO_X11_EXTERNAL_WINDOW_INPUT};
  static constexpr Hint VideoX11NetWmBypassCompositor{SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR};
  static constexpr Hint VideoX11NetWmPing{SDL_HINT_VIDEO_X11_NET_WM_PING};
  static constexpr Hint VideoX11Nodirectcolor{SDL_HINT_VIDEO_X11_NODIRECTCOLOR};
  static constexpr Hint VideoX11ScalingFactor{SDL_HINT_VIDEO_X11_SCALING_FACTOR};
  static constexpr Hint VideoX11Visualid{SDL_HINT_VIDEO_X11_VISUALID};
  static constexpr Hint VideoX11WindowVisualid{SDL_HINT_VIDEO_X11_WINDOW_VISUALID};
  static constexpr Hint VideoX11Xrandr{SDL_HINT_VIDEO_X11_XRANDR};
  static constexpr Hint VitaEnableBackTouch{SDL_HINT_VITA_ENABLE_BACK_TOUCH};
  static constexpr Hint VitaEnableFrontTouch{SDL_HINT_VITA_ENABLE_FRONT_TOUCH};
  static constexpr Hint VitaModulePath{SDL_HINT_VITA_MODULE_PATH};
  static constexpr Hint VitaPvrInit{SDL_HINT_VITA_PVR_INIT};
  static constexpr Hint VitaPvrOpengl{SDL_HINT_VITA_PVR_OPENGL};
  static constexpr Hint VitaResolution{SDL_HINT_VITA_RESOLUTION};
  static constexpr Hint VitaTouchMouseDevice{SDL_HINT_VITA_TOUCH_MOUSE_DEVICE};
  static constexpr Hint VulkanDisplay{SDL_HINT_VULKAN_DISPLAY};
  static constexpr Hint VulkanLibrary{SDL_HINT_VULKAN_LIBRARY};
  static constexpr Hint WaveChunkLimit{SDL_HINT_WAVE_CHUNK_LIMIT};
  static constexpr Hint WaveFactChunk{SDL_HINT_WAVE_FACT_CHUNK};
  static constexpr Hint WaveRiffChunkSize{SDL_HINT_WAVE_RIFF_CHUNK_SIZE};
  static constexpr Hint WaveTruncation{SDL_HINT_WAVE_TRUNCATION};
  static constexpr Hint WindowActivateWhenRaised{SDL_HINT_WINDOW_ACTIVATE_WHEN_RAISED};
  static constexpr Hint WindowActivateWhenShown{SDL_HINT_WINDOW_ACTIVATE_WHEN_SHOWN};
  static constexpr Hint WindowAllowTopmost{SDL_HINT_WINDOW_ALLOW_TOPMOST};
  static constexpr Hint WindowFrameUsableWhileCursorHidden{SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN};
  static constexpr Hint WindowsCloseOnAltF4{SDL_HINT_WINDOWS_CLOSE_ON_ALT_F4};
  static constexpr Hint WindowsEnableMenuMnemonics{SDL_HINT_WINDOWS_ENABLE_MENU_MNEMONICS};
  static constexpr Hint WindowsEnableMessageloop{SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP};
  static constexpr Hint WindowsEraseBackgroundMode{SDL_HINT_WINDOWS_ERASE_BACKGROUND_MODE};
  static constexpr Hint WindowsForceSemaphoreKernel{SDL_HINT_WINDOWS_FORCE_SEMAPHORE_KERNEL};
  static constexpr Hint WindowsGameinput{SDL_HINT_WINDOWS_GAMEINPUT};
  static constexpr Hint WindowsIntresourceIcon{SDL_HINT_WINDOWS_INTRESOURCE_ICON};
  static constexpr Hint WindowsIntresourceIconSmall{SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL};
  static constexpr Hint WindowsRawKeyboard{SDL_HINT_WINDOWS_RAW_KEYBOARD};
  static constexpr Hint WindowsUseD3d9ex{SDL_HINT_WINDOWS_USE_D3D9EX};
  static constexpr Hint X11ForceOverrideRedirect{SDL_HINT_X11_FORCE_OVERRIDE_REDIRECT};
  static constexpr Hint X11WindowType{SDL_HINT_X11_WINDOW_TYPE};
  static constexpr Hint X11XcbLibrary{SDL_HINT_X11_XCB_LIBRARY};
  static constexpr Hint XinputEnabled{SDL_HINT_XINPUT_ENABLED};
  // clang-format on
} // namespace sdl::hints

// todo: unimplemented
// SDL_AddHintCallback
// SDL_RemoveHintCallback
