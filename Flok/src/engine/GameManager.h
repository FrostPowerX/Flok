#pragma once

namespace Game {

void InitGManager();
void UnloadGManager();

void ResetScore(bool isMP = false);

void AddScore(bool isMP = false);
void AddJump(bool isMP = false);
void AddLose(bool isMP = false);

int GetScore(bool isMP = false);
int GetMaxScore(bool isMP = false);
int GetTotalJumps(bool isMP = false);
int GetTotalLose(bool isMP = false);
int GetTotalScore(bool isMP = false);

} // namespace Game
