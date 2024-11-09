#include "spaceship/Spaceship.h"
#include "framework/Actor.h"

namespace  ly
{
    Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
        :Actor{owningWorld, texturePath},
        mVelocity{},
        mHealthComp{100.f, 100.f}
    {
        
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
    {
        mVelocity = newVelocity;
    }

    void Spaceship::Shoot()
    {
        
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }
}
