#include <initializer_list>

#include "weapon/ThreeWayShooter.h"

namespace ly
{
	namespace
	{
		constexpr const char* kThreeWayLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserRed01.png";
	}

	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{ owner },
		mShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, -10.f }, -30.f, kThreeWayLaserTexture },
		mShooterMid{ owner, cooldownTime, localOffset, 0.f, kThreeWayLaserTexture },
		mShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, 10.f }, 30.f, kThreeWayLaserTexture },
		mTopLevelShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, 10.f }, 15.f, kThreeWayLaserTexture },
		mTopLevelShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, -10.f }, -15.f, kThreeWayLaserTexture }
	{
	}

	void ThreeWayShooter::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		for (LaserShooter* shooter : { &mShooterLeft, &mShooterMid, &mShooterRight, &mTopLevelShooterLeft, &mTopLevelShooterRight })
		{
			shooter->SetCurrentLevel(level);
		}
	}

	bool ThreeWayShooter::ShootImpl()
	{
		bool fired = ShootAll(mShooterLeft, mShooterMid, mShooterRight);

		if (IsAtMaxLevel())
		{
			fired = ShootAll(mTopLevelShooterLeft, mTopLevelShooterRight) || fired;
		}

		return fired;
	}
}
