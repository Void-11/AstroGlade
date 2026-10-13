#ifndef ASTROGLADE_ENGINE_WIDGETS_TEXTWIDGET_H
#define ASTROGLADE_ENGINE_WIDGETS_TEXTWIDGET_H

#include <string>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
	class TextWidget : public Widget
	{
	public:
		explicit TextWidget(const std::string& textStr,
			const std::string& fontPath = kDefaultFontPath,
			unsigned int characterSize = 10
		);

		void SetString(const std::string& newStr);
		void SetTextSize(unsigned int newSize);
		void SetTextColor(const sf::Color& color);
		[[nodiscard]] sf::FloatRect GetBounds() const override;

	private:
		void LocationUpdated(const sf::Vector2f& newLocation) override;
		void RotationUpdated(float newRotation) override;
		void Draw(sf::RenderWindow& windowRef) override;

		shared<sf::Font> mFont;
		sf::Text mText;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_TEXTWIDGET_H
