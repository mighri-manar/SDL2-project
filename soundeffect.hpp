#ifndef MAIN_CPP_SOUNDEFFECT_HPP
#define MAIN_CPP_SOUNDEFFECT_HPP


#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
public:
    SoundEffect();
    ~SoundEffect();

    void load(const std::string& fileName);
    void play();
    void stop();
    void setVolume(int volume);
    void unload();

private:
    std::string fileName;
    Mix_Chunk* soundData;
    int volume;
    bool loopStatus;
    bool isPlaying;
};

#endif //MAIN_CPP_SOUNDEFFECT_HPP