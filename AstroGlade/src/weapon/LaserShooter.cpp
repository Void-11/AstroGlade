#include "framework/Core.h"
#include "weapon/LaserShooter.h"
#include "weapon/Laser.h"
#include "framework/World.h"

namespace ly
{

	LaserShooter::LaserShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& laserTexturePath)
		: Shooter{ owner },
		mCooldownClock{},
		mCooldownTime{ cooldownTime },
		mLocalPositionOffset{ localPositionOffset },
		mLocalRotationOffset{ localRotationOffset },
		mLaserTexturePath{laserTexturePath}
	{
	}

	bool LaserShooter::IsOnCooldown() const
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime / GetCurrentLevel())
		{
			return false;
		}

		return true;
	}

	void LaserShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
	}

	void LaserShooter::SetLaserTexturePath(const std::string& laserTexturePath)
	{
		mLaserTexturePath = laserTexturePath;
	}

	void LaserShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();
		weak<Laser> newLaser = GetOwner()->GetWorld()->SpawnActor<Laser>(GetOwner(), mLaserTexturePath);
		newLaser.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
		newLaser.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
	}
}
