#include "Enemy/SpawnLocations.h"
#include "framework/MathUtility.h"

namespace ly
{
	sf::Vector2f RandomSideSpawnLocation(const sf::Vector2u& windowSize)
	{
		const bool spawnOnRight = RandomRange(-1.f, 1.f) < 0.f;
		const float spawnX = spawnOnRight ? static_cast<float>(windowSize.x) + kOffscreenSpawnMargin : -kOffscreenSpawnMargin;
		const float spawnY = RandomRange(0.f, static_cast<float>(windowSize.y));
		return sf::Vector2f{ spawnX, spawnY };
	}

	sf::Vector2f RandomTopSpawnLocation(const sf::Vector2u& windowSize)
	{
		const float spawnX = RandomRange(kOffscreenSpawnMargin, static_cast<float>(windowSize.x) - kOffscreenSpawnMargin);
		return sf::Vector2f{ spawnX, -kOffscreenSpawnMargin };
	}

	sf::Vector2f DirectionToWindowCenter(const sf::Vector2f& location, const sf::Vector2u& windowSize)
	{
		const sf::Vector2f center{ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f };
		sf::Vector2f direction = center - location;
		return Normalize(direction);
	}
}
