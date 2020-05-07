// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <ciAnimatedGif.h>
#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/map.h>
#include <mylibrary/prisoner.h>
#include <rph/SoundPlayer.h>

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

  /**
   * Time For Winning
   */
  const int kWinTime = 75;

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
  rph::SoundPlayerRef mSound;

  /**
   * Interactive Text for each map
   */
  std::string intro = "Hello! Welcome to Prison Break!\n"
      "As the title says, your main objective is to break out of the prison in the SPECIFIED amount of time. But for now,\n"
      "Current Objective:\n"
      "Use WASD or arrow keys to walk to the door";

  std::string jail = "This is my prison cell. Isn’t it luxurious?\n"
      "\n"
      "Current Objective:\n"
      "Explore my prison cell. Once you’re done, head to the next door.";

  std::string tunnel = "I escaped? This is my gateway to freedom.\n"
      "\n"
      "Current Objective:\n"
      "Find the exit from the tunnel.";

  std::string maze1 = "This is my first maze. I need to get away before the police catch me. RUN\n"
      "\n"
      "Current Objective:\n"
      "Find the door which leads you out.";
  std::string maze2 = "This is my second maze. It looks LONG AND HARD \n"
      "\n"
      "Current Objective:\n"
      "Move in circles until you find the exit.";

  std::string maze3 = "This is the bridge. I see 2 princesses; shall I go pay my tributes?\n"
      "\n"
      "Current Objective: \n"
      "Find the right bridge which gets you out.";

  std::string maze4 = "Is this the last maze? I am incredibly tired. Why are there 3 doors?\n"
      "Could I be teleported?\n"
      "\n"
      "Current Objective:\n"
      "LEAVE. The Clock is ticking!";

  std::string end_screen = "Congratulations. You are finally out. Enjoy the fresh air and the luxury.";

  /**
   * End game and Game over Text
   */
  std::string game_over = "Game Over";
  std::string game_win = "You Win";

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

  /**
   * GIF object
   */
  ci::ciAnimatedGifRef cute_gif;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
