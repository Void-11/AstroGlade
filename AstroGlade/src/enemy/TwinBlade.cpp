#include "Enemy/TwinBlade.h"
#include "weapon/LaserShooter.h"
#include "framework/World.h"

namespace ly
{
	TwinBlade::TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{owningWorld, texturePath},
		mShooterLeft{ new LaserShooter{this, 1.f, {50.f, -20.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooterRight{ new LaserShooter{this, .5f, {50.f, 20.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		sf::Vector2u windowSize = owningWorld->GetWindowSize();
		float scaleX = windowSize.x / 600.f;
		float scaleY = windowSize.y / 980.f;
		SetVelocity({velocity.x * scaleX, velocity.y * scaleY});
		SetActorRotation(90.f);
	}
	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
	void TwinBlade::Shoot()
	{
		mShooterLeft->Shoot();
		mShooterRight->Shoot();
	}
}