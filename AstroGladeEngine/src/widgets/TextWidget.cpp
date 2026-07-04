#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"
namespace ly
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize)
		:mFont{},
		mText{}
	{
		mFont = AssetManager::Get().LoadFont(fontPath);
		if (!mFont)
		{
			LOG("Failed to load text widget font: %s", fontPath.c_str());
		}
		else
		{
			mText.setFont(*mFont);
		}

		mText.setString(textStr);
		mText.setCharacterSize(characterSize);
	}
	
	void TextWidget::SetString(const std::string& newStr)
	{
		mText.setString(newStr);
	}

	void TextWidget::SetTextSize(unsigned int newSize)
	{
		mText.setCharacterSize(newSize);
	}

	void TextWidget::SetTextColor(const sf::Color& color)
	{
		mText.setFillColor(color);
	}

sf::FloatRect TextWidget::GetBounds() const
	{
		return mText.getGlobalBounds();
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mText.setPosition(newLocation);
	}
	void TextWidget::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
	}
	void TextWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mText);
	}
}
