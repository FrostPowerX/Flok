#pragma once
namespace SceneManager {

enum class Scenes {
  MainMenu = 0,
  Play, 
  Multiplayer,
  Credits,
  Exit
};



void ChangeScene(Scenes SelectedScene = Scenes::MainMenu);

}
