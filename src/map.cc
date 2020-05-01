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

void Map::ReadImageLabels() {
  std::string map_label_file = "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Break/assets/background.txt";
  std::ifstream file(map_label_file);

  while(!file.eof()) {
    std::string map_label;
    std::getline(file, map_label);
    map_labels_.push_back(map_label);
  }
}

void Map::ReadGameScreens() {
  int map_line_count = 0;
  std::string maps_file = "C:/Users/devjw/CLionProjects/cinder_0.9.2_vc2015/projects/Break/assets/maze.txt";
  std::ifstream file(maps_file);
  while (!file.eof()) {
    std::string map_line;
    std::getline(file, map_line);
    if (!map_line.empty()) {
      SetupMap(map_line);
      map_line_count++;


      if (map_line_count == 16) {
        Map game_screen = Map(map_);
        game_maps_.push_back(game_screen);

        map_line_count = 0;
        map_.clear();
      }
    }
  }
}

void Map::SetupMap(std::string map_line) {
  std::vector<char> map_line_char;
  map_line_char.reserve(16);
  for (int i = 0; i < 16; i++) {
    map_line_char.push_back(map_line.at(i));
  }
  map_.push_back(map_line_char);
}

std::string Map::GetMapLabels() {
  std::string ish;
  for (int i = 0; i < map_labels_.size(); i++) {
    if (i == screen_num_) {
      std::cout<<map_labels_[i]<<std::endl;
      //return map_labels_[i];
      ish = map_labels_[i];
    }
  }
  return ish;
}

std::vector<Map> Map::GetScreen() {
  return game_maps_;
}

bool Map::IsScreenChange() {
  return is_screen_change_;
}

int Map::GetNewScreenNum() {
  return screen_num_;
}

Location Map::GetPlayerNewLoc(const Map& curr_map, Engine engine) {
  Location loc = engine.GetPrisoner().GetLoc();
  int curr_row = loc.Col();
  int curr_col = loc.Row();

  for (int j = 0; j < entry_points_.size(); j++) {
    if (curr_map.coordinates_[curr_row][curr_col] == entry_points_.at(j)) {
      screen_num_ = GetTransitionScreenNum(GetCurrScreenNum(curr_map),
                                           entry_points_.at(j));
      is_screen_change_ = true;

      if (engine.GetDirection() == Direction::kUp) {
        return {curr_col, 1};
      } else if (engine.GetDirection() == Direction::kDown) {
        return {curr_col, 2};
      } else if (engine.GetDirection() == Direction::kLeft) {
        return {14, curr_row};
      } else if (engine.GetDirection() == Direction::kRight){
        return {2, curr_row - 2};
      }
    }
  }
  return loc;
}

int Map::GetCurrScreenNum(const Map& curr_map) {
  int count = 0;
  for (int i = 0; i < game_maps_.size(); i++) {
    for (int j = 0; j < 16; j++) {
      for (int k = 0; k < 16; k++) {
        if (game_maps_[i].coordinates_[j][k] == curr_map.coordinates_[j][k]) {
          count++;
        } else {
          count = 0;
          goto outerloop;
        }
        if (count == 256) {
          return i;
        }
      }
    }
    outerloop:;
  }
    //return 0;
}

int Map::GetTransitionScreenNum(int num, char entry) {
  for (int i = 0; i < game_maps_.size(); i++) {
    if (i != num) {
      for (int j = 0; j < 16; j++) {
        for (int k = 0; k < 16; k++) {
          if (game_maps_[i].coordinates_[j][k] == entry) {
            return i;
          }
        }
      }
    }
  }
}

}  // namespace mylibrary

