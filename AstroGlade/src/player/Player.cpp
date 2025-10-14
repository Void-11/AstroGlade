#include "player/Player.h"

namespace ly
{
    Player::Player()
        : mLifeCount{3},
          mScore{0},
          mCurrentSpaceship{}
    {
    }

    void Player::Reset()
    {
        mLifeCount = 3;
        mScore = 0;
        mCurrentSpaceship.reset();
        onLifeChange.Broadcast(mLifeCount);
        onScoreChange.Broadcast(mScore);
    }

    void Player::AddScore(int amt)
    {
        mScore += amt;
        if (mScore < 0) mScore = 0;
        onScoreChange.Broadcast(mScore);
    }
}
