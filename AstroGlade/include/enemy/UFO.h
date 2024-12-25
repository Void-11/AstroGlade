#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class LaserShooter;
    class UFO : public EnemySpaceship
    {
    public:
        
        UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath = "PNG/ufoBlue.png", float rotationSpeed = 40.f);

        virtual void Tick(float deltaTime) override;
        
    private:
        
        virtual void Shoot() override;

        unique<LaserShooter> mShooter1;
        unique<LaserShooter> mShooter2;
        unique<LaserShooter> mShooter3;
        float mRotationSpeed;
    };
}
