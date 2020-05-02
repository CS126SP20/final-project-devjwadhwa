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
  char cartesian[16][16]{};

 public:
  Map();
  explicit Map(std::vector<std::vector<char>> game_map);
  void ReadBackgroundImages();
  void ReadMaps();
  void SetupMap(std::string map_line);
  std::vector<Map> GetMaps();
  int GetCurrMapKey(const Map& current_map);
  int GetParallelMapKey(int key, char door);
  bool IsScreenChange();
  int GetParallelMapNum();
  Location GetPlayerParallelLoc(const Map& current_map, Engine engine);
  std::string Map::GetMapKeys();

    private:
  const int kBoardDimension = 16;
  int screen_num_{};
  std::vector<std::string> background_images;
  bool is_screen_change_ = false;
  std::vector<mylibrary::Map> maze_maps;
  std::vector<std::vector<char>> map;
  std::string exits = "abcdef";
};

}  // namespace mylibrary

#endif  // FINALPROJECT_MAP_H
