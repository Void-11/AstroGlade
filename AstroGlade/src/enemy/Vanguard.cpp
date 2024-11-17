#include "Enemy/Vanguard.h"
#include "weapon/LaserShooter.h"

namespace ly
{
    Vangaurd::Vangaurd(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
        : EnemySpaceship{ owningWorld, texturePath },
        mShooter{ new LaserShooter{this} }
    {
        SetVelocity(velocity);
        SetActorRotation(180.f);
    }

    void Vangaurd::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vangaurd::Shoot()
    {
        mShooter->Shoot();
    }

}