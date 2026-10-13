#ifndef ASTROGLADE_GAME_WEAPON_LASER_H
#define ASTROGLADE_GAME_WEAPON_LASER_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	// A projectile that flies forward, damages the first hostile actor it touches and is then destroyed.
	// It joins the team of the actor that fired it.
	class Laser : public Actor
	{
	public:
		Laser(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);

		void SetSpeed(float newSpeed);
		void SetDamage(float newDamage);
		[[nodiscard]] float GetDamage() const { return mDamage; }
		void Tick(float deltaTime) override;
		void BeginPlay() override;

	private:
		void OnActorBeginOverlap(Actor* other) override;
		void Move(float deltaTime);

		float mSpeed;
		float mDamage;
	};
}

#endif // ASTROGLADE_GAME_WEAPON_LASER_H
