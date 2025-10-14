#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    class Player : public Object
    {
    public:
        Player();

        void Reset();
        void AddScore(int amt);
        int GetScore() const { return mScore; }

        void SetLifeCount(int life) { mLifeCount = life; }
        int GetLifeCount() const { return mLifeCount; }

        weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentSpaceship; }
        void SetCurrentSpaceship(weak<PlayerSpaceship> sp) { mCurrentSpaceship = sp; }

        Delegate<int> onLifeChange;
        Delegate<int> onScoreChange;

    private:
        int mLifeCount;
        int mScore;
        weak<PlayerSpaceship> mCurrentSpaceship;
    };
}
