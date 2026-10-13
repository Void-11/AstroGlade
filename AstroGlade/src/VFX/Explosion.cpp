#include "framework/MathUtility.h"
#include "framework/World.h"
#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace ly
{
	void SpawnExplosion(World& world, const sf::Vector2f& location, const ExplosionSettings& settings)
	{
		if (settings.particleImagePaths.empty())
		{
			return;
		}

		for (int i = 0; i < settings.particleAmount; ++i)
		{
			const std::string& particleImagePath = settings.particleImagePaths[RandomIndex(settings.particleImagePaths.size())];
			if (const shared<Particle> particle = world.SpawnActor<Particle>(particleImagePath).lock())
			{
				particle->RandomLifeTime(settings.lifeTimeMin, settings.lifeTimeMax);
				particle->SetActorLocation(location);
				particle->RandomSize(settings.sizeMin, settings.sizeMax);
				particle->RandomVelocity(settings.speedMin, settings.speedMax);
				particle->GetSprite().setColor(settings.particleColor);
			}
		}
	}
}
