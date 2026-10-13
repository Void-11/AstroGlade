#include <algorithm>
#include <filesystem>
#include <string_view>

#include "EntryPoint.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "gameFramework/GameApplication.h"
#include "level/MainMenuLevel.h"

namespace ly
{
	namespace
	{
		constexpr std::string_view kWindowedFlag = "--windowed";
		constexpr unsigned int kWindowedWidth = 1280;
		constexpr unsigned int kWindowedHeight = 720;
	}

	unique<Application> CreateApplication(const List<std::string_view>& commandLine)
	{
		const bool windowed = std::find(commandLine.begin(), commandLine.end(), kWindowedFlag) != commandLine.end();
		return std::make_unique<GameApplication>(windowed ? WindowMode::Windowed : WindowMode::Fullscreen);
	}

	GameApplication::GameApplication(WindowMode windowMode)
		: Application{ GetVideoMode(windowMode).width, GetVideoMode(windowMode).height, "AstroGlade", GetWindowStyle(windowMode) }
	{
		AssetManager::Get().SetAssetRootDirectory(std::filesystem::path{ config::kResourceDirectory });
		LoadWorld<MainMenuLevel>();
	}

	sf::VideoMode GameApplication::GetVideoMode(WindowMode windowMode)
	{
		return windowMode == WindowMode::Windowed
			? sf::VideoMode{ kWindowedWidth, kWindowedHeight }
			: sf::VideoMode::getDesktopMode();
	}

	sf::Uint32 GameApplication::GetWindowStyle(WindowMode windowMode)
	{
		return windowMode == WindowMode::Windowed
			? sf::Style::Titlebar | sf::Style::Close
			: sf::Style::Fullscreen;
	}
}
