// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.
#include <stdexcept>

#include <mylibrary/direction.h>
#include <mylibrary/location.h>
#include <mylibrary/engine.h>

namespace mylibrary {

// Converts a direction into a delta location.
Location FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return {-1, 0};
    case Direction::kDown:
      return {+1, 0};
    case Direction::kLeft:
      return {0, -1};
    case Direction::kRight:
      return {0, +1};
  }

  throw std::out_of_range("switch statement not matched");
}

Prisoner Engine::GetPrisoner() const {
  return prisoner_;
}

Engine::Engine(int width, int height)
  : width_(width),
    height_(height),
    prisoner_(Location(0,0)){}

void Engine::Step() {
  Location d_loc = FromDirection(direction_);
  Location new_head_loc =
      (prisoner_.GetLoc() + d_loc) % Location(height_, width_);

  Location leader = new_head_loc;
  prisoner_.SetLoc(leader);

  last_direction_ = direction_;
}

void Engine::SetDirection(const mylibrary::Direction direction) {
  direction_ = direction;
}




}  // namespace mylibrary