#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"
namespace ly
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: mTexture{},
		mSprite{}
	{
		mTexture = AssetManager::Get().LoadTexture(imagePath);
		if (!mTexture)
		{
			LOG("Failed to load image widget texture: %s", imagePath.c_str());
			return;
		}

		mSprite.setTexture(*mTexture);
	}
	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			mTexture = newTexture;
			mSprite.setTexture(*(mTexture.get()));
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

	void ImageWidget::Draw(sf::RenderWindow& winowRef)
	{
		winowRef.draw(mSprite);
	}

sf::FloatRect ImageWidget::GetBounds() const
	{
		return mSprite.getGlobalBounds();
	}
}
