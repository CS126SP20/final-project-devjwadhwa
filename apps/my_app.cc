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

MyApp::MyApp()
    : engine_(kWidth, kHeight) {}

void MyApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();

  PlayBackgroundMusic();
}

void MyApp::update() {
  Location location = engine_.GetPrisoner().GetLoc();
  int row_now = location.Row();
  int col_now = location.Col();
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  DrawBoard();
  DrawPrisoner();

}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kLeft);
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kRight);
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kUp);
      engine_.Step();
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kDown);
      engine_.Step();
      break;
    }
  }
}

void MyApp::DrawPrisoner() {
  cinder::gl::color(1, 1, 0);
  mylibrary::Location location = engine_.GetPrisoner().GetLoc();
  cinder::fs::path image_path = cinder::fs::path("cursor.png");
  cinder::gl::Texture2dRef tex = cinder::gl::Texture2d::
      create(loadImage(cinder::app::loadAsset(image_path)));
  cinder::gl::draw(tex, Rectf (kTile * location.Row() - 2,
                               kTile * location.Col() - 2,
                               kTile * location.Row() + kTile + 1,
                               kTile * location.Col() + kTile + 1));
}

void MyApp::DrawBoard() {
  cinder::gl::color(1,1,1);
  cinder::gl::Texture2dRef tex = cinder::gl::Texture::
      create(loadImage(loadAsset("board.jpg")));
  cinder::gl::draw(tex);
}

void MyApp::PlayBackgroundMusic() {
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("back.mp3"));
  music_background = cinder::audio::Voice::create(sourceFile);

  music_background->start();
}

}  // namespace myapp
