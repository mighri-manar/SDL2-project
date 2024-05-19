#include "player.hpp"
#include <iostream>
#include <utility>

Player::Player() : username("Unknown") {}

Player::Player(std::string  name) : username(std::move(name)) {
    for (int i = 1; i <= 3; i++) {
        scores[static_cast<Level>(i)] = 0;
    }
}

Player::~Player() = default;

void Player::setName(const std::string& name) {
    username = name;
}

void Player::setScore(Level level, int score) {
    scores[level] = score;
}

void Player::increaseScore(Level level, int bonus) {
    scores[level] += bonus;
}

std::string Player::getName() const {
    return username;
}

int Player::getScore(Level level) const {
    auto it = scores.find(level);
    return it != scores.end() ? it->second : 0;
}