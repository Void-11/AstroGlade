#pragma once

#include "spaceship/Spaceship.h"

namespace ly
{
    class LaserShooter;
    class PlayerSpaceship : public Spaceship
    {
    public:

        PlayerSpaceship(World* owningWorld, const std::string& path = "PNG/playerShip2_red.png");

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() const { return mSpeed; }
        virtual void Shoot() override;

    private:

        void ManageInput();
        void NormalizeInput();
        void ApplyInput(float deltaTime);
        void ClampInputOnEdge();
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<LaserShooter> mShooter;
        std::vector<unique<LaserShooter>> mExtraShooters;
    public:
        void EnableThreeWayShooter();
        void EnableFrontalWiper();
    };
}
