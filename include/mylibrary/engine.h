// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H_
#define FINALPROJECT_ENGINE_H_

#include "direction.h"
#include "prisoner.h"

namespace mylibrary {

class Engine {
 public:
  // Creates a new window of the given size.
  Engine(int width, int height);

  // Executes a time step: moves the prisoner, etc.
  void Step();

  // Changes the direction of the prisoner for the next time step.
  void SetDirection(Direction);

  Prisoner GetPrisoner() const;


 private:
  Prisoner prisoner_;
  Direction direction_;
  Direction last_direction_;
  const int width_;
  const int height_;
};


}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
