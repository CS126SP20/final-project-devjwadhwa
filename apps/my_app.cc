// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::Rectf;
using cinder::app::KeyEvent;

using mylibrary::Direction;
using mylibrary::Location;

cinder::audio::VoiceRef music_background;

int map_key = 0;

const int kDimension = 16;
const int kTile = 50;

// Initializing number of steps in each direction
int step_up = 0;
int step_down = 0;
int step_left = 0;
int step_right = 0;

// Initializing validity of movement in each direction
bool is_up_valid = true;
bool is_down_valid = true;
bool is_left_valid = true;
bool is_right_valid = true;

cinder::fs::path image_path;
std::string current_map;

MyApp::MyApp() : game_engine_(kDimension, kDimension) {}

void MyApp::setup() {
  // Reads all maps and background images
  game_mapper_.ReadBackgroundImages();
  game_mapper_.ReadMaps();
  // Initializing prisoner direction
  prisoner_dir_state = static_cast<int>(Direction::kDown);
  PlayBackgroundMusic();
}

void MyApp::update() {
  // Gets the location of the character in the current map
  Location location = game_engine_.GetPrisoner().GetLoc();
  int curr_col = location.Row();
  int curr_row = location.Col();

  // Gets the location of the character in the parallel map
  Location player_parallel_loc =
      game_mapper_.GetPlayerParallelLoc(game_mapper_.GetMaps()[map_key],
                                  game_engine_);

  // Gets the key to the current map
  current_map = game_mapper_.GetBackgroundKey();

  // Gets the key to the parallel map
  map_key = game_mapper_.GetParallelMapNum();

  // Resets the location of the player in the parallel map
  ResetLoc(player_parallel_loc);

  // TODO:: Try the below in a function
  // Checks if the next move is into a wall
  is_up_valid =
      game_mapper_.GetMaps()[map_key].cartesian[curr_row - 1][curr_col] != '1';
  is_down_valid =
      game_mapper_.GetMaps()[map_key].cartesian[curr_row + 1][curr_col] != '1';
  is_left_valid =
      game_mapper_.GetMaps()[map_key].cartesian[curr_row][curr_col - 1] != '1';
  is_right_valid =
      game_mapper_.GetMaps()[map_key].cartesian[curr_row][curr_col + 1] != '1';
}

void MyApp::draw() {
  cinder::gl::enableAlphaBlending();
  cinder::gl::clear();
  cinder::gl::color(1,1,1);
  DrawBackground();
  DrawPrisoner();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {

    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_s: {
      CheckMoveValidity(event);
      prisoner_dir_state = static_cast<int>(Direction::kDown);
      step_down++;
      DrawPrisoner();
      game_engine_.Step();
      break;
    }

    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_w: {
      CheckMoveValidity(event);
      prisoner_dir_state = static_cast<int>(Direction::kUp);
      step_up++;
      DrawPrisoner();
      game_engine_.Step();
      break;
    }

    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_a: {
      CheckMoveValidity(event);
      prisoner_dir_state = static_cast<int>(Direction::kLeft);
      step_left++;
      DrawPrisoner();
      game_engine_.Step();
      break;
    }

    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_d: {
      CheckMoveValidity(event);
      prisoner_dir_state = static_cast<int>(Direction::kRight);
      step_right++;
      DrawPrisoner();
      game_engine_.Step();
      break;
    }
    /*
    case KeyEvent::KEY_h: {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.y = 10;//upwards - don't change x velocity
        body->SetLinearVelocity( vel );
      }
      break;
      */
  }
}


void MyApp::CheckMoveValidity(const cinder::app::KeyEvent& event) {

  if (is_down_valid &&
      event.getCode() == KeyEvent::KEY_DOWN ||
      event.getCode() == KeyEvent::KEY_s) {
    game_engine_.SetDirection(Direction::kDown);
    return;
  } else {
    game_engine_.SetDirection(Direction::kNull);
  }

  if (is_up_valid &&
      event.getCode() == KeyEvent::KEY_UP ||
      event.getCode() == KeyEvent::KEY_w) {
    game_engine_.SetDirection(Direction::kUp);
    return;
  } else {
    game_engine_.SetDirection(Direction::kNull);
  }

  if (is_left_valid &&
      event.getCode() == KeyEvent::KEY_LEFT ||
      event.getCode() == KeyEvent::KEY_a) {
    game_engine_.SetDirection(Direction::kLeft);
    return;
  } else {
    game_engine_.SetDirection(Direction::kNull);
  }

  if (is_right_valid &&
      event.getCode() == KeyEvent::KEY_RIGHT ||
      event.getCode() == KeyEvent::KEY_d) {
    game_engine_.SetDirection(Direction::kRight);
    return;
  } else {
    game_engine_.SetDirection(Direction::kNull);
  }
}

// TODO:: Optimize DrawPrisoner conditions
void MyApp::DrawPrisoner() {
  cinder::gl::color(1, 1, 0);
  const Location loc = game_engine_.GetPrisoner().GetLoc();

  if (prisoner_dir_state == static_cast<int>(Direction::kDown)) {
    if (step_down % 2 == 1) {
      image_path = cinder::fs::path("down_1.png");
    } else {
      image_path = cinder::fs::path("down_2.png");
    }

  } else if (prisoner_dir_state == static_cast<int>(Direction::kUp)) {
    if (step_up % 2 == 1) {
      image_path = cinder::fs::path("up_1.png");
    } else {
      image_path = cinder::fs::path("up_2.png");
    }

  } else if (prisoner_dir_state == static_cast<int>(Direction::kLeft)) {
    if (step_left % 2 == 1) {
      image_path = cinder::fs::path("left_1.png");
     } else {
       image_path = cinder::fs::path("left_2.png");
    }

  } else if (prisoner_dir_state == static_cast<int>(Direction::kRight)) {
    if (step_right % 2 == 1) {
      image_path = cinder::fs::path("right_1.png");
    } else {
      image_path = cinder::fs::path("right_2.png");
    }
  }

  // Image path changes with direction and step
  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage
                                    (loadAsset(image_path)));

  cinder::gl::draw(tex,
                   Rectf(kTile * loc.Row(),
                         kTile * loc.Col(),
                         kTile * loc.Row() + kTile,
                         kTile * loc.Col() + kTile));
}

void MyApp::DrawBackground() {
  // Current map changes when screen changes
  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage
                                  (loadAsset(current_map)));
  cinder::gl::draw(tex);
}

void MyApp::PlayBackgroundMusic() {
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset ("background.mp3"));
  music_background = cinder::audio::Voice::create(sourceFile);

  music_background->start();
}

void MyApp::ResetLoc(Location location) {
  if (game_mapper_.IsScreenChange()) {
    game_engine_.Reset(location);
  }
}
}  // namespace myapp
