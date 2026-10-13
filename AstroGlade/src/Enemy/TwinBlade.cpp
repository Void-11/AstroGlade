#include "Enemy/TwinBlade.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	namespace
	{
		constexpr const char* kTwinBladeLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserRed01.png";
	}

	TwinBlade::TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooterLeft{ this, 1.f, { 50.f, -20.f }, 0.f, kTwinBladeLaserTexture },
		mShooterRight{ this, 0.5f, { 50.f, 20.f }, 0.f, kTwinBladeLaserTexture }
	{
		GetHealthComp().SetInitialHealth(75.f, 75.f);
		SetScoreAwardAmt(10);
		SetVelocity(ScaleToResolution(velocity, owningWorld->GetWindowSize()));
		SetActorRotation(90.f);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void TwinBlade::Shoot()
	{
		if (ShootAll(mShooterLeft, mShooterRight))
		{
			GameAudio::PlayEnemyShoot();
		}
	}
}
