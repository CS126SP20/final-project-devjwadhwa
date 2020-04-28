// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H

#include <cstddef>
#include <iostream>

namespace mylibrary {

// Represents a location on the board.
class Location {
 public:
  Location(int row, int col);

  // Comparison operators.
  bool operator==(const Location& rhs) const;

  // Vector operators.
  Location operator+(const Location& rhs) const;
  // Note: Always returns positive coordinates.
  Location operator%(const Location& rhs) const;


  // Accessors.
  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;
};

std::ostream& operator<<(std::ostream& os, const Location& location);

}  // namespace mylibrary

#endif  // FINALPROJECT_LOCATION_H

