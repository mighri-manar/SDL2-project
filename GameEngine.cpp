
#include <sstream>
#include "GameEngine.hpp"

GameEngine::GameEngine() = default;

GameEngine::~GameEngine() = default;

void GameEngine::addPlayer(const Player& player) {
    players.push_back(player);
}

void GameEngine::savePlayersInFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Player& player : players) {
            file << player.getName() << ",";
            for (int level = static_cast<int>(Level::Easy); level <= static_cast<int>(Level::Hard); ++level) {
                file << player.getScore(static_cast<Level>(level)) << (level < static_cast<int>(Level::Hard) ? "," : "");
            }
            file << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}

void GameEngine::loadPlayersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        getline(iss, name, ',');
        Player player(name);
        int score;
        int level = static_cast<int>(Level::Easy);
        while (iss >> score) {
            player.setScore(static_cast<Level>(level++), score);
            if (iss.peek() == ',') iss.ignore();
        }
        players.push_back(player);
    }
    file.close();
}

void GameEngine::runGameByLevel(GameLevel level) {
//will be done later
}

void GameEngine::updateScores(int healthPoints, const std::string &playerName) {

//will be done later
}