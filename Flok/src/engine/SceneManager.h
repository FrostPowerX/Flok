#pragma once

namespace Game {

namespace SceneManager {

enum class Scenes { MainMenu = 0, Play, Multiplayer, Controls, Credits, Exit };

void ChangeScene(Scenes SelectedScene = Scenes::MainMenu);

} // namespace SceneManager

} // namespace Game
