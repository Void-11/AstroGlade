#include "enemy/Hexagon.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	namespace
	{
		constexpr const char* kHexagonLaserTexture = "SpaceShooterRedux/PNG/Lasers/laserRed01.png";
	}

	Hexagon::Hexagon(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooter1{ this, 1.f, sf::Vector2f{ 20.f, 50.f }, 30.f, kHexagonLaserTexture },
		mShooter2{ this, 1.f, sf::Vector2f{ 20.f, -50.f }, -30.f, kHexagonLaserTexture },
		mShooter3{ this, 1.f, sf::Vector2f{ 50.f, 0.f }, 0.f, kHexagonLaserTexture },
		mShooter4{ this, 1.f, sf::Vector2f{ -50.f, 0.f }, -180.f, kHexagonLaserTexture },
		mShooter5{ this, 1.f, sf::Vector2f{ -20.f, 50.f }, 120.f, kHexagonLaserTexture },
		mShooter6{ this, 2.5f, sf::Vector2f{ -50.f, -20.f }, 130.f, kHexagonLaserTexture }
	{
		GetHealthComp().SetInitialHealth(85.f, 85.f);
		SetScoreAwardAmt(15);
		SetVelocity(ScaleToResolution(velocity, owningWorld->GetWindowSize()));
		SetActorRotation(90.f);
	}

	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Hexagon::Shoot()
	{
		if (ShootAll(mShooter1, mShooter2, mShooter3, mShooter4, mShooter5, mShooter6))
		{
			GameAudio::PlayEnemyShoot();
		}
	}
}
