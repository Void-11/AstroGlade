#ifndef ASTROGLADE_GAME_VFX_EXPLOSION_H
#define ASTROGLADE_GAME_VFX_EXPLOSION_H

#include <string>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	class World;

	// Tunables for a burst of particles; the defaults are the standard ship explosion.
	struct ExplosionSettings
	{
		int particleAmount = 20;
		float lifeTimeMin = 0.5f;
		float lifeTimeMax = 1.5f;
		float sizeMin = 1.f;
		float sizeMax = 3.f;
		float speedMin = 200.f;
		float speedMax = 400.f;
		sf::Color particleColor{ 255, 128, 0, 255 };
		List<std::string> particleImagePaths{
			"SpaceShooterRedux/PNG/Effects/star1.png",
			"SpaceShooterRedux/PNG/Effects/star2.png",
			"SpaceShooterRedux/PNG/Effects/star3.png"
		};
	};

	void SpawnExplosion(World& world, const sf::Vector2f& location, const ExplosionSettings& settings = {});
}

#endif // ASTROGLADE_GAME_VFX_EXPLOSION_H
