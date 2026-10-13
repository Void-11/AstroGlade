#ifndef ASTROGLADE_GAME_WIDGETS_CONTROLSPANEL_H
#define ASTROGLADE_GAME_WIDGETS_CONTROLSPANEL_H

#include <SFML/Graphics.hpp>

#include "widgets/Button.h"
#include "widgets/TextWidget.h"

namespace ly
{
	// The key bindings overlay shared by the main menu and the pause menu.
	// The owning HUD binds the return button and decides when the panel is shown.
	class ControlsPanel
	{
	public:
		ControlsPanel();

		// Centers the panel in a window of windowSize. Call once the window size is known.
		void Layout(const sf::Vector2u& windowSize);
		void Draw(sf::RenderWindow& windowRef);
		bool HandleEvent(const sf::Event& event);

		void SetVisible(bool visible);
		[[nodiscard]] bool IsVisible() const { return mIsVisible; }

		Button& GetReturnButton() { return mReturnButton; }

	private:
		static constexpr float kPanelWidth = 640.f;
		static constexpr float kPanelHeight = 420.f;
		// Distance from the start of the keys column to the start of the actions column.
		static constexpr float kActionColumnOffset = 160.f;

		sf::RectangleShape mPanel;
		TextWidget mTitleText;
		TextWidget mKeysText;
		TextWidget mActionsText;
		Button mReturnButton;
		bool mIsVisible = false;
	};
}

#endif // ASTROGLADE_GAME_WIDGETS_CONTROLSPANEL_H
