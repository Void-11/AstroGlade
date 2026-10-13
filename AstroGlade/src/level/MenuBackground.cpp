#include <algorithm>

#include "level/MenuBackground.h"
#include "framework/Actor.h"
#include "framework/World.h"

namespace ly
{
	void SpawnMenuBackground(World& world)
	{
		const shared<Actor> background = world.SpawnActor<Actor>("SpaceShooterRedux/mainMenuBg.png").lock();
		if (!background)
		{
			return;
		}

		const sf::FloatRect bounds = background->GetActorGlobalBounds();
		if (bounds.width <= 0.f || bounds.height <= 0.f)
		{
			return; // The texture failed to load; the AssetManager has already reported it.
		}

		const sf::Vector2f windowSize{ world.GetWindowSize() };
		const float scale = std::max(windowSize.x / bounds.width, windowSize.y / bounds.height);

		background->GetSprite().setScale(scale, scale);
		background->SetActorLocation(windowSize / 2.f);
	}
}
