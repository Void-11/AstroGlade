#include "Enemy/Vanguard.h"
#include "weapon/LaserShooter.h"
#include "framework/World.h"
namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooter{ new LaserShooter{this, 1.f, {50.f, 0.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		sf::Vector2u windowSize = owningWorld->GetWindowSize();
		float scaleX = windowSize.x / 600.f;
		float scaleY = windowSize.y / 980.f;
		SetVelocity({velocity.x * scaleX, velocity.y * scaleY});
		SetActorRotation(90.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		mShooter->Shoot();
	}

}