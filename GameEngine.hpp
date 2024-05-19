#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "player.hpp"  // Your Player class

enum class GameLevel {
    EASY,
    MEDIUM,
    HARD
};

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    void addPlayer(const Player& player);
    void savePlayersInFile(const std::string& filename);
    void loadPlayersFromFile(const std::string& filename);
    void runGameByLevel(GameLevel level);
    void updateScores(int healthPoints, const std::string& playerName);
    const std::vector<Player>& getPlayers() const {
        return players;
    }

private:
    std::vector<Player> players;
    //std::map<GameLevel, std::vector<Game>> gamesByLevel;

};

#endif // GAME_ENGINE_HPP