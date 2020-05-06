# CS 126 Final Project Proposal - Prison Break

Author: Dev Wadhwa

---

### Project Description:
 My project will be an implementation of a Prison Break.
 The objective of this game is to get out of the prison maze as soon as possible.  
    
### Motivation:
 Prison Break is an implementation of Maze Runner, a game the author played while growing up with his elder brother.
 Thus, he always wanted to try to code since he learnt coding in CS 125.
 The sentimental value attached to it is the main driving factor.  

### Tentative Timeline:

#### Week 2 (starting 04/26 - new project) - 

##### Engine: 
* Setup of external libraries 
* Key movement code
* A character which appears to move
* A set of maps (txt or json)

##### Graphics: 
* Displaying the first map
* Images of all the maps
* The Character
* Character's ability to run
* Key Movement

#### Week 3 - 
##### Engine: 
* Changes screens
* Reject invalid moves (e.g. moving through walls)
* Notes the Time taken by the player
* Detect when Player wins
* Detect when Game is over

##### Graphics: 
Development of :-
* Game over screen
* Game win screen

## External Libraries

1. [SqliteModernCpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp) 
    The C++14 wrapper around sqlite library - sqlite_modern_cpp and sqlite3.
2. [Json](https://github.com/nlohmann/json) for the maps.
3. [Cinder-UI](https://github.com/rezaali/Cinder-UI) if needed to debug UI controls.
4. [gflags](https://github.com/gflags/gflags) for Command-Line arguments.
5. [Sound player](https://github.com/redpaperheart/Cinder-SoundPlayer) for Sound PLayer.

## Extensions/Extras
* Addition of policemen (monsters)
* Implementation of barriers to delay the player 
* Having a timer instead of a stopwatch
* Addition of a teleporter in a map