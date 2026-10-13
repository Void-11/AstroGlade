#include <algorithm>

#include "weapon/Shooter.h"

namespace ly
{
	Shooter::Shooter(Actor* owner)
		: mOwner{ owner }
	{
	}

	bool Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			return ShootImpl();
		}

		return false;
	}

	void Shooter::IncrementLevel(int amt)
	{
		if (amt <= 0 || IsAtMaxLevel()) return;

		SetCurrentLevel(mCurrentLevel + amt);
	}

	void Shooter::SetCurrentLevel(int level)
	{
		mCurrentLevel = std::clamp(level, 1, kMaxLevel);
	}
}
