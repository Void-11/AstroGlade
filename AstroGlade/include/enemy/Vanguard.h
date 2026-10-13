#ifndef ASTROGLADE_GAME_ENEMY_VANGUARD_H
#define ASTROGLADE_GAME_ENEMY_VANGUARD_H

#include <string>

#include "enemy/EnemySpaceship.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	class Vanguard : public EnemySpaceship
	{
	public:
		explicit Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue.png", const sf::Vector2f& velocity = sf::Vector2f{ 0.f, 150.f });

		void Tick(float deltaTime) override;

	private:
		void Shoot() override;

		LaserShooter mShooter;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_VANGUARD_H
