#ifndef ASTROGLADE_ENGINE_FRAMEWORK_BACKGROUNDLAYER_H
#define ASTROGLADE_ENGINE_FRAMEWORK_BACKGROUNDLAYER_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	// Drifts a set of randomly picked, sized and rotated sprites across the window.
	// Sprites that leave the window are recycled at the top with fresh random values.
	class BackgroundLayer : public Actor
	{
	public:
		explicit BackgroundLayer(World* owningWorld,
			const List<std::string>& assetPaths = {},
			const sf::Vector2f& minVel = sf::Vector2f{ 0.f, 50.f },
			const sf::Vector2f& maxVel = sf::Vector2f{ 0.f, 200.f },
			float sizeMin = 1.f,
			float sizeMax = 2.f,
			int spriteCount = 20,
			const sf::Color& colorTint = sf::Color{ 180, 180, 200, 225 }
		);

		void SetAssets(const List<std::string>& assetPaths);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int newCount);
		void SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max);
		void SetSizes(float min, float max);

		void Render(sf::RenderWindow& windowRef) override;
		void Tick(float deltaTime) override;

	private:
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite) const;
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false) const;
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY) const;
		void RandomSpriteRotation(sf::Sprite& sprite) const;
		void RandomSpriteSize(sf::Sprite& sprite) const;
		[[nodiscard]] sf::Vector2f RandomVelocity() const;
		[[nodiscard]] bool IsSpriteOffScreen(const sf::Sprite& sprite) const;

		sf::Vector2f mMinVelocity;
		sf::Vector2f mMaxVelocity;
		float mSizeMin = 1.f;
		float mSizeMax = 2.f;
		int mSpriteCount = 0;
		sf::Color mTintColor;

		List<shared<sf::Texture>> mTextures;
		List<sf::Sprite> mSprites;
		List<sf::Vector2f> mVelocities;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_BACKGROUNDLAYER_H
