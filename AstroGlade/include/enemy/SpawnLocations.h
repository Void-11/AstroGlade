#ifndef ASTROGLADE_GAME_ENEMY_SPAWNLOCATIONS_H
#define ASTROGLADE_GAME_ENEMY_SPAWNLOCATIONS_H

#include <SFML/Graphics.hpp>

namespace ly
{
	// Enemies spawn this far outside the window so they fly in rather than pop into view.
	inline constexpr float kOffscreenSpawnMargin = 100.f;

	// Just beyond the left or right edge (picked at random), at a random height.
	[[nodiscard]] sf::Vector2f RandomSideSpawnLocation(const sf::Vector2u& windowSize);

	// Just above the window, at a random horizontal position at least kOffscreenSpawnMargin from either edge.
	[[nodiscard]] sf::Vector2f RandomTopSpawnLocation(const sf::Vector2u& windowSize);

	// The unit vector pointing from location to the center of the window.
	[[nodiscard]] sf::Vector2f DirectionToWindowCenter(const sf::Vector2f& location, const sf::Vector2u& windowSize);
}

#endif // ASTROGLADE_GAME_ENEMY_SPAWNLOCATIONS_H
