#ifndef SEQANIMATION_HPP
#define SEQANIMATION_HPP

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include "TextureMgr.hpp"
#include "Transform.hpp"

struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<const char*> TextureIDs;
};

class SeqAnimation: public Animation{

    public:
        SeqAnimation(bool repeat = true);

        virtual void Update(float dt);
        void Parse(std::string source);
        void SetCurrentSeq(std::string seqID);
        void SetRepeat(bool repeat){m_Repeat = repeat;}
        //void DrawFrame(int x, int y, SDL_RendererFlip flip=SDL_FLIP_NONE, float scaleX=0.0f, float scaleY=0.0f, float rotation=0.0f, float speedRatio=1.0f);
        void DrawFrame(Transform* tf);

    private:
        Sequence m_CurrentSeq;
        std::map<std::string, Sequence> m_SeqMap;
};

#endif // SEQANIMATION_H
