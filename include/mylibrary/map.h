// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved

#ifndef FINALPROJECT_MAP_H
#define FINALPROJECT_MAP_H

#include <mylibrary/engine.h>
#include <string>
#include <vector>


namespace mylibrary {
using mylibrary::Engine;


class Map {
 public:
  /**
   * A cartesian system for the board
   */
  char cartesian[16][16]{};

 public:
  /**
   * Constructor
   */
  Map();

  /**
   * Explicit Constructor setting the cartesian to the game screen
   *
   * @param game_map : The current Game Map
   */
  explicit Map(std::vector<std::vector<char>> game_map);

  /**
   * Reads all background images from the txt file
   */
  void ReadBackgroundImagesFile();

  /**
   * Reads all maps from the text file
   */
  void ReadMapsFile();

  /**
  * Gets all the maps
  *
  * @return A vector containing all the maps
  */
  std::vector<Map> GetAllMaps();

  /**
   * Sets up map line by line
   *
   * @param map_line : One line of the map
   */
  void SetupMap(std::string map_line);

  /**
  * Gets the current map's string name
  * @return The name
  */
  std::string GetCurrentMapName();

  /**
   * Gets the current map's key
   *
   * @param current_map : Current Map
   *
   * @return The Key
   */
  int GetCurrentMapKey(const Map& current_map);

  /**
   * Gets the parallel map's key
   *
   * @param key : Current Map's Key
   * @param door : Any exit point
   *
   * @return Parallel map's key
   */
  int GetParallelMapKey(int key, char door);

  /**
   * Gets the Location of the Prisoner in the Parallel Map
   *
   * @param current_map : The current Map
   * @param engine : The game engine
   *
   * @return The location of the Prisoner
   */
  Location GetParallelMapLoc(const Map& current_map, Engine engine);

  /**
   * Gets the Parallel map's number
   *
   * @return The number
   */
  int GetParallelMapNum();

  /**
   * Bool which tells if the screen is changing
   *
   * @return True if the screen changes
   */
  bool IsScreenChange();

 private:
  /**
   * Dimension of the board.
   */
  const int kDimension = 16;

  /**
   * Constant for reallocating the Prisoner a position.
   */
  const int kLoc = 2;

  /**
   * Screen number
   */
  int parallel_map_num{};

  /**
   * Vector of strings saving every background image
   */
  std::vector<std::string> background_images;

  /**
   * True if there is a change of screen
   */
  bool is_screen_change_ = false;

  /**
   * Vector of Maps saving all the individual maps
   */
  std::vector<mylibrary::Map> all_maps;

  /**
   * Vector of char saving each map
   */
  std::vector<std::vector<char>> map;

  /**
   * Exit and entry points
   */
  std::string exits = "abcdefghi";
};

}  // namespace mylibrary

#endif  // FINALPROJECT_MAP_H
