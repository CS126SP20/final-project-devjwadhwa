// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/prisoner.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  mylibrary::Engine engine_;

 private:
  void DrawBoard();
  void DrawPrisoner();
  void PlayBackgroundMusic();
  bool is_up_valid;
  bool is_down_valid;
  bool is_left_valid;
  bool is_right_valid;


};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
