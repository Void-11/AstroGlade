#pragma once

#include "spaceship/Spaceship.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:

        PlayerSpaceship(World* owningWorld, const std::string& path = "PNG/playerShip2_red.png");

        virtual void Tick(float deltaTime) override;
        void SetSpeed(float newSpeed) { mSpeed = newSpeed; }
        float GetSpeed() const { return mSpeed; }

    private:

        void ManageInput();
        void NormalizeInput();
        void ApplyInput(float deltaTime);
        void ClampInputOnEdge();
        sf::Vector2f mMoveInput;
        float mSpeed;
    };
}
