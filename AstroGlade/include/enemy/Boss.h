#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World* world, const std::string& texturePath = "PNG/Enemies/boss.png");
        virtual void Tick(float deltaTime) override;
    private:
        float mTime;
        virtual void Shoot() override;
    };
}