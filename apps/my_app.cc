// Copyright (c) 2020 [Dev Wadhwa]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>
#include <cinder/Color.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>

namespace myapp {

using cinder::Rectf;
using cinder::app::KeyEvent;
using cinder::TextBox;

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

int draw_textbox_count = 0;

std::clock_t c_start = std::clock();


// Initializing validity of movement in each direction
bool is_up_valid = true;
bool is_down_valid = true;
bool is_left_valid = true;
bool is_right_valid = true;

bool draw_textbox = false;

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
  DrawTextbox(current_map);
  DrawTimer();
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

    case KeyEvent::KEY_h: {
      draw_textbox = true;
      draw_textbox_count++;
      DrawTextbox(current_map);
      break;
    }
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

template <typename C>
void PrintText(const std::string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font("Cooper Black", 40))
      .size(size)
      .color(color)
      .backgroundColor(cinder::ColorA(0,0,0,0.6))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawBackground() {
  // Current map changes when screen changes
  cinder::gl::Texture2dRef tex =
      cinder::gl::Texture2d::create(loadImage
                                  (loadAsset(current_map + ".png")));
  cinder::gl::draw(tex);
}

void MyApp::DrawTextbox(std::string map) {
  if (draw_textbox) {
    if (draw_textbox_count % 2 == 1) {

      std::string text = Intro;
      if (map == "jail") {
        text = jail;
      } else if (map == "tunnel") {
        text = tunnel;
      } else if (map == "maze1") {
        text = maze1;
      } else if (map == "maze2") {
        text = maze2;
      }

      const cinder::Color color = {1, 1, 1};
      const cinder::ivec2 size = {600, 200};
      const cinder::vec2 loc = {400, 600};

      PrintText(text, color, size, loc);

      // Stops the player from moving when the textbox is on
      is_up_valid = false;
      is_down_valid = false;
      is_left_valid = false;
      is_right_valid = false;

    }
  }
}

void MyApp::DrawTimer() const {
  std::clock_t c_end = std::clock();
  const std::string text = (std::to_string(int ((c_end - c_start)/1000)));
  const cinder::Color color = {255, 255, 0};
  const cinder::ivec2 size = {50, 50};
  const cinder::vec2 loc = {400, 25};

  PrintText(text, color, size, loc);
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


//void MyApp::DrawEndGame(std::string map) const {
//  if (map == "maze2") {
//    const std::string text = std::to_string(time_left_);
//    const Color color = {1, 1, 1};
//    const cinder::ivec2 size = {50, 50};
//    const cinder::vec2 loc = {50, 50};
//
//    PrintText(text, color, size, loc);
//  }
//}

}  // namespace myapp
