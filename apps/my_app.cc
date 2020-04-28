// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include "cinder/ImageIo.h"
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using mylibrary::Direction;
using mylibrary::Location;

cinder::audio::VoiceRef music_background;

const int kWidth = 16;
const int kHeight = 16;
const int kTile = 50;

int step_up = 0;
int step_down = 0;
int step_left = 0;
int step_right = 0;

cinder::fs::path image_path;

MyApp::MyApp() : engine_(kWidth, kHeight) {}

void MyApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  ReadMap();
  std::cout << "Dev" << std::endl;
  // IsUp = false;
  prisoner_dir = 0;

  PlayBackgroundMusic();
}

void MyApp::update() {
  Location location = engine_.GetPrisoner().GetLoc();
  int row_now = location.Row();
  int col_now = location.Col();

  // IsUp = false;
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(1,1,1);
  DrawBoard();
  DrawPrisoner();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      //IsUp = true;
      engine_.SetDirection(Direction::kLeft);
      prisoner_dir = static_cast<int>(Direction::kLeft);
      step_up++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kRight);
      prisoner_dir = static_cast<int>(Direction::kRight);
      step_down++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kUp);
      prisoner_dir = static_cast<int>(Direction::kUp);
      step_left++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kDown);
      prisoner_dir = static_cast<int>(Direction::kDown);
      step_right++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
  }
}

void MyApp::DrawPrisoner() {
  cinder::gl::color(1, 1, 0);
  const Location loc = engine_.GetPrisoner().GetLoc();

  if (prisoner_dir == static_cast<int>(Direction::kLeft)) {
    if (step_up % 2 == 1) {
      std::cout << step_up <<"u1"<<std::endl;
      image_path = cinder::fs::path("u1.jpg");
    } else {
      std::cout << step_up <<"u2"<< std::endl;
      image_path = cinder::fs::path("u3.jpg");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kRight)) {
    if (step_down % 2 == 1) {
      std::cout << step_down <<"u1"<<std::endl;
      image_path = cinder::fs::path("d1.jpg");
    } else {
      std::cout << step_down <<"u2"<< std::endl;
      image_path = cinder::fs::path("d3.jpg");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kUp)) {
    if (step_left % 2 == 1) {
      std::cout << step_left <<"l1"<<std::endl;
      image_path = cinder::fs::path("l1.jpg");
    } else {
      std::cout << step_left <<"l2"<< std::endl;
      image_path = cinder::fs::path("l3.jpg");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kDown)) {
    if (step_right % 2 == 1) {
      std::cout << step_right <<"r1"<<std::endl;
      image_path = cinder::fs::path("r1.jpg");
    } else {
      std::cout << step_right <<"r2"<< std::endl;
      image_path = cinder::fs::path("r3.jpg");
    }
  }

  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage(loadAsset(image_path)));
  cinder::gl::draw(tex,
                   Rectf(kTile * loc.Row(), kTile * loc.Col(),
                         kTile * loc.Row() + kTile, kTile * loc.Col() + kTile));
  image_path.clear();
}

void MyApp::DrawBoard() {
  cinder::gl::color(1, 1, 1);
  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture::create(loadImage(loadAsset("maze1.png")));
  cinder::gl::draw(tex);
}

void MyApp::PlayBackgroundMusic() {
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("back.mp3"));
  music_background = cinder::audio::Voice::create(sourceFile);

  music_background->start();
}
void MyApp::ReadMap() {
  std::cout<<"Dev is stu;pid"<<std::endl;

}
}  // namespace myapp
