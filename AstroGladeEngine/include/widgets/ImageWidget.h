#ifndef ASTROGLADE_ENGINE_WIDGETS_IMAGEWIDGET_H
#define ASTROGLADE_ENGINE_WIDGETS_IMAGEWIDGET_H

#include <string>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
	class ImageWidget : public Widget
	{
	public:
		explicit ImageWidget(const std::string& imagePath);

		void SetImage(const shared<sf::Texture>& newTexture);
		void SetImageScale(const sf::Vector2f& newScale);
		[[nodiscard]] sf::FloatRect GetBounds() const override;

	private:
		void LocationUpdated(const sf::Vector2f& newLocation) override;
		void RotationUpdated(float newRotation) override;
		void Draw(sf::RenderWindow& windowRef) override;

		shared<sf::Texture> mTexture;
		sf::Sprite mSprite;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_IMAGEWIDGET_H
