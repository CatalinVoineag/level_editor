#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

namespace Config {
inline const std::vector BUTTON_COLORS{
  SDL_Color{15, 15, 15, 255},  // Normal
  SDL_Color{15, 155, 15, 255}, // Hover
  SDL_Color{225, 15, 15, 255}, // Active
  SDL_Color{60, 60, 60, 255}   // Disabled
};

inline const std::string BASE_PATH{
  SDL_GetBasePath()};
inline const std::string FONT{
  BASE_PATH + "Assets/Rubik-SemiBold.ttf"};
inline constexpr SDL_Color FONT_COLOR{
  255, 255, 255, 255};
}

#ifdef WITH_EDITOR
namespace Config::Editor {

// Level
inline const int LEVEL_WIDTH{650};
inline const int LEVEL_HEIGHT{150};
inline constexpr SDL_Color LEVEL_BACKGROUND{50, 50, 50, 255};

// ActorMenu
inline const int ACTOR_MENU_WIDTH{70};

// Window
inline const std::string WINDOW_TITLE{"Editor"};
inline const int WINDOW_WIDTH{LEVEL_WIDTH + ACTOR_MENU_WIDTH};
inline const int WINDOW_HEIGHT{LEVEL_HEIGHT + 50};
inline const SDL_Color WINDOW_BACKGROUND{35, 35, 35, 255};

// ActorMenu
inline const int ACTOR_MENU_POSITION_X{WINDOW_WIDTH - ACTOR_MENU_WIDTH};
inline const SDL_Color ACTOR_MENU_BACKGROUND{15, 15, 15, 255};
inline const int PADDING{10};

}
#endif

namespace UserEvents {
#ifdef WITH_EDITOR
  inline Uint32 ACTOR_DRAG{SDL_RegisterEvents(1)};
#endif
}

inline void CheckSDLError(const std::string& Msg) {
#ifdef CHECK_ERRORS
  const char* error = SDL_GetError();
  if (*error != '\0') {
    std::cerr << Msg << " Error: "
      << error << '\n';
    SDL_ClearError();
  }
#endif
}
