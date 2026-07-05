#include <algorithm>

#include "Level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"
#include "framework/Application.h"
#include "gameplay/GameAudio.h"
#include "Level/ScoreBriefingLevel.h"
#include "framework/Actor.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApplication)
		: World{owningApplication}
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPlay()
	{
		GameAudio::PlayMenuMusic();
		mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
		weak<Actor> background = SpawnActor<Actor>("SpaceShooterRedux/mainMenuBg.png");
		if (!background.expired())
		{
			sf::Vector2u windowSize = GetWindowSize();
			sf::FloatRect bounds = background.lock()->GetActorGlobalBounds();
			float scale = std::max(windowSize.x / bounds.width, windowSize.y / bounds.height);

			background.lock()->GetSprite().setScale(scale, scale);
			background.lock()->SetActorLocation({ windowSize.x / 2.f, windowSize.y / 2.f });
		}
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
