# Prison Break - CS 126 Final Project

This project was made as a part of CS 126 Final Project under the guidance of Prof. Michael J Woodley at the University
of Illinois Urbana-Champaign.

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Dev Wadhwa - [`devjw2@illinois.edu`](mailto:devjw2@illinois.edu)

---------------------
## About

My project is an adaptation of a maze runner game the developer played in his childhood. The point is to
run as fast and possible and reach the end of the maze, while enjoying the different screens the player is in.

## Dependencies

* [Cinder 0.9.2](https://github.com/cinder/Cinder/releases)
* [CMake](https://cmake.org/download/)
* [Catch2](https://github.com/catchorg/Catch2.git) 
* clang/clang++

## External Libraries/Third-party Libraries
For the implementation of this game, I will be using a couple of external/third-party libraries listed below:

* [ciAnimatedGif](https://github.com/cwhitney/ciAnimatedGif)
* [Cinder-SoundPlayer](https://github.com/redpaperheart/Cinder-SoundPlayer)

# Installation

1. [Install Visual Studio from here](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2017).
2. [Download Cinder 0.9.2 from here](https://libcinder.org/download).
3. Follow the setup guide to set up [Cinder + Git](https://libcinder.org/docs/guides/git/index.html). 
3. Install [SQLiteModernCpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp) and [SQLite3](https://github.com/alex85k/sqlite3-cmake) 
and follow [these instructions](http://srombauts.github.io/SQLiteCpp/) to add these libraries to the CMake files. 
4. [Clone](https://github.com/CS126SP20/final-project-devjwadhwa.git) this repository using git clone.
5. Build and run the project from Visual Studio. 


## Game Controls

#### Keyboard

| Key                    | Action                                                      |
|------------------------|-------------------------------------------------------------|
| `W / Up arrow key`     | Move up                                                     |
| `A / Left arrow key`   | Move left                                                   |
| `S / Down arrow key`   | Move down                                                   |
| `D / Right arrow key`  | Move right                                                  |
| `h`                    | Interact with the Game Screen                               |
| `SPACE`                | Pause or Play Music                                         |
