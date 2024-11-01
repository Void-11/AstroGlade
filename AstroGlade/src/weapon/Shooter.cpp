#include "weapon/Shooter.h"

namespace ly
{
    void Shooter::Shoot()
    {
        if(CanShot() && !IsOnCoolDown())
        {
            ShootExecution();
        }
    }

    Shooter::Shooter(Actor* owner)
        :mOwner{}
    {
        
    }
}
