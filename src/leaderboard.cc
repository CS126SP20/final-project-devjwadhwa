// Copyright (c) 2020 CS126SP20. All rights reserved.

#include <mylibrary/leaderboard.h>
#include <snake/prisoner.h>
#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace mylibrary {

using std::string;
using std::vector;

LeaderBoard::LeaderBoard(const string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name  TEXT NOT NULL,\n"
         "  score INTEGER NOT NULL\n"
         ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  db_ << "Insert into leaderboard (name,score) values (?,?);"
      << player.name
      << player.score;
}

vector<Player> GetPlayers(sqlite::database_binder* rows) {
  vector<Player> players;

  for (auto&& row : *rows) {
    string name;
    size_t score;
    row >> name >> score;
    Player player = {name, score};
    players.push_back(player);
  }

  return players;
}

vector<Player> LeaderBoard::RetrieveHighScores(const size_t limit) {
  auto rows = db_ << "SELECT \n"
                     "  name, \n"
                     "  score \n"
                     "FROM \n"
                     "  leaderboard \n"
                     "ORDER BY \n"
                     "  score DESC \n"
                     "LIMIT \n"
                     " ?;" << limit;

  return GetPlayers(&rows);
}

vector<Player> LeaderBoard::RetrieveHighScores(const Player& player,
                                               const size_t limit) {
  auto rows = db_ << "SELECT \n"
                     "  name, \n"
                     "  score \n"
                     "FROM \n"
                     "  leaderboard \n"
                     "WHERE \n"
                     "  name = ? \n"
                     "ORDER BY \n"
                     "  score DESC \n"
                     "LIMIT \n"
                     " ?;" << player.name << limit;
  return GetPlayers(&rows);
}

}  // namespace snake
