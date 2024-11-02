#include "weapon/LaserShooter.h"
#include "framework/Core.h"
#include "weapon/Laser.h"
#include "framework/World.h"

namespace ly
{
    LaserShooter::LaserShooter(Actor* owner, float cooldownTime)
        :Shooter{owner},
        mCooldownClock{},
        mCooldownTime{cooldownTime}
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
        mCooldownClock.restart();
        weak<Laser> newLaser = GetOwner()->GetWorld()->SpawnActor<Laser>(GetOwner(), "PNG/Lasers/laserRed01.png");
        newLaser.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        newLaser.lock()->SetActorRotation(GetOwner()->GetActorRotation());
    }
}
