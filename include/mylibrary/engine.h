// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H_
#define FINALPROJECT_ENGINE_H_

#include "direction.h"
#include "prisoner.h"

namespace mylibrary {

class Engine {
 public:
  /**
   * Creates a new window of the given size.
   *
   * @param width : Width of the window
   * @param height : Height of the window
   */
  Engine(int width, int height);

  /**
   * Setting definitions for Steps
   *
   * @param direction : The direction the Prisoner is facing
   *
   * @return The new location
   */
  Location FromDirection(const Direction direction);

  /**
   * Getter for the Prisoner.
   *
   * @return the Prisoner
   */
  Prisoner GetPrisoner() const;

  /**
   * Executes a time step: moves the prisoner etc.
   */
  void Step();

  /**
   * Changes the direction of the prisoner for the next time step.
   */
  void SetDirection(Direction);

  /**
   * Getter for the Direction.
   *
   * @return the Direction
   */
  Direction GetDirection();

  /**
   * Reset the Prisoner's location to thr given one.
   *
   * @param location : The Rest location coordinates
   */
  void Reset(Location location);

 private:
  /**
   * Object of the Prisoner class.
   */
  Prisoner prisoner_;

  /**
   * Object of the current Direction class.
   */
  Direction direction_;

  /**
   * Object of the previous Direction class.
   */
  Direction last_direction_;

  /**
   * Width of the window.
   */
  const int width_;

  /**
   * Height of the window.
   */
  const int height_;
};

}  // namespace mylibrary

#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
