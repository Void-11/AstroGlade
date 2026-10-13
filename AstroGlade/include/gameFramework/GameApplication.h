#ifndef ASTROGLADE_GAME_GAMEFRAMEWORK_GAMEAPPLICATION_H
#define ASTROGLADE_GAME_GAMEFRAMEWORK_GAMEAPPLICATION_H

#include <SFML/Graphics.hpp>

#include "framework/Application.h"

namespace ly
{
	enum class WindowMode
	{
		Fullscreen, // Covers the whole desktop at its native resolution (the default).
		Windowed    // A fixed size desktop window, selected with the --windowed command-line flag.
	};

	class GameApplication : public Application
	{
	public:
		explicit GameApplication(WindowMode windowMode = WindowMode::Fullscreen);

	private:
		[[nodiscard]] static sf::VideoMode GetVideoMode(WindowMode windowMode);
		[[nodiscard]] static sf::Uint32 GetWindowStyle(WindowMode windowMode);
	};
}

#endif // ASTROGLADE_GAME_GAMEFRAMEWORK_GAMEAPPLICATION_H
