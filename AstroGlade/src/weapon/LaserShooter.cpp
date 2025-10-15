#include "weapon/LaserShooter.h"
#include "framework/Core.h"
#include "weapon/Laser.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

namespace ly
{
    LaserShooter::LaserShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& texturePath) 
        :Shooter{owner},
        mCooldownClock{},
        mCooldownTime{cooldownTime},
        mLocalPositionOffset{localPositionOffset},
        mLocalRotationOffset{localRotationOffset},
        mTexturePath{texturePath}
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
        auto* owner = GetOwner();
        // Aim using the owner's current rotation (owner decides where to face)
        float baseRot = owner->GetActorRotation();
        sf::Vector2f fwd = RotationToVector(baseRot);
        sf::Vector2f right = RotationToVector(baseRot + 90.f);

        mCooldownClock.restart();
        weak<Laser> newLaser = owner->GetWorld()->SpawnActor<Laser>(owner, mTexturePath);
        if (auto l = newLaser.lock())
        {
            // Use owner's facing directly; sprite will be rotated to that angle
            l->SetActorLocation(owner->GetActorLocation() + fwd * mLocalPositionOffset.x + right * mLocalPositionOffset.y);
            l->SetActorRotation(baseRot + mLocalRotationOffset);
            l->SetMoveRotation(baseRot + mLocalRotationOffset); // actual movement direction
        }
    }
}
