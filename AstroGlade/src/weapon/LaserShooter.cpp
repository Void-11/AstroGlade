#include "weapon/LaserShooter.h"
#include "framework/Core.h"

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
        LOG("Shooting!")
    }
}
