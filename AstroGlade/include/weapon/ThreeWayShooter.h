#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/LaserShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f});

		LaserShooter mShooterLeft;
		LaserShooter mShooterMid;
		LaserShooter mShooterRight;

		LaserShooter mTopLevelShooterLeft;
		LaserShooter mTopLevelShooterRight;

		virtual void IncrementLevel(int amt) override;
		virtual void SetCurrentLevel(int level) override;
	private:
		virtual void ShootImpl();
	};
}