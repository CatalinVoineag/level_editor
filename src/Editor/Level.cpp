#include "Editor/Level.h"
#include "Editor/Scene.h"

using namespace Editor;

void Level::HandleEvent(const SDL_Event& E) {
  for (ActorPtr& A : Actors) {
    A->HandleEvent(E);
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
    A->Render(Surface);
  }
}

void Level::AddToLevel(ActorPtr NewActor) {
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
