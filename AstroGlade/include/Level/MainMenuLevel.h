#ifndef ASTROGLADE_GAME_LEVEL_MAINMENULEVEL_H
#define ASTROGLADE_GAME_LEVEL_MAINMENULEVEL_H

#include "framework/World.h"

namespace ly
{
	class MainMenuHUD;

	class MainMenuLevel : public World
	{
	public:
		explicit MainMenuLevel(Application* owningApplication);

	private:
		void BeginPlay() override;
		void StartGame();
		void QuitGame();

		weak<MainMenuHUD> mMainMenuHUD;
	};
}

#endif // ASTROGLADE_GAME_LEVEL_MAINMENULEVEL_H
