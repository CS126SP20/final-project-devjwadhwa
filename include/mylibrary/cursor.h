// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>
#include "location.h"

namespace mylibrary {

class Cursor {
 public:
  Cursor(Location location)
      : loc_(location){}

  void SetLoc(Location set_loc) {
    loc_ = set_loc;
  }

  Location GetLoc() const {
    return loc_;
  }

 private:
  Location loc_;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_PLAYER_H
