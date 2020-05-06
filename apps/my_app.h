// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/prisoner.h>
#include <mylibrary/map.h>
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

namespace myapp {

class MyApp : public cinder::app::App {

 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  /**
   * Dimension of screen
   */
  const int kDimension = 16;

  /**
   * Tile Size for the game
   */
  const int kTile = 50;

  /*
   * Object of Game Engine class
   */
  mylibrary::Engine game_engine_;

  /**
   * Object of Map class
   */
  mylibrary::Map game_map_;

  /**
   * Constant which decides the direction state of the prisoner
   */
  int prisoner_direction;

  /**
   * The map key
   */
  int map_key = 0;

  /**
   * Initializing number of steps in each direction
   */
  int step_up = 0;
  int step_down = 0;
  int step_left = 0;
  int step_right = 0;

  /**
    * Initializing validity of movement in each direction
    */
  bool is_up_valid = true;
  bool is_down_valid = true;
  bool is_left_valid = true;
  bool is_right_valid = true;


  /**
   * Bool for if user wants to interact
   */
  bool draw_textbox = false;

  /**
   * A counter for drawing textbox
   */
  int draw_textbox_count = 0;

  /**
   * Path for the prisoner image
   */
  cinder::fs::path image_path;

  /**
   * The current map
   */
  std::string current_map;

  /**
   * Audio ref for background music
   */
  cinder::audio::VoiceRef music_background;

  /**
   * Interactive Text for each map
   */
  std::string intro = "Intro boy";
  std::string jail = "Jail boy";
  std::string tunnel = "Tunnel boy";
  std::string maze1 = "Maze1 boy";
  std::string maze2 = "Maze2 boy";
  std::string maze3 = "Maze3 boy";
  std::string maze4 = "Maze4";
  std::string maze5 = "Maze5";

  /**
   * End game and Game over Text
   */
  std::string game_over = "Game Over";
  std::string game_win = "You Win";

  /**
   * Time For Winning
   */
  int win_time = 120;

 private:
  /**
   * Draws the then background of the scene
   */
  void DrawBackground();

  /**
   * Draws the prisoner according to it's direction and step
   */
  void DrawPrisoner();

  /**
   * Plays the background music
   */
  void PlayBackgroundMusic();

  /**
   * Checks if it is allowed to move in a particular direction
   *
   * @param event : They key pressed ny the player
   */
  void CheckMoveValidity(const cinder::app::KeyEvent& event);

  /**
   * Resets the location of the player in a parallel world
   *
   * @param location : the new location of the player
   */
  void ResetLoc(mylibrary::Location location);

  /**
   * Let's the user interact with the Screen
   *
   * @param map : The current map
   */
  void DrawInteractiveText(std::string map);

  /**
   * Draws the end game
   */
  void DrawEndGameScreen();

  /**
   * Draws a timer for the game
   */
  void DrawTimer() const;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
