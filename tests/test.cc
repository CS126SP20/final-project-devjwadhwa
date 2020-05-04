// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include <mylibrary/location.h>
#include <mylibrary/engine.h>
#include <mylibrary/direction.h>
#include <mylibrary/prisoner.h>
#include <mylibrary/map.h>

using mylibrary::Location;
using mylibrary::Engine;
using mylibrary::Direction;
using mylibrary::Prisoner;
using mylibrary::Map;

std::vector<std::vector<char>> test_screen =
    {{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
     {'1','1','1','1','1','1','1','1','1','1','1','1','0','0','0','c'},
     {'1','1','1','1','1','1','0','0','0','0','0','1','0','1','1','1'},
     {'1','1','1','1','1','1','0','1','1','1','0','1','0','0','1','1'},
     {'1','1','1','1','1','1','0','0','0','1','0','1','1','0','1','1'},
     {'1','1','1','1','1','1','1','1','0','1','0','1','0','0','1','1'},
     {'1','1','1','1','1','1','1','1','0','1','0','1','0','1','1','1'},
     {'1','1','0','0','0','0','0','1','0','1','0','1','0','0','1','1'},
     {'1','1','0','0','0','0','0','1','0','1','0','1','1','0','1','1'},
     {'b','0','0','1','1','1','0','1','0','1','0','1','0','0','1','1'},
     {'b','0','0','1','1','1','0','1','0','1','0','1','0','1','1','1'},
     {'1','1','1','1','1','1','0','1','0','1','0','1','0','0','1','1'},
     {'1','1','1','1','1','1','0','0','0','1','0','1','1','0','1','1'},
     {'1','1','1','1','1','1','1','1','1','1','0','0','0','0','1','1'},
     {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
     {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}};

Map test_map = Map(test_screen);

TEST_CASE("Location Operators", "[location]") {

  SECTION("Addition Operator") {
    Location initial(15,11);
    Location final(2,6);

    Location result = initial + final;
    REQUIRE(result == Location{17, 17});
  }

  SECTION("Equals Operator") {
    Location initial(15,11);
    Location final(15,11);

    REQUIRE(initial == final);
  }

  SECTION("Modulus Operator") {
    Location initial(15,11);
    Location final(2,6);

    Location result = initial % final;
    REQUIRE(result == Location{1, 5});
  }
}

TEST_CASE("Location Pointers", "[location]") {
  Location location{4,12};

  SECTION("Row Value") {
    int row = location.Row();
    REQUIRE(row == 4);
  }

  SECTION("Column Value") {
    int col = location.Col();
    REQUIRE(col == 12);
  }
}

TEST_CASE("Direction Change", "[engine][direction]") {
  int row = 9;
  int col = 11;

  Engine engine(row,col);

  SECTION("Initial Direction") {
    engine.Step();
    REQUIRE(engine.GetDirection() == Direction::kDown);
  }

  SECTION("Direction Up") {
    engine.SetDirection(Direction::kUp);
    REQUIRE(engine.GetDirection() == Direction::kUp);
  }

  SECTION("Direction Down") {
    engine.SetDirection(Direction::kDown);
    REQUIRE(engine.GetDirection() == Direction::kDown);
  }

  SECTION("Direction Right") {
    engine.SetDirection(Direction::kRight);
    REQUIRE(engine.GetDirection() == Direction::kRight);
  }

  SECTION("Direction Left") {
    engine.SetDirection(Direction::kLeft);
    REQUIRE(engine.GetDirection() == Direction::kLeft);
  }

  SECTION("Direction Null") {
    engine.SetDirection(Direction::kNull);
    REQUIRE(engine.GetDirection() == Direction::kNull);
  }
}

