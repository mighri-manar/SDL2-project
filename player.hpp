#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#ifndef MAIN_CPP_PLAYER_HPP
#define MAIN_CPP_PLAYER_HPP

// Define an enumeration for levels
enum class Level {
    Easy,
    Medium,
    Hard
};

class Player {
private:
    std::string username;
    std::map<Level, int> scores;  // Map to store scores for different levels

public:
    Player();  // Constructor
    explicit Player(std::string  name);  // Constructor with name initialization
    ~Player();  // Destructor

    void setName(const std::string& name);
    void setScore(Level level, int score);  // Set score for a specific level
    void increaseScore(Level level, int bonus);  // Increase score by a bonus amount

    std::string getName() const;
    int getScore(Level level) const;  // Get score for a specific level

};

#endif // MAIN_CPP_PLAYER_HPP