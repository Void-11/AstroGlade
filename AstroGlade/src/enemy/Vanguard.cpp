#include "enemy/Vanguard.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooter{ this, 1.f, { 50.f, 0.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
		GetHealthComp().SetInitialHealth(50.f, 50.f);
		SetScoreAwardAmt(5);
		SetVelocity(ScaleToResolution(velocity, owningWorld->GetWindowSize()));
		SetActorRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		if (mShooter.Shoot())
		{
			GameAudio::PlayEnemyShoot();
		}
	}
}
