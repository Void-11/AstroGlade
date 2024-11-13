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
        mHealthComp.onHealthModified.BindAction(GetWeakRef(), &Spaceship::OnHealthModified);
        mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amount)
    {
        mHealthComp.ModifyHealth(-amount);
    }

    void Spaceship::OnHealthModified(float amt, float health, float maxHealth)
    {
        
    }

    void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
    {
        
    }

    void Spaceship::Blow()
    {
        Destroy();
    }
}
