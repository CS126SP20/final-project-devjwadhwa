// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>
#include "location.h"

namespace mylibrary {

class Prisoner {
 public:
  /**
   * Explicit Constructor.
   *
   * @param location : Location of player
   */
  explicit Prisoner(Location location)
      : loc_(location){}

  /**
   * Setter for Location.
   *
   * @param set_loc : Input location
   */
  void SetLoc(Location set_loc) {
    loc_ = set_loc;
  }

  /**
   * Getter for Location.
   *
   * @return location
   */
  Location GetLoc() const {
    return loc_;
  }

 private:
  /**
   * Location object
   */
  Location loc_;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_PLAYER_H
