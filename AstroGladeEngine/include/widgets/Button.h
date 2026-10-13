#ifndef ASTROGLADE_ENGINE_WIDGETS_BUTTON_H
#define ASTROGLADE_ENGINE_WIDGETS_BUTTON_H

#include <string>

#include "framework/Core.h"
#include "framework/Delegate.h"
#include "widgets/Widget.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		explicit Button(const std::string& textString = "Button", const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

		[[nodiscard]] sf::FloatRect GetBounds() const override;
		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int characterSize);
		void SetButtonColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor);
		void SetTextColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor);
		bool HandleEvent(const sf::Event& windowEvent) override;

		Delegate<> onButtonClicked;

	private:
		void Draw(sf::RenderWindow& windowRef) override;
		void LocationUpdated(const sf::Vector2f& location) override;
		void RotationUpdated(float rotation) override;
		void CenterText();
		[[nodiscard]] bool ContainsPoint(int x, int y) const;

		void ButtonUp();
		void ButtonDown();
		void MouseHovered();

		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;

		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor{ 128, 128, 128, 255 };
		sf::Color mButtonDownColor{ 64, 64, 64, 255 };
		sf::Color mButtonHoverColor{ 190, 190, 190, 255 };
		sf::Color mTextDefaultColor{ 255, 255, 255, 255 };
		sf::Color mTextDownColor{ 200, 200, 200, 255 };
		sf::Color mTextHoverColor{ 255, 255, 255, 255 };

		bool mIsButtonDown = false;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_BUTTON_H
