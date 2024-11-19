#include "GameManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "SoundManager.h"

namespace Game {

using namespace SoundManager;

static int f_MaxScoreMP = 0;
static int f_CurrentScoreMP = 0;
static int f_TotalScoreMP = 0;
static int f_TotalJumpsMP = 0;
static int f_TotalLoseMP = 0;

static int f_MaxScore = 0;
static int f_CurrentScore = 0;
static int f_TotalScore = 0;
static int f_TotalJumps = 0;
static int f_TotalLose = 0;

static const std::string k_SaveFile = "data.json";
static const std::string k_EncryptationKey = "WOLOOLOO";

static std::string EncryptDecrypt(const std::string& k_Data, const std::string& k_Key) {

  std::string result = k_Data;

  for (size_t i = 0; i < k_Data.size(); i++) {

    result[i] ^= k_Key[i % k_Key.size()];
  }

  return result;
}

static std::string CreateJSONString() {

  std::ostringstream k_Json;

  k_Json << "{";
  k_Json << "\"MaxScoreMP\":" << f_MaxScoreMP << ",";
  k_Json << "\"CurrentScoreMP\":" << f_CurrentScoreMP << ",";
  k_Json << "\"TotalScoreMP\":" << f_TotalScoreMP << ",";
  k_Json << "\"TotalJumpsMP\":" << f_TotalJumpsMP << ",";
  k_Json << "\"TotalLoseMP\":" << f_TotalLoseMP << ",";

  k_Json << "\"MaxScore\":" << f_MaxScore << ",";
  k_Json << "\"CurrentScore\":" << f_CurrentScore << ",";
  k_Json << "\"TotalScore\":" << f_TotalScore << ",";
  k_Json << "\"TotalJumps\":" << f_TotalJumps << ",";
  k_Json << "\"TotalLose\":" << f_TotalLose << ",";

  k_Json << "\"SoundVolume\":" << GetSoundVolume() << ",";
  k_Json << "\"MusicVolume\":" << GetMusicVolume();
  k_Json << "}";

  std::cout << "Save: " << k_Json.str() << "\n";

  return k_Json.str();
}

static void ParseJSONString(const std::string& k_JsonString) {

  size_t Pos = 0;

  auto GetValue = [&](const std::string& key) -> int {
    size_t KeyPos = k_JsonString.find("\"" + key + "\":", Pos);
    if (KeyPos == std::string::npos) {

      return 0;
    }

    KeyPos += key.size() + 3;
    size_t EndPos = k_JsonString.find_first_of(",}", KeyPos);

    return std::stoi(k_JsonString.substr(KeyPos, EndPos - KeyPos));
  };

  f_MaxScoreMP = GetValue("MaxScoreMP");
  f_CurrentScoreMP = GetValue("CurrentScoreMP");
  f_TotalScoreMP = GetValue("TotalScoreMP");
  f_TotalJumpsMP = GetValue("TotalJumpsMP");
  f_TotalLoseMP = GetValue("TotalLoseMP");

  f_MaxScore = GetValue("MaxScore");
  f_CurrentScore = GetValue("CurrentScore");
  f_TotalScore = GetValue("TotalScore");
  f_TotalJumps = GetValue("TotalJumps");
  f_TotalLose = GetValue("TotalLose");

  SetSoundVolume(GetValue("SoundVolume"));
  SetMusicVolume(GetValue("MusicVolume"));

  std::cout << "Load: " << k_JsonString << "\n";
}

static void SaveInfo() {

  std::string jsonString = CreateJSONString();

  std::string encryptedData = EncryptDecrypt(jsonString, k_EncryptationKey);

  std::ofstream file(k_SaveFile, std::ios::binary);

  if (file.is_open()) {
    file.write(encryptedData.c_str(), encryptedData.size());
    file.close();
  }
}

static void LoadInfo() {

  std::ifstream file(k_SaveFile, std::ios::binary);

  if (file.is_open()) {

    std::string encryptedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::string jsonString = EncryptDecrypt(encryptedData, k_EncryptationKey);
    ParseJSONString(jsonString);
  }
}

void InitGManager() {

  LoadInfo();
}

void UnloadGManager() {

  SaveInfo();
}

void ResetScore(bool isMP) {

  if (isMP) {

    f_MaxScoreMP = (f_CurrentScoreMP > f_MaxScoreMP) ? f_CurrentScoreMP : f_MaxScoreMP;
    f_CurrentScoreMP = 0;
  } else {

    f_MaxScore = (f_CurrentScore > f_MaxScore) ? f_CurrentScore : f_MaxScore;
    f_CurrentScore = 0;
  }
}

void AddScore(bool isMP) {

  if (isMP) {

    f_TotalScoreMP++;
    f_CurrentScoreMP++;
  } else {

    f_TotalScore++;
    f_CurrentScore++;
  }
}

void AddJump(bool isMP) {

  if (isMP) {

    f_TotalJumpsMP++;
  } else {

    f_TotalJumps++;
  }
}

void AddLose(bool isMP) {

  if (isMP) {

    f_TotalLoseMP++;
  } else {

    f_TotalLose++;
  }
}

int GetScore(bool isMP) {

  return (isMP) ? f_CurrentScoreMP : f_CurrentScore;
}

int GetMaxScore(bool isMP) {

  return (isMP) ? f_MaxScoreMP : f_MaxScore;
}

int GetTotalJumps(bool isMP) {

  return (isMP) ? f_TotalJumpsMP : f_TotalJumps;
}

int GetTotalLose(bool isMP) {

  return (isMP) ? f_TotalLoseMP : f_TotalLose;
}

int GetTotalScore(bool isMP) {

  return (isMP) ? f_TotalScoreMP : f_TotalScore;
}

} // namespace Game
