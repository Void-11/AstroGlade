#include <initializer_list>

#include "weapon/FrontalWiper.h"

namespace ly
{
	namespace
	{
		constexpr const char* kOuterLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserGreen11.png";
		constexpr const char* kInnerLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserBlue07.png";
	}

	FrontalWiper::FrontalWiper(Actor* ownerActor, float cooldownTime, const sf::Vector2f& localOffset, float width)
		: Shooter{ ownerActor },
		mShooter1{ ownerActor, cooldownTime, { localOffset.x, localOffset.y - width / 2.f }, 0.f, kOuterLaserTexture },
		mShooter2{ ownerActor, cooldownTime, { localOffset.x, localOffset.y - width / 6.f }, 0.f, kInnerLaserTexture },
		mShooter3{ ownerActor, cooldownTime, { localOffset.x, localOffset.y + width / 6.f }, 0.f, kInnerLaserTexture },
		mShooter4{ ownerActor, cooldownTime, { localOffset.x, localOffset.y + width / 2.f }, 0.f, kOuterLaserTexture },
		mShooter5{ ownerActor, cooldownTime / 1.5f, { localOffset.x, localOffset.y + width / 1.5f }, 15.f, kOuterLaserTexture },
		mShooter6{ ownerActor, cooldownTime / 1.5f, { localOffset.x, localOffset.y - width / 1.5f }, -15.f, kOuterLaserTexture }
	{
	}

	void FrontalWiper::SetCurrentLevel(int newLevel)
	{
		Shooter::SetCurrentLevel(newLevel);
		for (LaserShooter* shooter : { &mShooter1, &mShooter2, &mShooter3, &mShooter4, &mShooter5, &mShooter6 })
		{
			shooter->SetCurrentLevel(newLevel);
		}
	}

	bool FrontalWiper::ShootImpl()
	{
		bool fired = ShootAll(mShooter1, mShooter2, mShooter3, mShooter4);

		if (IsAtMaxLevel())
		{
			fired = ShootAll(mShooter5, mShooter6) || fired;
		}

		return fired;
	}
}
