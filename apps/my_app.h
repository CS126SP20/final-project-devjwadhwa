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
  mylibrary::Engine game_engine_;
  mylibrary::Map game_mapper_;
  int prisoner_dir;

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
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
