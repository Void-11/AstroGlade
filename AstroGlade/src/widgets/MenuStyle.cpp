#include <algorithm>
#include <cmath>
#include <limits>

#include "widgets/Button.h"
#include "widgets/MenuStyle.h"
#include "widgets/Widget.h"

namespace ly::MenuStyle
{
	void ApplyMenuButtonStyle(Button& button, unsigned int textSize)
	{
		button.SetTextSize(textSize);
		button.SetButtonColors(kTransparent, kHoverGlow, kDownGlow);
		button.SetTextColors(kAstroWhite, kMenuGreen, kMenuGreen);
	}

	void ApplyPanelStyle(sf::RectangleShape& panel)
	{
		panel.setFillColor(kPanelFill);
		panel.setOutlineColor(kPanelOutline);
		panel.setOutlineThickness(kPanelOutlineThickness);
	}

	void CenterHorizontally(Widget& widget, const sf::Vector2u& windowSize, float y)
	{
		widget.SetWidgetLocation({ widget.GetWidgetLocation().x, y });
		CenterGroupHorizontally({ &widget }, static_cast<float>(windowSize.x) / 2.f);
	}

	void CenterGroupHorizontally(std::initializer_list<Widget*> widgets, float centerX)
	{
		if (widgets.size() == 0)
		{
			return;
		}

		float left = std::numeric_limits<float>::max();
		float right = std::numeric_limits<float>::lowest();
		for (const Widget* const widget : widgets)
		{
			const sf::FloatRect bounds = widget->GetBounds();
			left = std::min(left, bounds.left);
			right = std::max(right, bounds.left + bounds.width);
		}

		const float offset = centerX - (left + right) / 2.f;
		for (Widget* const widget : widgets)
		{
			const sf::Vector2f location = widget->GetWidgetLocation();
			// Whole pixel positions keep text glyphs and sprites crisp.
			widget->SetWidgetLocation({ std::round(location.x + offset), location.y });
		}
	}
}
