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

}  // namespace mylibrary

