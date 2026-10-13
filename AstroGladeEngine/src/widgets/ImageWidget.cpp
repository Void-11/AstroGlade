#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"
#include "framework/Log.h"

namespace ly
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: mTexture{ AssetManager::Get().LoadTexture(imagePath) }
	{
		if (!mTexture)
		{
			LogError("Failed to load image widget texture: ", imagePath);
			return;
		}

		mSprite.setTexture(*mTexture);
	}

	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			mTexture = newTexture;
			mSprite.setTexture(*mTexture);
		}
	}

	void ImageWidget::SetImageScale(const sf::Vector2f& newScale)
	{
		mSprite.setScale(newScale);
	}

	void ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}

	void ImageWidget::RotationUpdated(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}

	void ImageWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mSprite);
	}

	sf::FloatRect ImageWidget::GetBounds() const
	{
		return mSprite.getGlobalBounds();
	}
}
