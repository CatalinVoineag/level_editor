#include "Editor/Actor.h"
#include "Editor/Scene.h"
#include "Config.h"

using namespace Editor;

void Actor::HandleEvent(const SDL_Event& E) {
  if (
    E.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
    E.button.button == SDL_BUTTON_LEFT &&
    HasMouseFocus()
  ) {
    DragOffset.x = int(E.button.x) - Rect.x;
    DragOffset.y = int(E.button.y) - Rect.y;

    SDL_Event DragEvent{UserEvents::ACTOR_DRAG};
    DragEvent.user.data1 = this;
    SDL_PushEvent(&DragEvent);
  }
}

bool Actor::HasMouseFocus() const {
  if (!ParentScene.HasMouseFocus()) {
    return false;
  }

  float x, y;
  SDL_GetMouseState(&x, &y);

  if (
    x < Rect.x ||
    x > Rect.x + Rect.w ||
    y < Rect.y ||
    y > Rect.y + Rect.h
  ) { return false; }

  return true;
}
