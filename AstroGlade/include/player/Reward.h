#pragma once
#include "framework/Actor.h"

namespace ly
{
    enum class RewardType { Health, ThreeWay, FrontalWiper, Life };

    class Reward : public Actor
    {
    public:
        Reward(World* w, const sf::Vector2f& spawnLoc, RewardType type = RewardType::Health);
        virtual void Tick(float deltaTime) override;
    private:
        RewardType mType;
    };
}