#ifndef ASTROGLADE_ENGINE_WIDGETS_WIDGET_H
#define ASTROGLADE_ENGINE_WIDGETS_WIDGET_H

#include <SFML/Graphics.hpp>

#include "framework/Object.h"

namespace ly
{
	// Font used by the text based widgets when no other font is given.
	inline constexpr const char* kDefaultFontPath = "SpaceShooterRedux/Bonus/Oxanium-SemiBold.ttf";

	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);
		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);
		[[nodiscard]] sf::Vector2f GetWidgetLocation() const { return mWidgetTransform.getPosition(); }
		[[nodiscard]] float GetWidgetRotation() const { return mWidgetTransform.getRotation(); }

		void SetVisibility(bool newVisibility);
		[[nodiscard]] bool GetVisibility() const { return mIsVisible; }
		[[nodiscard]] virtual sf::FloatRect GetBounds() const = 0;
		[[nodiscard]] sf::Vector2f GetCenterPosition() const;

	protected:
		Widget() = default;

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

		sf::Transformable mWidgetTransform;
		bool mIsVisible = true;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_WIDGET_H
