// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>

#include <cinder/audio/Voice.h>


#include <mylibrary/direction.h>
#include <mylibrary/engine.h>
#include <mylibrary/cursor.h>


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
  void DrawCursor();
  void PlayBackgroundMusic();

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
