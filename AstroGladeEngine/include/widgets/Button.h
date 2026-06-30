#pragma once

#include "widgets/Widget.h"
#include "framework/Delegate.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button", const std::string& buttonTexturePath="SpaceShooterRedux/PNG/UI/buttonBlue.png");
		virtual sf::FloatRect GetBounds() const;
		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int characterSize);
		void SetButtonColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor);
		void SetTextColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor);
		virtual bool HandleEvent(const sf::Event& windowEvent) override;
		Delegate<> onButtonClicked;
	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& location);
		virtual void RotationUpdated(float rotation);
		void CenterText();
		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;

		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;
		sf::Color mTextDefaultColor;
		sf::Color mTextDownColor;
		sf::Color mTextHoverColor;

		bool mIsButtonDown;

		void ButtonUp();
		void ButtonDown();
		void MouseHovered();
	};
}
