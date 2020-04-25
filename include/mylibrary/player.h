// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>
#include "location.h"

namespace mylibrary {

class Player {
 public:
  Player(const std::string& name, int score, Location location)
      : name_(name),score_(score), loc_(location){}

  void SetLoc(Location set_loc) {
    loc_ = set_loc;
  }

  Location GetLoc() const {
    return loc_;
  }

  std::string name_;
  int score_;

 private:
  Location loc_;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_PLAYER_H
