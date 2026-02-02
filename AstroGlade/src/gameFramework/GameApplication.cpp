#include "gameFramework/GameApplication.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, "AstroGlade" , sf::Style::Fullscreen }
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
	}
}

