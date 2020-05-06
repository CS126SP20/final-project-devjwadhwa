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
    REQUIRE(engine.GetDirection() == Direction::kUp);
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

TEST_CASE("Location Change", "[engine][location][direction]") {
  int row = 0;
  int col = 0;

  Engine engine(row, col);

  SECTION("Step Up") {
    REQUIRE(engine.FromDirection(Direction::kUp) == Location{0, -1});
  }

  SECTION("Step Down") {
    REQUIRE(engine.FromDirection(Direction::kDown) == Location{0, +1});
  }

  SECTION("Step Right") {
    REQUIRE(engine.FromDirection(Direction::kRight) == Location{+1, 0});
  }

  SECTION("Step Left") {
    REQUIRE(engine.FromDirection(Direction::kLeft) == Location{-1, 0});
  }
}

TEST_CASE("Prisoner Location", "[prisoner][location][direction]") {
  Prisoner prisoner(Location{3, 4});

  SECTION("Prisoner Location") {
    REQUIRE(prisoner.GetLoc() == Location{3, 4});
  }

  SECTION("Prisoner Location with transportation") {
    prisoner.SetLoc(Location{12, 8});
    REQUIRE(prisoner.GetLoc() == Location{12, 8});
  }
}

TEST_CASE("Map keys and Map Screens", "[map][key][background]") {
  Map testing_map;
  testing_map.ReadBackgroundImagesFile();
  testing_map.ReadMapsFile();

  std::vector<Map> testing_map_screens = testing_map.GetAllMaps();

  SECTION("Number of Screens") { REQUIRE(testing_map_screens.size() == 5); }

  SECTION("Image Backgrounds") {
    std::string image_background = "intro.png";
    REQUIRE(testing_map.GetCurrentMapName() == image_background);
    REQUIRE(testing_map.GetParallelMapNum() == 0);
  }

  SECTION("Map Key") {
    int map_key = testing_map.GetCurrentMapKey(test_map);
    REQUIRE(map_key == 2);
  }
}

TEST_CASE("Screen Change", "[map][key][background]") {
  Map testing_map;
  testing_map.ReadBackgroundImagesFile();
  testing_map.ReadMapsFile();

  int row = 0;
  int col = 0;

  Engine testing_engine(row, col);
  Location test_loc = testing_map.GetParallelMapLoc(test_map, testing_engine);

  SECTION("No Screen Change") {
    REQUIRE(!testing_map.IsScreenChange());
  }

  SECTION("Intro Player Location") {
    REQUIRE(test_loc == Location(7,10));
  }

  testing_engine.Reset(Location(15, 1));
  Location new_location = testing_map.GetParallelMapLoc(test_map, testing_engine);

  SECTION("Screen Change") {
    REQUIRE(testing_map.IsScreenChange());
  }

  SECTION("New location") {
    REQUIRE(new_location == Location(15, 14));
  }

  SECTION("Change in map key") {
    int new_key = testing_map.GetParallelMapKey(4, 'd');
    REQUIRE(new_key == 3);
  }
}

