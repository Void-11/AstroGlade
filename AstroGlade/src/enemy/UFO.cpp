#include "Enemy/UFO.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	UFO::UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath, float rotationSpeed)
		: EnemySpaceship{ owningWorld, texturePath},
		mShooter1{ new LaserShooter{this, .5f, sf::Vector2f{0.f,0.f}, -60, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter2{ new LaserShooter{this, .5f, sf::Vector2f{0.f,0.f}, 60, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter3{ new LaserShooter{this, .5f, sf::Vector2f{0.f,0.f}, 180.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mRotationSpeed{rotationSpeed}
	{
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
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
	}
}