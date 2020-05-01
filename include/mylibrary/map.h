// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include <mylibrary/engine.h>
#include <string>
#include <vector>


namespace mylibrary {
using mylibrary::Engine;


class Map {
 public:
  char coordinates_[16][16]{};

 public:
  Map();
  explicit Map(std::vector<std::vector<char>> game_screen);
  Location GetPlayerNewLoc(const Map& curr_map, Engine engine);
  std::string GetMapLabels();
  void ReadImageLabels();
  void ReadGameScreens();
  void SetupMap(std::string map_line);
  bool IsScreenChange();
  int GetCurrScreenNum(const Map& curr_map);
  int GetNewScreenNum();
  int GetTransitionScreenNum(int num, char entry);
  std::vector<Map> GetScreen();
  enum EntryPoints { a = 97};

 private:
  int screen_num_{};
  std::vector<std::string> map_labels_;
  bool is_screen_change_ = false;
  std::vector<mylibrary::Map> game_maps_;
  std::vector<std::vector<char>> map_;
  std::string entry_points_ = "a";
};

}  // namespace mylibrary

#endif  // FINALPROJECT_MAP_H
