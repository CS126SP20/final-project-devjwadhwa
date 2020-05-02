// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>

#include <cinder/gl/gl.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Rectf;
using mylibrary::Direction;
using mylibrary::Location;

cinder::audio::VoiceRef music_background;

int map_key = 0;

const int kWidth = 16;
const int kHeight = 16;
const int kTile = 50;

int step_up = 0;
int step_down = 0;
int step_left = 0;
int step_right = 0;

bool is_up_valid = true;
bool is_down_valid = true;
bool is_left_valid = true;
bool is_right_valid = true;

cinder::fs::path image_path;
cinder::fs::path current_map;


MyApp::MyApp() : engine_(kWidth, kHeight) {}

void MyApp::setup() {
  cinder::gl::disableDepthRead();
  cinder::gl::disableDepthWrite();
  current_map = "Intro.png";
  mapper.ReadBackgroundImages();
  mapper.ReadMaps();
  prisoner_dir = 0;
  PlayBackgroundMusic();
}

void MyApp::update() {
  Location location = engine_.GetPrisoner().GetLoc();
  int curr_col = location.Row();
  int curr_row = location.Col();
  Location player_parallel_loc =
      mapper.GetPlayerParallelLoc(mapper.GetMaps()[map_key],engine_);
  current_map = mapper.GetBackgroundKeys();
  map_key = mapper.GetParallelMapNum();

  ResetLoc(player_parallel_loc);


  is_up_valid =
      mapper.GetMaps()[map_key].cartesian[curr_row - 1][curr_col] != '1';
  is_down_valid =
      mapper.GetMaps()[map_key].cartesian[curr_row + 1][curr_col] != '1';
  is_left_valid =
      mapper.GetMaps()[map_key].cartesian[curr_row][curr_col - 1] != '1';
  is_right_valid =
      mapper.GetMaps()[map_key].cartesian[curr_row][curr_col + 1] != '1';

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
      CheckMoveValidity(event);
      prisoner_dir = static_cast<int>(Direction::kDown);
      step_down++;
      DrawPrisoner();
      engine_.Step();
      break;
    }

    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      CheckMoveValidity(event);
      prisoner_dir = static_cast<int>(Direction::kUp);
      step_up++;
      DrawPrisoner();
      engine_.Step();
      break;
    }

    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      CheckMoveValidity(event);
      prisoner_dir = static_cast<int>(Direction::kLeft);
      step_left++;
      DrawPrisoner();
      engine_.Step();
      break;
    }

    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      CheckMoveValidity(event);
      prisoner_dir = static_cast<int>(Direction::kRight);
      step_right++;
      DrawPrisoner();
      engine_.Step();
      break;
    }
  }
}


void MyApp::CheckMoveValidity(const cinder::app::KeyEvent& event) {

  if (is_down_valid &&
      event.getCode() == KeyEvent::KEY_DOWN ||
      event.getCode() == KeyEvent::KEY_s) {
    engine_.SetDirection(Direction::kDown);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_up_valid &&
      event.getCode() == KeyEvent::KEY_UP ||
      event.getCode() == KeyEvent::KEY_w) {
    engine_.SetDirection(Direction::kUp);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_left_valid &&
      event.getCode() == KeyEvent::KEY_LEFT ||
      event.getCode() == KeyEvent::KEY_a) {
    engine_.SetDirection(Direction::kLeft);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }

  if (is_right_valid &&
      event.getCode() == KeyEvent::KEY_RIGHT ||
      event.getCode() == KeyEvent::KEY_d) {
    engine_.SetDirection(Direction::kRight);
    return;
  } else {
    engine_.SetDirection(Direction::kNull);
  }
}

void MyApp::DrawPrisoner() {
  cinder::gl::color(1, 1, 0);
  const Location loc = engine_.GetPrisoner().GetLoc();

  if (prisoner_dir == static_cast<int>(Direction::kDown)) {
    if (step_down % 2 == 1) {
      image_path = cinder::fs::path("down_1.png");
    } else {
      image_path = cinder::fs::path("down_2.png");
    }

  } else if (prisoner_dir == static_cast<int>(Direction::kUp)) {
    if (step_up % 2 == 1) {
      image_path = cinder::fs::path("up_1.png");
    } else {
      image_path = cinder::fs::path("up_2.png");
    }

  } else if (prisoner_dir == static_cast<int>(Direction::kLeft)) {
    if (step_left % 2 == 1) {
      image_path = cinder::fs::path("left_1.png");
    } else {
      image_path = cinder::fs::path("left_2.png");
    }

  } else if (prisoner_dir == static_cast<int>(Direction::kRight)) {
    if (step_right % 2 == 1) {
      image_path = cinder::fs::path("right_1.png");
    } else {
      image_path = cinder::fs::path("right_2.png");
    }
  }

  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage
                                    (loadAsset(image_path)));
  cinder::gl::draw(tex,
                   Rectf(kTile * loc.Row(),
                         kTile * loc.Col(),
                         kTile * loc.Row() + kTile,
                         kTile * loc.Col() + kTile));
}

void MyApp::DrawBoard() {
  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage
                                  (loadAsset(current_map)));
  cinder::gl::draw(tex, getWindowBounds());
}

void MyApp::PlayBackgroundMusic() {
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("back.mp3"));
  music_background = cinder::audio::Voice::create(sourceFile);

  music_background->start();
}

void MyApp::ResetLoc(Location location) {
  if (mapper.IsScreenChange()) {

    engine_.Reset(location);
  }
}

}  // namespace myapp
