#ifndef ASTROGLADE_GAME_ENEMY_TWINBLADE_H
#define ASTROGLADE_GAME_ENEMY_TWINBLADE_H

#include <string>

#include "Enemy/EnemySpaceship.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	class TwinBlade : public EnemySpaceship
	{
	public:
		explicit TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack.png", const sf::Vector2f& velocity = sf::Vector2f{ 0.f, 120.f });

		void Tick(float deltaTime) override;

	private:
		void Shoot() override;

		LaserShooter mShooterLeft;
		LaserShooter mShooterRight;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_TWINBLADE_H
