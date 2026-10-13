#include <cmath>
#include <string>

#include "widgets/ValueGuage.h"
#include "framework/AssetManager.h"
#include "framework/Log.h"

namespace ly
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
		: mTextFont{ AssetManager::Get().LoadFont(kDefaultFontPath) },
		mBarFront{ size },
		mBarBack{ size },
		mPercent{ initialPercent }
	{
		if (mTextFont)
		{
			mText.setFont(*mTextFont);
		}
		else
		{
			LogError("Failed to load value gauge font: ", kDefaultFontPath);
		}

		mBarFront.setFillColor(foregroundColor);
		mBarBack.setFillColor(backgroundColor);
		SetTextSize(20);
	}

	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0.f) return;

		mPercent = value / maxValue;
		mText.setString(std::to_string(static_cast<int>(value)) + "/" + std::to_string(static_cast<int>(maxValue)));

		const sf::Vector2f barSize = mBarBack.getSize();
		mBarFront.setSize({ barSize.x * mPercent, barSize.y });
		CenterText();
	}

	sf::FloatRect ValueGauge::GetBounds() const
	{
		return mBarBack.getGlobalBounds();
	}

	void ValueGauge::SetTextSize(unsigned int characterSize)
	{
		mText.setCharacterSize(characterSize);
	}

	void ValueGauge::SetTextColor(const sf::Color& color)
	{
		mText.setFillColor(color);
	}

	void ValueGauge::SetTextOutline(const sf::Color& color, float thickness)
	{
		mText.setOutlineColor(color);
		mText.setOutlineThickness(thickness);
		CenterText();
	}

	void ValueGauge::SetForegroundColor(const sf::Color& color)
	{
		mBarFront.setFillColor(color);
	}

	void ValueGauge::SetBackgroundColor(const sf::Color& color)
	{
		mBarBack.setFillColor(color);
	}

	void ValueGauge::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mBarBack);
		windowRef.draw(mBarFront);
		windowRef.draw(mText);
	}

	void ValueGauge::LocationUpdated(const sf::Vector2f& newLocation)
	{
		mBarFront.setPosition(newLocation);
		mBarBack.setPosition(newLocation);
		CenterText();
	}

	void ValueGauge::RotationUpdated(float newRotation)
	{
		mText.setRotation(newRotation);
		mBarFront.setRotation(newRotation);
		mBarBack.setRotation(newRotation);
	}

	void ValueGauge::CenterText()
	{
		const sf::Vector2f widgetCenter = GetCenterPosition();
		const sf::FloatRect textBounds = mText.getLocalBounds();
		const sf::Vector2f textLocation = widgetCenter - sf::Vector2f{ textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f };
		// Whole pixel positions keep the glyphs crisp.
		mText.setPosition(std::round(textLocation.x), std::round(textLocation.y));
	}
}
