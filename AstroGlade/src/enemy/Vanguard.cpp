#include "Enemy/Vanguard.h"
#include "weapon/LaserShooter.h"

namespace ly
{
    Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
        : EnemySpaceship{ owningWorld, texturePath },
        mShooter{ new LaserShooter{this, 1.f, {50.f, 0.f}, 0.f, "PNG/Lasers/laserRed07.png"} }
    {
        SetVelocity(velocity);
        // Face downwards
        SetActorRotation(90.f);
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        mShooter->Shoot();
    }

}