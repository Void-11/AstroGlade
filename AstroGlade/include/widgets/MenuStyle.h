#ifndef ASTROGLADE_GAME_WIDGETS_MENUSTYLE_H
#define ASTROGLADE_GAME_WIDGETS_MENUSTYLE_H

#include <initializer_list>

#include <SFML/Graphics.hpp>

namespace ly
{
	class Button;
	class Widget;

	// The shared look of the AstroGlade menus: colors, fonts and the styling of buttons and panels.
	namespace MenuStyle
	{
		inline const sf::Color kAstroWhite{ 245, 248, 255, 255 };
		inline const sf::Color kMenuGreen{ 40, 255, 95, 255 };
		inline const sf::Color kGladeGreen{ 0, 255, 80, 255 };
		inline const sf::Color kTransparent{ 255, 255, 255, 0 };
		inline const sf::Color kHoverGlow{ 0, 255, 90, 55 };
		inline const sf::Color kDownGlow{ 0, 180, 65, 90 };
		inline const sf::Color kPanelFill{ 0, 0, 0, 165 };
		inline const sf::Color kPanelOutline{ 0, 255, 90, 220 };
		// Darkens the paused playfield so that the menu on top of it stays readable.
		inline const sf::Color kScreenDim{ 0, 0, 0, 140 };
		inline constexpr float kPanelOutlineThickness = 2.f;

		inline constexpr const char* kTitleFontPath = "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf";

		// A borderless text button that glows green when hovered or pressed.
		void ApplyMenuButtonStyle(Button& button, unsigned int textSize);

		// A translucent black panel with a thin green outline.
		void ApplyPanelStyle(sf::RectangleShape& panel);

		// Moves widget to y and centers its visible bounds horizontally in the window.
		void CenterHorizontally(Widget& widget, const sf::Vector2u& windowSize, float y);

		// Shifts the widgets together, keeping their relative layout, so that their combined bounds are centered on centerX.
		void CenterGroupHorizontally(std::initializer_list<Widget*> widgets, float centerX);
	}
}

#endif // ASTROGLADE_GAME_WIDGETS_MENUSTYLE_H
