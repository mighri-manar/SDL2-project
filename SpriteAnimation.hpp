#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include <SDL2/SDL.h>
#include "Transform.hpp"
#include "Animation.hpp"
#include "TextureMgr.hpp"

class SpritetAnimation : public Animation {

    public:
        SpritetAnimation(bool repeat = true);

        virtual void Update(float dt);
        void SetProps(int spriteRow, int frameCount, int speed);
        void Draw(Transform* tf);

    private:
        int m_Speed;
        int m_SpriteRow;
        int m_FrameCount;
};

#endif // SPRITEANIMATION_H
