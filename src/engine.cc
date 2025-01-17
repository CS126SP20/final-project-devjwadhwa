// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.
#include <stdexcept>

#include <mylibrary/direction.h>
#include <mylibrary/location.h>
#include <mylibrary/engine.h>

namespace mylibrary {

Engine::Engine(int width, int height)
    : width_(width),
      height_(height),
      direction_(Direction::kUp),
      last_direction_(Direction::kUp),
      prisoner_(Location(7,10)) {
}

// Converts a direction into a delta location (Inspired from Snake)
Location Engine::FromDirection(const Direction direction) {
  switch (direction) {
    case Direction::kLeft:
      return {-1, 0};
    case Direction::kRight:
      return {+1, 0};
    case Direction::kUp:
      return {0, -1};
    case Direction::kDown:
      return {0, +1};
    case Direction::kNull:
      return {0,0};
  }

  throw std::out_of_range("switch statement not matched");
}

Prisoner Engine::GetPrisoner() const {
  return prisoner_;
}

void Engine::Step() {
  // Inspired from Snake
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

Direction Engine::GetDirection() {
  return direction_;
}

void Engine::Reset(Location location) {
  prisoner_.SetLoc(location);
}

}  // namespace mylibrary