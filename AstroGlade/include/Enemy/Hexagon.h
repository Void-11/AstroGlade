#ifndef ASTROGLADE_GAME_ENEMY_HEXAGON_H
#define ASTROGLADE_GAME_ENEMY_HEXAGON_H

#include <string>

#include "Enemy/EnemySpaceship.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	class Hexagon : public EnemySpaceship
	{
	public:
		explicit Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed6.png", const sf::Vector2f& velocity = sf::Vector2f{ 0.f, 100.f });

		void Tick(float deltaTime) override;

	private:
		void Shoot() override;

		LaserShooter mShooter1;
		LaserShooter mShooter2;
		LaserShooter mShooter3;
		LaserShooter mShooter4;
		LaserShooter mShooter5;
		LaserShooter mShooter6;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_HEXAGON_H
