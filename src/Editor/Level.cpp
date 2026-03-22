#include "Editor/Level.h"
#include "Editor/Scene.h"
#include <ranges>

using namespace Editor;

void Level::HandleEvent(const SDL_Event& E) {
  using namespace std::views;
  for (ActorPtr& A : reverse(Actors)) {
    if (A->HandleEvent(E)) {
      break;
    }
  }

  if (
    E.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
    E.button.button == SDL_BUTTON_LEFT
  ) {
    SelectedActor = nullptr;
  } else if (
    E.type == SDL_EVENT_KEY_DOWN &&
    E.key.key == SDLK_BACKSPACE && SelectedActor
  ) {
    for (size_t i{0}; i < Actors.size(); i++) {
      if (Actors[i].get() == SelectedActor) {
        Actors.erase(Actors.begin() + i);
        break;
      }
    }
    SelectedActor = nullptr;
  }
}

void Level::Tick(float DeltaTime) {
  for (ActorPtr& A : Actors) {
    A->Tick(DeltaTime);
  }
}

void Level::Render(SDL_Surface* Surface) {
  auto [r, g, b, a]{
    Config::Editor::LEVEL_BACKGROUND
  };

  const auto* Fmt{SDL_GetPixelFormatDetails(
    Surface->format
  )};

  SDL_FillSurfaceRect(Surface, &Rect, SDL_MapRGB(Fmt, nullptr, r, g, b));

  for (ActorPtr& A : Actors) {
    if (SelectedActor && A.get() == SelectedActor && SelectedActor->GetIsVisible()) {
      auto [x, y, w, h] {
        SelectedActor->GetRect()
      };
      SDL_Rect Rect{x - 1, y - 1, w + 2, h + 2};
      SDL_FillSurfaceRect(Surface, &Rect, SDL_MapRGB(Fmt, nullptr, 255, 255, 255));
    }
    A->Render(Surface);
  }
}

void Level::AddToLevel(ActorPtr NewActor) {
  NewActor->SetLocation(ActorLocation::Level);
  Actors.push_back(std::move(NewActor));
}

bool Level::HasMouseFocus() const {
  float MouseX, MouseY;
  SDL_GetMouseState(&MouseX, &MouseY);

  if (
    MouseX <= 0 ||
    MouseY <= 0 ||
    MouseX >= Config::Editor::LEVEL_WIDTH ||
    MouseY >= Config::Editor::LEVEL_HEIGHT
  ) {
    return false;
  }

  return true;
}

void Level::HandleDrop(Actor* DragActor) {
  DragActor->SetIsVisible(true);
  if (!HasMouseFocus()) {
    return;
  }
  float MouseX, MouseY;

  SDL_GetMouseState(&MouseX, &MouseY);
  auto [DragOffsetX, DragOffsetY] {
    DragActor->GetDragOffset()
  };

  using enum ActorLocation;
  if (DragActor->GetLocation() == Menu) {
    ActorPtr NewActor{DragActor->Clone()};
    NewActor->SetPosition(
      int(MouseX) - DragOffsetX,
      int(MouseY) - DragOffsetY
    );
    SelectedActor = NewActor.get();
    AddToLevel(std::move(NewActor));
  } else {
    DragActor->SetPosition(
      int(MouseX) - DragOffsetX,
      int(MouseY) - DragOffsetY
    );
    SelectedActor = DragActor;
  }
}
