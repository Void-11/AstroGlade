#ifndef ASTROGLADE_ENGINE_WIDGETS_VALUEGAUGE_H
#define ASTROGLADE_ENGINE_WIDGETS_VALUEGAUGE_H

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "widgets/Widget.h"

namespace ly
{
	// A horizontal bar that fills to value / maxValue and shows "value/maxValue" centered on top.
	class ValueGauge : public Widget
	{
	public:
		explicit ValueGauge(const sf::Vector2f& size = sf::Vector2f{ 200.f, 30.f },
			float initialPercent = 0.75f,
			const sf::Color& foregroundColor = sf::Color{ 128, 255, 128, 255 },
			const sf::Color& backgroundColor = sf::Color{ 128, 128, 128, 255 });

		void UpdateValue(float value, float maxValue);
		[[nodiscard]] sf::FloatRect GetBounds() const override;

		void SetTextSize(unsigned int characterSize);
		void SetTextColor(const sf::Color& color);
		// An outline keeps the text readable over both the filled and the empty part of the bar.
		void SetTextOutline(const sf::Color& color, float thickness);

		void SetForegroundColor(const sf::Color& color);
		void SetBackgroundColor(const sf::Color& color);

	private:
		void Draw(sf::RenderWindow& windowRef) override;
		void LocationUpdated(const sf::Vector2f& newLocation) override;
		void RotationUpdated(float newRotation) override;
		void CenterText();

		shared<sf::Font> mTextFont;
		sf::Text mText;

		sf::RectangleShape mBarFront;
		sf::RectangleShape mBarBack;

		float mPercent = 0.f;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_VALUEGAUGE_H
