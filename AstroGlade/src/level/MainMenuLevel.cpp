#include "framework/Application.h"
#include "gameplay/GameAudio.h"
#include "level/MainMenuLevel.h"
#include "level/MenuBackground.h"
#include "level/ScoreBriefingLevel.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApplication)
		: World{ owningApplication },
		mMainMenuHUD{ SpawnHUD<MainMenuHUD>() }
	{
	}

	void MainMenuLevel::BeginPlay()
	{
		GameAudio::PlayMenuMusic();
		if (const shared<MainMenuHUD> mainMenuHUD = mMainMenuHUD.lock())
		{
			mainMenuHUD->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
			mainMenuHUD->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
		}
		SpawnMenuBackground(*this);
	}

	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<ScoreBriefingLevel>();
	}

	void MainMenuLevel::QuitGame()
	{
		GameAudio::StopMusic();
		GetApplication()->QuitApplication();
	}
}
