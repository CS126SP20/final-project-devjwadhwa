// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include "cinder/ImageIo.h"
#include <gflags/gflags.h>

using cinder::Rectf;
using mylibrary::Direction;

const int kWidth = 8;
const int kHeight = 8;
const int kTile = 50;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp()
    : engine_(kWidth, kHeight) {}

void MyApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
}

void MyApp::update() { }

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
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

}  // namespace myapp
