#pragma once
#include <SDL3/SDL.h>
#include "AssetManager.h"
#include "ActorMenu.h"
#include "ActorTooltip.h"
#include "Window.h"
#include "Level.h"

namespace Editor {
  class Scene {
    public:
      Scene(Window& ParentWindow) : ParentWindow{ParentWindow}{}

      void HandleEvent(const SDL_Event& E) {
        ActorShelf.HandleEvent(E);
        TooltipWindow.HandleEvent(E);
        CurrentLevel.HandleEvent(E);
      }

      void Tick(float DeltaTime) {
        ActorShelf.Tick(DeltaTime);
        TooltipWindow.Tick(DeltaTime);
        CurrentLevel.Tick(DeltaTime);
      }

      void Render(SDL_Surface* Surface) {
        ActorShelf.Render(Surface);
        TooltipWindow.Render();
        CurrentLevel.Render(Surface);
      }

      AssetManager& GetAssets() {
        return Assets;
      }

      bool HasMouseFocus() const {
        return ParentWindow.HasMouseFocus();
      }

      Window& GetWindow() const {
        return ParentWindow;
      }

      Level& GetLevel() {
        return CurrentLevel;
      }

    private:
      Window& ParentWindow;
      AssetManager Assets;
      ActorMenu ActorShelf{*this};
      ActorTooltip TooltipWindow{*this};
      Level CurrentLevel{*this};
  };
}
