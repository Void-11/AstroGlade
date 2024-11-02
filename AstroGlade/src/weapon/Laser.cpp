#include "weapon/Laser.h"

namespace ly
{
    Laser::Laser(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
        :Actor{world, texturePath},
        mOwner{owner},
        mSpeed{speed},
        mDamage{damage}
    {
        
    }

    void Laser::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Laser::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Laser::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
    }

    void Laser::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
    }
}
