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

Map::Map(std::vector<std::vector<char>> game_map) {

  // A coordinate system
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      this->cartesian[i][j] = game_map[i][j];
    }
  }
}

void Map::ReadBackgroundImages() {

  std::string background_file =
      "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Break/assets/background.txt";

  std::ifstream images_file(background_file);

  while(!images_file.eof()) {
    std::string image;
    std::getline(images_file, image);

    // Gets each image name in a string
    background_images.push_back(image);
  }
}

void Map::ReadMaps() {
  int maze_count = 0;

  std::string maze_file =
      "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Break/assets/maze.txt";

  std::ifstream file(maze_file);
  while (!file.eof()) {
    std::string line_maze;
    std::getline(file, line_maze);

    // Ignores empty lines
    if (!line_maze.empty()) {
      SetupMap(line_maze);
      maze_count++;

      // Ends one map
      if (maze_count == kBoardDimension) {
        Map game_map = Map(map);
        maze_maps.push_back(game_map);

        maze_count = 0;
        map.clear();
      }
    }
  }
}

void Map::SetupMap(std::string map_line) {
  std::vector<char> map_char;

  // Reserves space for each line
  map_char.reserve(kBoardDimension);

  // Pushes back each char
  for (int i = 0; i < kBoardDimension; i++) {
    map_char.push_back(map_line.at(i));
  }

  // Pushes back each line
  map.push_back(map_char);
}

std::vector<Map> Map::GetMaps() {
  return maze_maps;
}

int Map::GetCurrMapKey(const Map& current_map) {
  int count = 0;
  for (int i = 0; i < maze_maps.size(); i++) {
    for (int j = 0; j < kBoardDimension; j++) {
      for (int k = 0; k < kBoardDimension; k++) {

        // Checking Similarity bock wise
        if (maze_maps[i].cartesian[j][k] == current_map.cartesian[j][k]) {
          count++;

        } else {
          count = 0;
          goto exitloop;
        }

        // If the current map is EXACTLY similar to the ith map
        if (count == kBoardDimension*kBoardDimension) {
          return i;
        }
      }
    }
    exitloop:;
  }
  return 0;
}

int Map::GetParallelMapKey(int key, char door) {
  for (int i = 0; i < maze_maps.size(); i++) {
    if (i != key) {
      for (int j = 0; j < kBoardDimension; j++) {
        for (int k = 0; k < kBoardDimension; k++) {

          // Gets the map with the same door point as the current one
          if (maze_maps[i].cartesian[j][k] == door) {
            return i;
          }
        }
      }
    }
  }
  return 0;
}



}  // namespace mylibrary

