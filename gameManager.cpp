#include "gameManager.hpp"
#include"Engine.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "StateMgr.hpp"
#include <iostream>


GameManager::GameManager() : window(nullptr), renderer(nullptr), font(nullptr),
                             music(nullptr), aboutMusic(nullptr), buttonHoverSound(nullptr),
                             isRunning(false), currentState(MAIN_MENU), volumeSlider(nullptr), currentPlayer("Unknown"),currentLevel(EASY){
    path = Message(16);
    engine.loadPlayersFromFile("players.txt");
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    init();
}
/*--------------------------------------------------------------------------------------------------------------------*/

GameManager::~GameManager() {
    clean();
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::init() {
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        isRunning = false; // Stop running if audio cannot be initialized
        return;
    }

    loadResources();
    // currentplayer should be the last player loaded from the file
    if (!engine.getPlayers().empty()) {
        currentPlayer = engine.getPlayers().back();
    }
    isRunning = true;
}
/*--------------------------------------------------------------------------------------------------------------------*/


void GameManager::loadResources() {
    // Fonts
    font = TTF_OpenFont("/home/manar/Documents/ENIT/POO/sdl project/arcad.TTF", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
    }

    // Backgrounds
    backgroundsByState[MAIN_MENU].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/the-smurfs-mission-vileaf.jpg", 800, 600);
    backgroundsByState[GAME].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/Nature.bmp", 800, 600);
    backgroundsByState[OPTIONS].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/5bd1180766373-wallpaper-preview.jpg", 800, 600);
    backgroundsByState[VOLUME_SETTINGS].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/5bd1180766373-wallpaper-preview.jpg", 800, 600);
    backgroundsByState[ABOUT].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/Magical Forest.png", 800, 600);
    backgroundsByState[HELP].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/help.png", 800, 600);
    backgroundsByState[PROFILE_SETTINGS].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/5bd1180766373-wallpaper-preview.jpg", 800, 600);
    backgroundsByState[PROFILE_INFO].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/5bd1180766373-wallpaper-preview.jpg", 800, 600);
    backgroundsByState[SELECT_LEVEL].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/AnotherOne/5bd1180766373-wallpaper-preview.jpg", 800, 600);
    backgroundsByState[PATH].emplace_back(renderer, "/home/manar/Documents/ENIT/POO/sdl project/5bd1180766373-wallpaper-preview.jpg", 800, 600);

    // Buttons
    SDL_Color color = {179, 158, 181, 255};
    buttonsByState[MAIN_MENU].emplace_back(50, 100, 250, 75, color, "Play", renderer, font);
    buttonsByState[MAIN_MENU].emplace_back(50, 170, 250, 75, color, "Options", renderer, font);
    buttonsByState[MAIN_MENU].emplace_back(50, 450, 250, 75, color, "Quit", renderer, font);
    buttonsByState[MAIN_MENU].emplace_back(50, 380, 250, 75, color, "About", renderer, font);
    buttonsByState[MAIN_MENU].emplace_back(50, 310, 250, 75, color, "Help", renderer, font);
    buttonsByState[MAIN_MENU].emplace_back(50, 240, 250, 75, color, "Path", renderer, font);
    // Shared return buttons for different states
    buttonsByState[OPTIONS].emplace_back(50, 400, 250, 75, color, "Return", renderer, font);
    buttonsByState[OPTIONS].emplace_back(50, 330, 250, 75, color, "Set volume", renderer, font);
    buttonsByState[OPTIONS].emplace_back(50, 260, 250, 75, color, "Profile settings", renderer, font);
    buttonsByState[OPTIONS].emplace_back(50, 190, 250, 75, color, "Select level", renderer, font);
    buttonsByState[GAME].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[ABOUT].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[VOLUME_SETTINGS].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[PROFILE_SETTINGS].emplace_back(50, 260, 250, 75, color, "Create profile", renderer, font);
    buttonsByState[PROFILE_SETTINGS].emplace_back(50, 330, 250, 75, color, "See profile", renderer, font);
    buttonsByState[PROFILE_SETTINGS].emplace_back(50, 400, 250, 75, color, "Return", renderer, font);
    buttonsByState[HELP].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[PROFILE_INFO].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[SELECT_LEVEL].emplace_back(50, 500, 250, 75, color, "Return", renderer, font);
    buttonsByState[SELECT_LEVEL].emplace_back(30, 50, 250, 75, color, "Easy", renderer, font);
    buttonsByState[SELECT_LEVEL].emplace_back(180, 50, 250, 75, color, "Medium", renderer, font);
    buttonsByState[SELECT_LEVEL].emplace_back(330, 50, 250, 75, color, "Hard", renderer, font);
    buttonsByState[PATH].emplace_back(50, 400, 250, 75, color, "Return", renderer, font);
    buttonsByState[PATH].emplace_back(50, 330, 250, 75, color, "Decrypt", renderer, font);
     //saving raindrops
    int numberOfRaindrops = 100;
    int screenWidth = 800;
    int spacing = screenWidth / numberOfRaindrops;
    for (int i = 0; i < numberOfRaindrops; ++i)
    {
        // Calculate initial X position to evenly distribute raindrops
        int initialX = i * spacing;
        int initialY;
        initialY = rand() % 100; // Random Y position between 0 and 100 (to appear at the top of the screen)
        int velocity = 3;            // You can adjust the velocity as needed
        Raindrop raindrop(initialX, initialY, velocity);
        raindrops.push_back(raindrop);
    }

    // Music and sound effects
    music = Mix_LoadMUS("/home/manar/Documents/ENIT/POO/sdl project/TheSmurfs.mp3");
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
    }

    aboutMusic = Mix_LoadMUS("/home/manar/Documents/ENIT/POO/sdl project/198666-ADR_GROUP_Child_Yells_Smurfs_Float.wav");
    buttonHoverSound = Mix_LoadWAV("/home/manar/Documents/ENIT/POO/sdl project/interface.mp3");
    if (Mix_PlayMusic(music, -1) == -1) {
        std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
        isRunning=false;
    }
    
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::runGame() {
    Engine::Instance()->Init();

    while(Engine::Instance()->IsRunning()){
        Input::Instance()->Listen();
        StateMgr::Instance()->Update();
        StateMgr::Instance()->Render();
        Timer::Instance()->Tick();
    }

    Engine::Instance()->Clean();
}
/*--------------------------------------------------------------------------------------------------------------------*/





void GameManager::handleButtonClick(Button &button) {
    std::string buttonText = button.getText();
    if (buttonText == "Play") {
        changeGameState(GAME);
        runGame();
        SDL_Event event;
        SDL_PollEvent(&event);
        while (event.type != SDL_QUIT){
                savePath(event.key);
        }
        path.encryptMessage(textPath);

    } else if (buttonText == "Options") {
        changeGameState(OPTIONS);

    }else if (buttonText == "Select level") {
        changeGameState(SELECT_LEVEL);
    }
    else if (buttonText == "Easy"){
        currentLevel = EASY;
    }
    else if (buttonText == "Medium"){
        currentLevel = MEDIUM;
    }
    else if (buttonText == "Hard"){
        currentLevel = HARD;
    }
    else if (buttonText == "Set volume") {
        changeGameState(VOLUME_SETTINGS);
        openVolumeSettings();
    }
    else if (buttonText == "Profile settings") {
        changeGameState(PROFILE_SETTINGS);
    } else if (buttonText == "Create profile") {
        std::string profileText = "Enter your username adventurer!";
        renderPrompt(profileText);
        std::string username = askForUsername(); // Function to get username input from user
        Player newPlayer(username);
        engine.addPlayer(newPlayer);
        engine.savePlayersInFile("players.txt");
        currentPlayer = newPlayer;
    }
    else if (buttonText == "See profile") {
        changeGameState(PROFILE_INFO);
    }
    else if (buttonText == "Path") {
        changeGameState(PATH);
    }
    else if (buttonText == "Decrypt") {
        path.decryptMessage(path.getEncryptedMessage());
        renderPath(path.getDecryptedMessage());
    }
    else if (buttonText == "Return") {
        changeGameState(MAIN_MENU);
    }

    else if (buttonText == "About") {
        changeGameState(ABOUT);

    }
    else if (buttonText == "Help") {
        changeGameState(HELP);

    }else if (buttonText.find("Return") != std::string::npos && currentState == ABOUT) {
        changeGameState(MAIN_MENU);
        Mix_HaltMusic();
        Mix_PlayMusic(music, -1);

    }else if (buttonText.find("Return") != std::string::npos) {
        changeGameState(MAIN_MENU);
    } else if (buttonText == "Quit") {
        isRunning = false;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

    std::string GameManager::askForUsername() {

        SDL_StartTextInput();
        std::string inputText; // This will store the user input
        SDL_Event e;
        bool done = false;

        while (!done) {
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_QUIT) {
                    done = true;
                }
                    // Special key input
                else if (e.type == SDL_KEYDOWN) {
                    // Handle backspace
                    if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                        inputText.pop_back();
                        renderInputText(inputText);  // Update the screen with current text
                    }
                        // Handle return
                    else if (e.key.keysym.sym == SDLK_RETURN) {
                        done = true;
                    }
                }
                    // Handle text input
                else if (e.type == SDL_TEXTINPUT) {
                    // Not copying or pasting
                    if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V'))) {
                        inputText += e.text.text;
                        renderInputText(inputText);  // Update the screen with current text
                    }
                }
            }
        }

        SDL_StopTextInput();
        return inputText;
    }
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::renderInputText(const std::string& text) {
    // Clear the part of the screen where the text is displayed
    // Set color for rendering text
    SDL_Color textColor = {255, 255, 255, 0}; // White text

    // Render the new text
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect renderQuad = {120, 130, surface->w, surface->h};  // Position where the text is rendered
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    // Cleanup
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::renderPrompt(const std::string& text) {
    // Clear the part of the screen where the text is displayed
    // Set color for rendering text
    SDL_Color textColor = {255, 255, 255, 0}; // White text

    // Render the new text
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect renderQuad = {100, 100, surface->w, surface->h};  // Position where the text is rendered
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    // Cleanup
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}
/*--------------------------------------------------------------------------------------------------------------------*/


void GameManager::displayPlayerInfo(const Player& player) {
    int yOffset = 50; // Initial vertical offset for text rendering
    std::string title =  player.getName() + ":";

    renderText(title, 50, yOffset, {255, 255, 255});
    yOffset += 30; // Increment for next line

    // Display scores for each level
    for (int level = static_cast<int>(Level::Easy); level <= static_cast<int>(Level::Hard); level++) {
        std::string scoreLine = "Level " + std::to_string(level) + ": " + std::to_string(player.getScore(static_cast<Level>(level)));
        renderText(scoreLine, 50, yOffset, {255, 255, 255});
        yOffset += 30; // Increment for next line
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect renderQuad = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::changeGameState(GameState newState) {

    if (currentState != newState) {
        currentState = newState;

    }
    if (currentState == ABOUT) {
        Mix_PlayMusic(aboutMusic, -1);
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (currentState == VOLUME_SETTINGS) {
            volumeSlider->handleEvent(event);
        }

        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                handleKeyboard(event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseButtonDown(event.button);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMotion(event.motion);
                break;
            default:
                break;
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::handleMouseButtonDown(const SDL_MouseButtonEvent &btn) {
    if (buttonsByState.find(currentState) != buttonsByState.end()) {
        for (auto &button: buttonsByState[currentState]) {
            if (button.wasClicked(btn.x, btn.y)) {
                Mix_PlayChannel(-1, buttonHoverSound, 0);
                handleButtonClick(button);
                break;
            }
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::handleMouseMotion(const SDL_MouseMotionEvent &motion) {
    for (auto &button : buttonsByState[currentState]) {
        if (button.wasClicked(motion.x, motion.y)) {
            button.hover();
        } else {
            button.unhover();
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::handleKeyboard(const SDL_KeyboardEvent &keyEvent) {
    switch (keyEvent.keysym.sym) {
        case SDLK_ESCAPE:
            isRunning = false;
            break;
        case SDLK_j:
            currentState = GAME;
            break;

        case SDLK_F1:
            Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN;
            bool isFullscreen = SDL_GetWindowFlags(window) & fullscreenFlag;
            SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
            //destroy the renderer and create a new one
            if (renderer) {
                SDL_DestroyRenderer(renderer);

            }
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
                isRunning = false;
            }
            loadResources();
            break;

    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::render() {
    SDL_RenderClear(renderer);
    for (auto& bg : backgroundsByState[currentState]) {
        bg.render(renderer);
        if (currentState == MAIN_MENU) {
            updateRaindrops(raindrops, 600);
            renderRaindrops(renderer, raindrops);
        }
    }
    for (auto& btn : buttonsByState[currentState]) {
        btn.render();
    }

    if (currentState == VOLUME_SETTINGS) {
        volumeSlider->render();
    }
    if (currentState == PROFILE_INFO) {
        displayPlayerInfo(currentPlayer);
    }

    SDL_RenderPresent(renderer);
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::clean() {
    if (volumeSlider) {
        delete volumeSlider;
        volumeSlider = nullptr;
    }
    unloadResources();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::unloadResources() {
    if (font) TTF_CloseFont(font);
    if (music) Mix_FreeMusic(music);
    if (aboutMusic) Mix_FreeMusic(aboutMusic);
    if (buttonHoverSound) Mix_FreeChunk(buttonHoverSound);
}


/*--------------------------------------------------------------------------------------------------------------------*/


void GameManager::openVolumeSettings() {
    int maxVolumeLevel = MIX_MAX_VOLUME; // SDL_mixer max volume
    int currentVolumeLevel = Mix_VolumeMusic(-1); // Get current volume
    volumeSlider = new Slider(100, 200, 200, 20, 0, maxVolumeLevel, currentVolumeLevel, renderer);
    currentState = VOLUME_SETTINGS;
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::updateRaindrops(std::vector<Raindrop> &raindrops, int screenHeight)
{
    // Add a counter to keep track of the number of raindrops
    static int raindropCounter = 0;

    // Update existing raindrops and remove those that have fallen off the screen
    for (auto it = raindrops.begin(); it != raindrops.end();)
    {
        it->update();
        if (it->isOffScreen(screenHeight))
        {
            it = raindrops.erase(it); // Remove raindrop from the vector if it's off the screen
        }
        else
        {
            ++it;
        }
    }

    // Spawn new raindrops at the top of the screen
    if (raindropCounter % 2 == 0) // Spawn new raindrops more frequently
    {
        int numberOfNewRaindrops = 2; // Spawn more raindrops at once
        for (int i = 0; i < numberOfNewRaindrops; ++i)
        {
            // Generate random initial position and velocity for each new raindrop
            int initialX = rand() % 800; // Random X position between 0 and 800 (screen width)
            int initialY = 0;            // Start raindrops at the top of the screen
            int velocity = 2;            // Increase the velocity to make the raindrops fall faster
            Raindrop raindrop(initialX, initialY, velocity);
            raindrops.push_back(raindrop);
        }
    }

    // Increment the raindrop counter
    ++raindropCounter;
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::renderRaindrops(SDL_Renderer *renderer, const std::vector<Raindrop> &raindrops) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // grey color for raindrops
    for (const auto &raindrop : raindrops) {
        SDL_RenderDrawLine(renderer, raindrop.getX(), raindrop.getY(), raindrop.getX(), raindrop.getY() + 5);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Reset to white or another default color
}


/*--------------------------------------------------------------------------------------------------------------------*/


void GameManager::run() {
    while (isRunning) {
        handleEvents();
        render();
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/


void GameManager::renderPath(const std::string &text) {
    // Clear the part of the screen where the text is displayed
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set color for rendering text
    SDL_Color textColor = {255, 255, 255, 0}; // White text

    // Render the new text
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect renderQuad = {50, 50, surface->w, surface->h};  // Position where the text is rendered
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    // Cleanup
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);

}
/*--------------------------------------------------------------------------------------------------------------------*/

std::string GameManager::getKeyPhrase(SDL_Keycode keycode) {
    switch (keycode) {
        case SDLK_d:
            return " Go straight adventurer! ";
        case SDLK_q:
            return " Go backward smurfy! ";
        case SDLK_s:
            return " Now crouch!! ";
        case SDLK_j:
            return " JUMP! ";
        default:
            return ""; // Return empty string for unhandled keys
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

void GameManager::savePath(const SDL_KeyboardEvent& keyEvent) {
    // Check if the key event is a key press
    if (keyEvent.type == SDL_KEYDOWN) {
        // Get the key phrase corresponding to the pressed key
        std::string keyPhrase = getKeyPhrase(keyEvent.keysym.sym);

        // Append the key phrase to the path
        textPath += keyPhrase;
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
