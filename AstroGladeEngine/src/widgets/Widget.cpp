#include "widgets/Widget.h"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (mIsVisible)
		{
			Draw(windowRef);
		}
	}

	bool Widget::HandleEvent([[maybe_unused]] const sf::Event& event)
	{
		return false;
	}

	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		mWidgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		mWidgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisibility(bool newVisibility)
	{
		mIsVisible = newVisibility;
	}

	sf::Vector2f Widget::GetCenterPosition() const
	{
		const sf::FloatRect bounds = GetBounds();
		return sf::Vector2f{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
	}

	void Widget::Draw([[maybe_unused]] sf::RenderWindow& windowRef)
	{
	}

	void Widget::LocationUpdated([[maybe_unused]] const sf::Vector2f& newLocation)
	{
	}

	void Widget::RotationUpdated([[maybe_unused]] float newRotation)
	{
	}
}
