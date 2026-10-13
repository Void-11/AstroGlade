#ifndef ASTROGLADE_GAME_WEAPON_FRONTALWIPER_H
#define ASTROGLADE_GAME_WEAPON_FRONTALWIPER_H

#include <SFML/Graphics.hpp>

#include "weapon/LaserShooter.h"

namespace ly
{
	// Fires a wall of four parallel lasers across width, plus two angled ones at the maximum level.
	class FrontalWiper : public Shooter
	{
	public:
		explicit FrontalWiper(Actor* ownerActor,
			float cooldownTime = 0.3f,
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 60.f
		);

		void SetCurrentLevel(int newLevel) override;

	private:
		bool ShootImpl() override;

		LaserShooter mShooter1;
		LaserShooter mShooter2;
		LaserShooter mShooter3;
		LaserShooter mShooter4;
		LaserShooter mShooter5;
		LaserShooter mShooter6;
	};
}

#endif // ASTROGLADE_GAME_WEAPON_FRONTALWIPER_H
