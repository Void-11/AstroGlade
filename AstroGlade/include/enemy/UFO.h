#ifndef ASTROGLADE_GAME_ENEMY_UFO_H
#define ASTROGLADE_GAME_ENEMY_UFO_H

#include <string>

#include "enemy/EnemySpaceship.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	// Drifts across the screen at a fixed velocity while spinning and firing in three directions.
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufo.png", float rotationSpeed = 40.f);

		void Tick(float deltaTime) override;

	private:
		void Shoot() override;

		LaserShooter mShooter1;
		LaserShooter mShooter2;
		LaserShooter mShooter3;
		float mRotationSpeed;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_UFO_H
