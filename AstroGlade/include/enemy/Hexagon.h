#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class LaserShooter;
    class Hexagon : public EnemySpaceship
    {
    public:
        Hexagon(World* owingWorld, const std::string& texturePath = "PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = sf::Vector2f{0.f, 100.f});

        virtual void Tick(float deltaTime) override;
    private:
        virtual void Shoot() override;

        unique<LaserShooter> mShooter1;
        unique<LaserShooter> mShooter2;
        unique<LaserShooter> mShooter3;
        unique<LaserShooter> mShooter4;
        unique<LaserShooter> mShooter5;
        unique<LaserShooter> mShooter6;
    };
}