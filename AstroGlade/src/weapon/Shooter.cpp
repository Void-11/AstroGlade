#include "weapon/Shooter.h"

namespace ly
{
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
		if (amt <= 0 || mCurrentLevel == mMaxLevel) return;

		mCurrentLevel += amt;
		if (mCurrentLevel > mMaxLevel)
		{
			mCurrentLevel = mMaxLevel;
		}
	}

	void Shooter::SetCurrentLevel(int level)
	{
		if (level < 1)
		{
			level = 1;
		}

		if (level > mMaxLevel)
		{
			level = mMaxLevel;
		}

		mCurrentLevel = level;
	}

	Shooter::Shooter(Actor* owner)
		: mOwner{owner},
		mCurrentLevel{1},
		mMaxLevel{4}
	{

	}
}
