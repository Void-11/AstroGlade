#include <cstddef>

#include "framework/AssetManager.h"
#include "framework/BackgroundLayer.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	BackgroundLayer::BackgroundLayer(World* owningWorld,
		const List<std::string>& assetPaths,
		const sf::Vector2f& minVel,
		const sf::Vector2f& maxVel,
		float sizeMin,
		float sizeMax,
		int spriteCount,
		const sf::Color& colorTint)
		: Actor{ owningWorld },
		mMinVelocity{ minVel },
		mMaxVelocity{ maxVel },
		mSizeMin{ sizeMin },
		mSizeMax{ sizeMax },
		mSpriteCount{ spriteCount },
		mTintColor{ colorTint }
	{
		SetAssets(assetPaths);
		SetEnablePhysics(false);
	}

	void BackgroundLayer::SetAssets(const List<std::string>& assetPaths)
	{
		mTextures.clear();
		for (const std::string& texturePath : assetPaths)
		{
			// A missing asset is logged by the AssetManager; the layer simply uses the remaining ones.
			if (shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath))
			{
				mTextures.push_back(std::move(newTexture));
			}
		}
		RefreshSprites();
	}

	void BackgroundLayer::RefreshSprites()
	{
		mSprites.clear();
		mVelocities.clear();

		for (int i = 0; i < mSpriteCount; ++i)
		{
			sf::Sprite& newSprite = mSprites.emplace_back();
			RandomSpriteTexture(newSprite);
			RandomSpriteTransform(newSprite, true);

			mVelocities.push_back(RandomVelocity());
		}

		SetColorTint(mTintColor);
	}

	void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite) const
	{
		if (mTextures.empty())
		{
			return;
		}

		const shared<sf::Texture>& pickedTexture = mTextures[RandomIndex(mTextures.size())];
		sprite.setTexture(*pickedTexture, true);

		// The origin is in local (untransformed) coordinates, so center it on the local bounds.
		const sf::FloatRect localBounds = sprite.getLocalBounds();
		sprite.setOrigin(localBounds.width / 2.f, localBounds.height / 2.f);
	}

	void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY) const
	{
		// Size and rotation come first so the position can use the final bounds of the sprite.
		RandomSpriteRotation(sprite);
		RandomSpriteSize(sprite);
		RandomSpritePosition(sprite, randomY);
	}

	void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY) const
	{
		const sf::Vector2u windowSize = GetWorld()->GetWindowSize();
		const sf::FloatRect bounds = sprite.getGlobalBounds();

		const float posX = RandomRange(0.f, static_cast<float>(windowSize.x));
		const float posY = randomY ? RandomRange(0.f, static_cast<float>(windowSize.y)) : -bounds.height;

		sprite.setPosition(sf::Vector2f{ posX, posY });
	}

	void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite) const
	{
		sprite.setRotation(RandomRange(0.f, 360.f));
	}

	void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite) const
	{
		const float size = RandomRange(mSizeMin, mSizeMax);
		sprite.setScale(size, size);
	}

	sf::Vector2f BackgroundLayer::RandomVelocity() const
	{
		return sf::Vector2f{ RandomRange(mMinVelocity.x, mMaxVelocity.x), RandomRange(mMinVelocity.y, mMaxVelocity.y) };
	}

	void BackgroundLayer::SetColorTint(const sf::Color& color)
	{
		mTintColor = color;
		for (sf::Sprite& sprite : mSprites)
		{
			sprite.setColor(color);
		}
	}

	void BackgroundLayer::SetSpriteCount(int newCount)
	{
		mSpriteCount = newCount;
		RefreshSprites();
	}

	void BackgroundLayer::Render(sf::RenderWindow& windowRef)
	{
		Actor::Render(windowRef);
		for (const sf::Sprite& sprite : mSprites)
		{
			windowRef.draw(sprite);
		}
	}

	void BackgroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		for (std::size_t i = 0; i < mSprites.size(); ++i)
		{
			sf::Sprite& sprite = mSprites[i];
			sprite.move(mVelocities[i] * deltaTime);

			if (IsSpriteOffScreen(sprite))
			{
				RandomSpriteTexture(sprite);
				RandomSpriteTransform(sprite);
				mVelocities[i] = RandomVelocity();
			}
		}
	}

	bool BackgroundLayer::IsSpriteOffScreen(const sf::Sprite& sprite) const
	{
		const sf::FloatRect bounds = sprite.getGlobalBounds();
		const sf::Vector2u windowSize = GetWorld()->GetWindowSize();
		const sf::Vector2f spritePos = sprite.getPosition();

		const bool offScreenX = spritePos.x < -bounds.width || spritePos.x > static_cast<float>(windowSize.x) + bounds.width;
		const bool offScreenY = spritePos.y < -bounds.height || spritePos.y > static_cast<float>(windowSize.y) + bounds.height;
		return offScreenX || offScreenY;
	}

	void BackgroundLayer::SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		mMinVelocity = min;
		mMaxVelocity = max;

		for (sf::Vector2f& velocity : mVelocities)
		{
			velocity = RandomVelocity();
		}
	}

	void BackgroundLayer::SetSizes(float min, float max)
	{
		mSizeMin = min;
		mSizeMax = max;

		for (sf::Sprite& sprite : mSprites)
		{
			RandomSpriteSize(sprite);
		}
	}
}
