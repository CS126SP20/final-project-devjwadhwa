// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H_
#define FINALPROJECT_ENGINE_H_

#include "direction.h"
#include "cursor.h"

namespace mylibrary {

class Engine {
 public:
  // Creates a new chess game of the given size.
  Engine(int width, int height);

  // Executes a time step: moves the ches, etc.
  void Step();

  // Changes the direction of the chess for the next time step.
  void SetDirection(Direction);

  Player GetPlayer() const;


 private:
  Player cursor_;
  Direction direction_;
  Direction last_direction_;
  const int width_;
  const int height_;
};


}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
