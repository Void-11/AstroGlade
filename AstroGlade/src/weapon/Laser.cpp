#include "weapon/Laser.h"

namespace ly
{
    Laser::Laser(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
        :Actor{world, texturePath},
        mOwner{owner},
        mSpeed{speed},
        mDamage{damage}
    {
        SetTeamID(owner->GetTeamID());
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
        if(IsActorOutOfWindowBounds())
        {
            Destroy();   
        }
    }

    void Laser::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Laser::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorRightDirection() * mSpeed * deltaTime);
    }

    void Laser::OnActorBeginOverlap(Actor* other)
    {
        if (IsOtherHostile(other))
        {
            other->ApplyDamage(GetDamage());
            Destroy();
        }
    }
}
