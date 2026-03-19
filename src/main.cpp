#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Config.h"

#ifdef WITH_EDITOR
#include "Editor/Schene.h"
#include "Editor/Window.h"
#endif

int main(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // CheckSDLError("SDL_Init");
    return 1;
  }

  if (!TTF_Init()) {
    // CheckSDLError("TTF_Init");
    return 1;
  }

#ifdef WITH_EDITOR
  Editor::Window EditorWindow;
  Editor::Scene EditorScene{EditorWindow};
#endif

  Uint64 LastTick{SDL_GetPerformanceCounter()};
  SDL_Event E;
  while (true) {
    while (SDL_PollEvent(&E)) {
#ifdef WITHEDITOR
      Editor.HandleEvent(E)
#endif
      if (E.type == SDL_EVENT_QUIT || E.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        TTF_Quit();
        SDL_Quit();
        return 0;
      }
    }

    Uint64 CurrentTick{SDL_GetPerformanceCounter()};
    float DeltaTime{
      static_cast<float>(CurrentTick - LastTick) / static_cast<float>(SDL_GetPerformanceFrequency())
    };
    LastTick = CurrentTick;

#ifdef WITH_EDITOR
    EditorScene.Tick(DeltaTime);
    EditorScene.Render();
    EditorScene.Render(EditorWindow.GetSurface());
    EditorWindow.Update();
#endif
  }

  return 0;
}

