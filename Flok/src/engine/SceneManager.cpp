#include "SceneManager.h"

#include "CloseUp.h"
#include "Error.h"
#include "scenes/Credits.h"
#include "scenes/MainMenu.h"
#include "scenes/Play.h"

namespace {

void SceneLoop(const SceneManager::Scenes SelectedScene) {

  switch (SelectedScene) {
    case SceneManager::Scenes::MainMenu:
      MainMenu::Menu();
      break;
    case SceneManager::Scenes::Play:
      Play::Play();
      break;
    case SceneManager::Scenes::Credits:
      Credits::Credits();
      break;
    case SceneManager::Scenes::Exit:
      CloseUp::Close();
      break;
    default:
      CloseUp::Close();
      Error::Unhandled(__LINE__, __FILE__);
      break;
  }

}

}



void SceneManager::ChangeScene(const Scenes SelectedScene) {
  SceneLoop(SelectedScene);
}
