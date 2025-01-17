// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

#include <cstddef>
#include <iostream>

namespace mylibrary {

class Location {

  // Represents a location on the board.
 public:
  Location(int row, int col);

  /**
   * Comparison operator.
   *
   * @param rhs Other location
   *
   * @return New location
   */
  bool operator==(const Location& rhs) const;

  /**
   * Addition operator.
   *
   * @param rhs Other location
   *
   * @return New location
   */
  Location operator+(const Location& rhs) const;

  /**
   * Modulus operator.
   *
   * @param rhs :mOther location
   *
   * @return New location
   */
  Location operator%(const Location& rhs) const;

  /**
   * Row accessor.
   *
   * @return Row
   */
  int Row() const;

  /**
   * Column accessor.
   *
   * @return Column
   */
  int Col() const;

 private:
  /**
   * Row of the Location.
   */
  int row_;

  /**
   * Column of the Location.
   */
  int col_;
};

}  // namespace mylibrary

#endif  // FINALPROJECT_LOCATION_H

