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

void Map::ReadBackgroundImagesFile() {
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

void Map::ReadMapsFile() {
  int number_of_maps = 0;
  std::string maps_file =
      "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Trial/assets/maze.txt";
  std::ifstream file(maps_file);

  while (!file.eof()) {
    std::string line_map;
    std::getline(file, line_map);

    // Ignores empty lines, else setups Map
    if (!line_map.empty()) {
      SetupMap(line_map);
      number_of_maps++;

      // Ends one map
      if (number_of_maps == kDimension) {
        Map game_map = Map(map);
        all_maps.push_back(game_map);

        // Repeats the same
        number_of_maps = 0;
        map.clear();
      }
    }
  }
}

std::vector<Map> Map::GetAllMaps() {
  return all_maps;
}

void Map::SetupMap(std::string map_line) {
  std::vector<char> map_char;

  // Pushes back each char
  for (int i = 0; i < kDimension; i++) {
    map_char.push_back(map_line.at(i));
  }

  // Pushes back each line
  map.push_back(map_char);
}

std::string Map::GetCurrentMapName() {
  std::string curr_map;
  for (int i = 0; i < background_images.size(); i++) {
    if (i == parallel_map_num) {
      curr_map = background_images[i];
    }
  }
  return curr_map;
}

int Map::GetCurrentMapKey(const Map& current_map) {
  int count = 0;
  for (int i = 0; i < all_maps.size(); i++) {
    for (int j = 0; j < kDimension; j++) {
      for (int k = 0; k < kDimension; k++) {

        // Checking similarity block wise
        if (all_maps[i].cartesian[j][k] == current_map.cartesian[j][k]) {
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
  for (int i = 0; i < all_maps.size(); i++) {
    for (int j = 0; j < kDimension; j++) {
      for (int k = 0; k < kDimension; k++) {

        // Gets the map with the same door point as the current one
        if (all_maps[i].cartesian[j][k] == door && i != key) {
          return i;
        }
      }
    }
  }
  return 0;
}

Location Map::GetParallelMapLoc(const Map& current_map, Engine engine) {
  Location loc = engine.GetPrisoner().GetLoc();
  int curr_row = loc.Col();
  int curr_col = loc.Row();

  for (int j = 0; j < exits.size(); j++) {
    if (current_map.cartesian[curr_row][curr_col] == exits.at(j)) {
      parallel_map_num = GetParallelMapKey(GetCurrentMapKey(current_map),
                                           exits.at(j));
      is_screen_change_ = true;

      // Sets the location for different Scenarios
      if (engine.GetDirection() == Direction::kUp) {
        return {curr_col, kDimension - curr_row - 1};
      } else if (engine.GetDirection() == Direction::kDown) {
        return {curr_col, kDimension - curr_row + 1};
      } else if (engine.GetDirection() == Direction::kLeft) {
        return {kDimension - curr_col - kLoc, curr_row};
      } else if (engine.GetDirection() == Direction::kRight){
        return {kDimension - curr_col, curr_row};
      }
    }
  }
  return loc;
}

int Map::GetParallelMapNum() {
  return parallel_map_num;
}

bool Map::IsScreenChange() {
  return is_screen_change_;
}

}  // namespace mylibrary

