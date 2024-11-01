#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly
{
    class LaserShooter : public Shooter
    {
    public:

        LaserShooter(Actor* owner, float cooldownTime = 1.f);
        virtual bool IsOnCoolDown() const override;

    private:

        sf::Clock mCooldownClock;
        float mCooldownTime;
        
        virtual void ShootExecution() override;
    };
}
