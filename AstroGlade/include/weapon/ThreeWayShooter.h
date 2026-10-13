#ifndef ASTROGLADE_GAME_WEAPON_THREEWAYSHOOTER_H
#define ASTROGLADE_GAME_WEAPON_THREEWAYSHOOTER_H

#include <SFML/Graphics.hpp>

#include "weapon/LaserShooter.h"

namespace ly
{
	// Fires a fan of three lasers, widening to five at the maximum level.
	class ThreeWayShooter : public Shooter
	{
	public:
		explicit ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = { 0.f, 0.f });

		void SetCurrentLevel(int level) override;

	private:
		bool ShootImpl() override;

		LaserShooter mShooterLeft;
		LaserShooter mShooterMid;
		LaserShooter mShooterRight;

		LaserShooter mTopLevelShooterLeft;
		LaserShooter mTopLevelShooterRight;
	};
}

#endif // ASTROGLADE_GAME_WEAPON_THREEWAYSHOOTER_H
