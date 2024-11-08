#pragma once
namespace SceneManager {

enum class Scenes {
  MainMenu = 1,
  Play,
  Credits,
  Exit
};



void ChangeScene(Scenes SelectedScene = Scenes::MainMenu);

}
