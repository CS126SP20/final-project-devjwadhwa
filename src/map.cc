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
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      this->coordinates_[i][j] = game_map[i][j];
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
    if (!line_maze.empty()) {
      SetupMap(line_maze);
      maze_count++;

      if (maze_count == kBoardDimension) {
        Map game_screen = Map(map);
        maze_maps.push_back(game_screen);

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

  for (int i = 0; i < kBoardDimension; i++) {
    map_char.push_back(map_line.at(i));
  }
  map.push_back(map_char);
}

}  // namespace mylibrary

