#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/LaserShooter.h"

namespace ly
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* ownerActor, 
			float cooldownTime = 0.3f,
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 60.f
		);
		
		virtual void IncrementLevel(int amt = 1) override;
		virtual void SetCurrentLevel(int newLevel) override;
	private:
		virtual void ShootImpl() override;

		float mWidth;

		LaserShooter mShooter1;
		LaserShooter mShooter2;
		LaserShooter mShooter3;
		LaserShooter mShooter4;
		LaserShooter mShooter5;
		LaserShooter mShooter6;
	};
}