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
  for (int i = 0; i < kDimension; i++) {
    for (int j = 0; j < kDimension; j++) {
      this->cartesian[i][j] = game_map[i][j];
    }
  }
}

void Map::ReadBackgroundImages() {
  std::string background_file =
      "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Trial/assets/background.txt";
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
      "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Trial/assets/maze.txt";
  std::ifstream file(maze_file);

  while (!file.eof()) {
    std::string line_maze;
    std::getline(file, line_maze);

    // Ignores empty lines, else setups Map
    if (!line_maze.empty()) {
      SetupMap(line_maze);
      maze_count++;

      // Ends one map
      if (maze_count == kDimension) {
        Map game_map = Map(map);
        maze_maps.push_back(game_map);

        // Repeats the same
        maze_count = 0;
        map.clear();
      }
    }
  }
}

void Map::SetupMap(std::string map_line) {
  std::vector<char> map_char;

  // Reserves space for each line
  map_char.reserve(kDimension);

  // Pushes back each char
  for (int i = 0; i < kDimension; i++) {
    map_char.push_back(map_line.at(i));
  }

  // Pushes back each line
  map.push_back(map_char);
}

std::string Map::GetBackgroundKey() {
  std::string key;
  for (int i = 0; i < background_images.size(); i++) {
    if (i == screen_num_) {
      std::cout<<background_images[i]<<std::endl;
      key = background_images[i];
    }
  }
  return key;
}

int Map::GetCurrMapKey(const Map& current_map) {
  int count = 0;
  for (int i = 0; i < maze_maps.size(); i++) {
    for (int j = 0; j < kDimension; j++) {
      for (int k = 0; k < kDimension; k++) {

        // Checking similarity block wise
        if (maze_maps[i].cartesian[j][k] == current_map.cartesian[j][k]) {
          count++;

          // Checks if the current map is EXACTLY similar to the ith map
          if (count == kDimension*kDimension) {
            return i;
          }
        } else {
          count = 0;
        }
      }
    }
  }
  return 0;
}

int Map::GetParallelMapKey(int key, char door) {
  for (int i = 0; i < maze_maps.size(); i++) {
    for (int j = 0; j < kDimension; j++) {
      for (int k = 0; k < kDimension; k++) {

        // Gets the map with the same door point as the current one
        if (maze_maps[i].cartesian[j][k] == door && i != key) {
          return i;
        }
      }
    }
  }
  return 0;
}

Location Map::GetPlayerParallelLoc(const Map& current_map, Engine engine) {
  Location loc = engine.GetPrisoner().GetLoc();
  int curr_row = loc.Col();
  int curr_col = loc.Row();

  for (int j = 0; j < exits.size(); j++) {
    if (current_map.cartesian[curr_row][curr_col] == exits.at(j)) {
      screen_num_ = GetParallelMapKey(GetCurrMapKey(current_map),
                                           exits.at(j));
      is_screen_change_ = true;

      if (engine.GetDirection() == Direction::kUp) {
        return {curr_col, kDimension - kLoc};
      } else if (engine.GetDirection() == Direction::kDown) {
        return {curr_col, kLoc};
      } else if (engine.GetDirection() == Direction::kLeft) {
        return {kDimension - kLoc, curr_row};
      } else if (engine.GetDirection() == Direction::kRight){
        return {kLoc - 1, curr_row};
      }
    }
  }
  return loc;
}


std::vector<Map> Map::GetMaps() {
  return maze_maps;
}

bool Map::IsScreenChange() {
  return is_screen_change_;
}

int Map::GetParallelMapNum() {
  return screen_num_;
}

}  // namespace mylibrary

