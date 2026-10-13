#ifndef ASTROGLADE_ENGINE_VFX_PARTICLE_H
#define ASTROGLADE_ENGINE_VFX_PARTICLE_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	// A short lived sprite that drifts, shrinks and fades out over its lifetime.
	class Particle : public Actor
	{
	public:
		Particle(World* owningWorld, const std::string& texturePath);
		void Tick(float deltaTime) override;

		void RandomVelocity(float minSpeed, float maxSpeed);
		void RandomSize(float min, float max);
		void RandomLifeTime(float min, float max);

	private:
		void Move(float deltaTime);
		void Fade();

		sf::Vector2f mVelocity;
		float mLifeTime = 1.f;
		sf::Clock mTimer;
	};
}

#endif // ASTROGLADE_ENGINE_VFX_PARTICLE_H
