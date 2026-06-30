#include "framework/AssetManager.h"
#include "widgets/Button.h"
namespace ly
{
	Button::Button(const std::string& textString, const std::string& buttonTexturePath)
		: mButtonTexture{ AssetManager::Get().LoadTexture(buttonTexturePath) },
		mButtonSprite{ *(mButtonTexture.get()) },
		mButtonFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/Oxanium-SemiBold.ttf") },
		mButtonText(textString, *(mButtonFont.get())),
		mButtonDefaultColor{128,128,128,255},
		mButtonDownColor{64,64,64, 255},
		mButtonHoverColor{190, 190,190, 255},
		mTextDefaultColor{255, 255, 255, 255},
		mTextDownColor{200, 200, 200, 255},
		mTextHoverColor{255, 255, 255, 255},
		mIsButtonDown{false}
	{
		mButtonSprite.setColor(mButtonDefaultColor);
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
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBound = mButtonText.getGlobalBounds();
		mButtonText.setPosition(widgetCenter - sf::Vector2f{ textBound.width / 2.f, textBound.height });
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
		if (windowEvent.type == sf::Event::MouseButtonReleased)
		{
			if (windowEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y) && mIsButtonDown)
				{
					onButtonClicked.Broadcast();
					handled = true;
				}
			}
			ButtonUp();
		}
		else if (windowEvent.type == sf::Event::MouseButtonPressed)
		{
			if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
		}
		else if (windowEvent.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
				{
					MouseHovered();
				}
				else
				{
					ButtonUp();
				}
			}
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
