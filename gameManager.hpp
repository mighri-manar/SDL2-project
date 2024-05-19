#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "background.hpp"
#include "buttonmenu.hpp"
#include "soundeffect.hpp"
#include"slider.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>
#include <string>
#include"raindrop.hpp"
#include"GameEngine.hpp"
#include"smurf.hpp"
#include "Message.h"


class GameManager {
public:
    GameManager();
    ~GameManager();
    void run();
    void runGame();
    void init();
    void handleEvents();
    void render();
    void clean();

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Mix_Music* music;
    Mix_Music* aboutMusic;
    Mix_Chunk* buttonHoverSound;
    Slider* volumeSlider;
    std::vector<Raindrop> raindrops;
    Player currentPlayer;
    GameEngine engine;
    Message path;
    std::string textPath;




    std::map<int, std::vector<Background>> backgroundsByState;
    std::map<int, std::vector<Button>> buttonsByState;

    enum GameState { MAIN_MENU, OPTIONS, GAME, ABOUT, VOLUME_SETTINGS, PROFILE_SETTINGS, PROFILE_INFO,SELECT_LEVEL,PATH, HELP};    GameState currentState;
    enum GameLevel { EASY, MEDIUM, HARD};
    GameLevel currentLevel;
    void handleButtonClick(Button &button);
    void changeGameState(GameState newState);
    void handleMouseButtonDown(const SDL_MouseButtonEvent &btn);
    void handleMouseMotion(const SDL_MouseMotionEvent &motion);
    void handleKeyboard(const SDL_KeyboardEvent &keyEvent);
    void loadResources();
    void unloadResources();
    void openVolumeSettings();
    static void updateRaindrops(std::vector<Raindrop> &raindrops, int screenHeight);
    static void renderRaindrops(SDL_Renderer *renderer, const std::vector<Raindrop> &raindrops);
    std::string askForUsername();
    void displayPlayerInfo(const Player& player);
    void renderInputText(const std::string& text);
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    void renderPrompt(const std::string& text);
    void savePath(const SDL_KeyboardEvent &keyEvent);
    static std::string getKeyPhrase(SDL_Keycode keycode);
    void renderPath(const std::string& text);



};

#endif // GAMEMANAGER_HPP