// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include <mylibrary/map.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using mylibrary::Direction;
using mylibrary::Location;


namespace mylibrary {

Map::Map() = default;

Map::Map(std::vector<std::vector<char>> game_screen) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      this->coordinates_[i][j] = game_screen[i][j];
    }
  }
}

}  // namespace mylibrary

