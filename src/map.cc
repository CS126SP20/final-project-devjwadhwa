// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include <mylibrary/map.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using mylibrary::Direction;
using mylibrary::Location;

int prev_row = 0;
int prev_col = 0;

namespace mylibrary {

Map::Map() = default;

Map::Map(std::vector<std::vector<char>> game_screen) {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      this->coordinates_[i][j] = game_screen[i][j];
    }
  }
}

void Map::ReadBackgrounds() {
  std::string background_file =
}



/*
char **Map::ReadMap() {
  std::ifstream fileInput;
  fileInput.open("assets/maze.txt");
  while ( !fileInput.eof() ) {
    for (int i = 0 ; i < 16; i++) {
      for (int j = 0 ; j < 33; j++) {
        fileInput >> maze[i][j];
      }
    }
  }
  fileInput.close();
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 33; j++) {
      std::cout << maze[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return maze;
}

void Map::SetMapKey(char map_[16][33]) {
  int count = 0;
  for (int i = 1; i <= num_maps; i++) {
    for (int j = count; j < 16 + count; j++) {
      for (int k = 0; k < 16; k++) {
        maps[i][k][j] = map_[k][j];
      }
    }
    count += 16;
  }
}

int Map::GetNewMapKey(Location location, int curr_map_key) {
  int row = location.Row();
  int col = location.Col();
  int count = 0;
  for (int j = 0; j < 16; j++) {
    for (int k = 0; k < 16; k++) {
        if(map[i][k][j] == 'a' && i != curr_map_key);
        Location location = engine.GetPrisoner().GetLoc();
        location.Row() == i;
        location.Col() == j;
        Location(row_now, col_now);
      }
    }
    count += 16;
  }
}
 */



}  // namespace mylibrary

