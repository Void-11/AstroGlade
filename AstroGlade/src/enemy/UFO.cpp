#include "enemy/UFO.h"
#include "gameplay/GameAudio.h"

namespace ly
{
	namespace
	{
		constexpr const char* kUFOLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserRed01.png";
	}

	UFO::UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooter1{ this, 0.5f, sf::Vector2f{ 0.f, 0.f }, -60.f, kUFOLaserTexture },
		mShooter2{ this, 0.5f, sf::Vector2f{ 0.f, 0.f }, 60.f, kUFOLaserTexture },
		mShooter3{ this, 0.5f, sf::Vector2f{ 0.f, 0.f }, 180.f, kUFOLaserTexture },
		mRotationSpeed{ rotationSpeed }
	{
		GetHealthComp().SetInitialHealth(85.f, 85.f);
		SetScoreAwardAmt(20);
		SetVelocity(velocity);
		SetActorRotation(90.f);
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
		AddActorRotationOffset(mRotationSpeed * deltaTime);
	}

	void UFO::Shoot()
	{
		if (ShootAll(mShooter1, mShooter2, mShooter3))
		{
			GameAudio::PlayEnemyShoot();
		}
	}
}
