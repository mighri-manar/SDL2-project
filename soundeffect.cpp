#include "soundeffect.hpp"

SoundEffect::SoundEffect() : soundData(nullptr), volume(MIX_MAX_VOLUME), loopStatus(false), isPlaying(false) {}

SoundEffect::~SoundEffect() {
    unload();
}

void SoundEffect::load(const std::string& fileName) {
    soundData = Mix_LoadWAV(fileName.c_str());
    if (!soundData) {
        // Handle error
    }
    this->fileName = fileName;
}

void SoundEffect::play() {
    if (soundData) {
        Mix_PlayChannel(-1, soundData, loopStatus ? -1 : 0);
        isPlaying = true;
    }
}

void SoundEffect::stop() {
    if (isPlaying) {
        Mix_HaltChannel(-1);
        isPlaying = false;
    }
}

void SoundEffect::setVolume(int volume) {
    this->volume = volume;
    Mix_Volume(-1, volume);
}

void SoundEffect::unload() {
    if (soundData) {
        Mix_FreeChunk(soundData);
        soundData = nullptr;
    }
}