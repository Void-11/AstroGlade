#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class LaserShooter;
    class TwinBlade : public EnemySpaceship
    {
    public:
        TwinBlade(World* owningWorld, const std::string& texturePath = "PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.f, 120.f });
        virtual void Tick(float deltaTime) override;
        virtual void Shoot() override;
    private:
        unique<LaserShooter> mShooterLeft;
        unique<LaserShooter> mShooterRight;
    };
}