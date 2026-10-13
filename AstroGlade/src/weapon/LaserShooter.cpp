#include "framework/World.h"
#include "weapon/Laser.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	LaserShooter::LaserShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& laserTexturePath)
		: Shooter{ owner },
		mCooldownTime{ cooldownTime },
		mLocalPositionOffset{ localPositionOffset },
		mLocalRotationOffset{ localRotationOffset },
		mLaserTexturePath{ laserTexturePath }
	{
	}

	bool LaserShooter::IsOnCooldown() const
	{
		return mCooldownClock.getElapsedTime().asSeconds() <= mCooldownTime / static_cast<float>(GetCurrentLevel());
	}

	void LaserShooter::SetLaserTexturePath(const std::string& laserTexturePath)
	{
		mLaserTexturePath = laserTexturePath;
	}

	bool LaserShooter::ShootImpl()
	{
		Actor* const owner = GetOwner();
		const sf::Vector2f ownerForwardDir = owner->GetActorForwardDirection();
		const sf::Vector2f ownerRightDir = owner->GetActorRightDirection();

		mCooldownClock.restart();
		if (const shared<Laser> newLaser = owner->GetWorld()->SpawnActor<Laser>(owner, mLaserTexturePath).lock())
		{
			newLaser->SetActorLocation(owner->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
			newLaser->SetActorRotation(owner->GetActorRotation() + mLocalRotationOffset);
		}
		return true;
	}
}
