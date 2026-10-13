#include <cmath>

#include "framework/AssetManager.h"
#include "framework/Log.h"
#include "widgets/Button.h"

namespace ly
{
	namespace
	{
		// The vertical middle of a capital letter in the text's local space, where SFML puts the baseline at the character size.
		// Centering on it rather than on the string's own bounds keeps every label on the same baseline,
		// whatever its descenders, such as the tail of a "Q".
		[[nodiscard]] float CapHeightCenter(const sf::Text& text)
		{
			const sf::Font* const font = text.getFont();
			if (!font)
			{
				const sf::FloatRect textBounds = text.getLocalBounds();
				return textBounds.top + textBounds.height / 2.f;
			}

			const bool isBold = (text.getStyle() & sf::Text::Bold) != 0;
			const sf::FloatRect capBounds = font->getGlyph(U'H', text.getCharacterSize(), isBold).bounds;
			return static_cast<float>(text.getCharacterSize()) + capBounds.top + capBounds.height / 2.f;
		}
	}

	Button::Button(const std::string& textString, const std::string& buttonTexturePath)
		: mButtonTexture{ AssetManager::Get().LoadTexture(buttonTexturePath) },
		mButtonFont{ AssetManager::Get().LoadFont(kDefaultFontPath) }
	{
		if (mButtonTexture)
		{
			mButtonSprite.setTexture(*mButtonTexture);
			mButtonSprite.setColor(mButtonDefaultColor);
		}
		else
		{
			LogError("Failed to load button texture: ", buttonTexturePath);
		}

		if (mButtonFont)
		{
			mButtonText.setFont(*mButtonFont);
		}
		else
		{
			LogError("Failed to load button font: ", kDefaultFontPath);
		}

		mButtonText.setString(textString);
		mButtonText.setFillColor(mTextDefaultColor);
		CenterText();
	}

	void Button::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mButtonSprite);
		windowRef.draw(mButtonText);
	}

	void Button::LocationUpdated(const sf::Vector2f& location)
	{
		mButtonSprite.setPosition(location);
		CenterText();
	}

	void Button::RotationUpdated(float rotation)
	{
		mButtonSprite.setRotation(rotation);
		mButtonText.setRotation(rotation);
	}

	sf::FloatRect Button::GetBounds() const
	{
		return mButtonSprite.getGlobalBounds();
	}

	void Button::CenterText()
	{
		const sf::Vector2f widgetCenter = GetCenterPosition();
		const sf::FloatRect textBounds = mButtonText.getLocalBounds();
		const sf::Vector2f textCenter{ textBounds.left + textBounds.width / 2.f, CapHeightCenter(mButtonText) };

		// Whole pixel positions keep the glyphs crisp.
		mButtonText.setPosition(std::round(widgetCenter.x - textCenter.x), std::round(widgetCenter.y - textCenter.y));
	}

	bool Button::ContainsPoint(int x, int y) const
	{
		return GetBounds().contains(static_cast<float>(x), static_cast<float>(y));
	}

	void Button::SetTextString(const std::string& newStr)
	{
		mButtonText.setString(newStr);
		CenterText();
	}

	void Button::SetTextSize(unsigned int characterSize)
	{
		mButtonText.setCharacterSize(characterSize);
		CenterText();
	}

	void Button::SetButtonColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor)
	{
		mButtonDefaultColor = defaultColor;
		mButtonHoverColor = hoverColor;
		mButtonDownColor = downColor;
		ButtonUp();
	}

	void Button::SetTextColors(const sf::Color& defaultColor, const sf::Color& hoverColor, const sf::Color& downColor)
	{
		mTextDefaultColor = defaultColor;
		mTextHoverColor = hoverColor;
		mTextDownColor = downColor;
		ButtonUp();
	}

	bool Button::HandleEvent(const sf::Event& windowEvent)
	{
		if (!GetVisibility()) return false;

		bool handled = false;
		switch (windowEvent.type)
		{
		case sf::Event::MouseButtonReleased:
			if (windowEvent.mouseButton.button == sf::Mouse::Left
				&& mIsButtonDown
				&& ContainsPoint(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				onButtonClicked.Broadcast();
				handled = true;
			}
			ButtonUp();
			break;

		case sf::Event::MouseButtonPressed:
			if (ContainsPoint(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
			break;

		case sf::Event::MouseMoved:
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (ContainsPoint(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
				{
					MouseHovered();
				}
				else
				{
					ButtonUp();
				}
			}
			break;

		default:
			break;
		}

		return handled || Widget::HandleEvent(windowEvent);
	}

	void Button::ButtonUp()
	{
		mIsButtonDown = false;
		mButtonSprite.setColor(mButtonDefaultColor);
		mButtonText.setFillColor(mTextDefaultColor);
	}

	void Button::ButtonDown()
	{
		mIsButtonDown = true;
		mButtonSprite.setColor(mButtonDownColor);
		mButtonText.setFillColor(mTextDownColor);
	}

	void Button::MouseHovered()
	{
		mButtonSprite.setColor(mButtonHoverColor);
		mButtonText.setFillColor(mTextHoverColor);
	}
}
