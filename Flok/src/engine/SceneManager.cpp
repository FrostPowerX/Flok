#include "SceneManager.h"

#include "CloseUp.h"
#include "Error.h"
#include "scenes/Controls.h"
#include "scenes/Credits.h"
#include "scenes/MainMenu.h"
#include "scenes/Play.h"
#include "scenes/Statistics.h"

namespace Game {

namespace SceneManager {

static void SceneLoop(const Scenes SelectedScene) {

  switch (SelectedScene) {
    case Scenes::MainMenu:
      Scene::Menu();
      break;

    case Scenes::Play:
      Scene::Play();
      break;

    case Scenes::Multiplayer:
      Scene::Play(true);
      break;

    case Scenes::Statistics:
      Scene::Statistics();
      break;

    case Scenes::Controls:
      Scene::Controls();
      break;

    case Scenes::Credits:
      Scene::Credits();
      break;

    case Scenes::Exit:
      Close();
      break;

    default:
      Close();
      Error::Unhandled(__LINE__, __FILE__);
      break;
  }
}

void ChangeScene(const Scenes SelectedScene) {
  SceneLoop(SelectedScene);
}

} // namespace SceneManager

} // namespace Game
