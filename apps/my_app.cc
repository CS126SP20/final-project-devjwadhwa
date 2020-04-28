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

    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kDown);
      prisoner_dir = static_cast<int>(Direction::kDown);
      step_down++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kUp);
      prisoner_dir = static_cast<int>(Direction::kUp);
      step_up++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kLeft);
      prisoner_dir = static_cast<int>(Direction::kLeft);
      step_left++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kRight);
      prisoner_dir = static_cast<int>(Direction::kRight);
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

  if (prisoner_dir == static_cast<int>(Direction::kDown)) {
    std::cout<<"Down"<<std::endl;
    std::cout<<loc.Row()<<std::endl;
    std::cout<<loc.Col()<<std::endl;
    if (step_down % 2 == 1) {
      image_path = cinder::fs::path("down_1.png");
    } else {
      image_path = cinder::fs::path("down_2.png");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kUp)) {
    std::cout<<"Up"<<std::endl;
    std::cout<<loc.Row()<<std::endl;
    std::cout<<loc.Col()<<std::endl;
    if (step_up % 2 == 1) {
      image_path = cinder::fs::path("up_1.png");
    } else {
      image_path = cinder::fs::path("up_2.png");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kLeft)) {
    std::cout<<"Left"<<std::endl;
    std::cout<<loc.Row()<<std::endl;
    std::cout<<loc.Col()<<std::endl;
    if (step_left % 2 == 1) {
      image_path = cinder::fs::path("left_1.png");
    } else {
      image_path = cinder::fs::path("left_2.png");
    }
  } else if (prisoner_dir == static_cast<int>(Direction::kRight)) {
    std::cout<<"Right"<<std::endl;
    std::cout<<loc.Row()<<std::endl;
    std::cout<<loc.Col()<<std::endl;
    if (step_right % 2 == 1) {
      image_path = cinder::fs::path("right_1.png");
    } else {
      image_path = cinder::fs::path("right_2.png");
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
  std::cout<<"Dev is studpid"<<std::endl;
  std::ifstream fileInput;
  fileInput.open(R"(C:\Users\devjw\CLionProjects\cinder_0.9.2_vc2015\projects\Break\assets\maze1.txt)");


  if ( !fileInput.is_open() ) return; //if the file didn't open correctly, quit the function

  while ( !fileInput.eof() ) //this is a viable option now
  {
    for (int i = 0 ; i < 16; i++)
    {
      for (int j = 0 ; j < 16; j++) //you had the incorrect const here originally.
      {
        fileInput >> maze[i][j];
      }
    }
  }

  fileInput.close();

  for (int i = 0; i < 16; i++)
  {
    for (int j = 0; j < 16; j++)
    {
      std::cout << maze[i][j] << " "; //space between columns
    }
    std::cout << std::endl; //newlines for rows
  }
  std::cout<<maze[14][15]<<std::endl;
  std::cout<<maze[13][15]<<std::endl;
  std::cout<<maze[14][14]<<std::endl;
  std::cout<<maze[13][14]<<std::endl;

  std::cout<<maze[3][2]<<std::endl;
}


}  // namespace myapp
