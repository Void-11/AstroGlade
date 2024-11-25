#include "weapon/LaserShooter.h"
#include "framework/Core.h"
#include "weapon/Laser.h"
#include "framework/World.h"

namespace ly
{
    LaserShooter::LaserShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset) 
        :Shooter{owner},
        mCooldownClock{},
        mCooldownTime{cooldownTime},
        mLocalPositionOffset{localPositionOffset},
        mLocalRotationOffset{localRotationOffset}
    {
        
    }

    bool LaserShooter::IsOnCoolDown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
        {
            return false;
        }

        return true;
    }

    void LaserShooter::ShootExecution()
    {
        sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
        sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();
        mCooldownClock.restart();
        weak<Laser> newLaser = GetOwner()->GetWorld()->SpawnActor<Laser>(GetOwner(), "PNG/Lasers/laserRed07.png");
        newLaser.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
        newLaser.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
    }
}
