#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Spaceship : public Actor
    {
    public:

        Spaceship(World* owningWorld, const std::string& texturePath = "");
        virtual void Tick(float deltaTime) override;
        void SetVelocity(const sf::Vector2f& newVelocity);
        sf::Vector2f GetVelocity() const {return mVelocity;}
        virtual void Shoot();

    private:

        sf::Vector2f mVelocity;
    };
}