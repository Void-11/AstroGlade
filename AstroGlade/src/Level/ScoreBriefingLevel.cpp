#include <algorithm>

#include "Level/ScoreBriefingLevel.h"
#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameAudio.h"
#include "widgets/ScoreBriefingHUD.h"

namespace ly
{
	ScoreBriefingLevel::ScoreBriefingLevel(Application* owningApplication)
		: World{owningApplication}
	{
		mScoreBriefingHUD = SpawnHUD<ScoreBriefingHUD>();
	}

	void ScoreBriefingLevel::BeginPlay()
	{
		GameAudio::PlayMenuMusic();
		SpawnBackground();

		mScoreBriefingHUD.lock()->onStartRunClicked.BindAction(GetWeakRef(), &ScoreBriefingLevel::StartRun);
		mScoreBriefingHUD.lock()->onBackClicked.BindAction(GetWeakRef(), &ScoreBriefingLevel::ReturnToMainMenu);
	}

	void ScoreBriefingLevel::StartRun()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void ScoreBriefingLevel::ReturnToMainMenu()
	{
		GetApplication()->LoadWorld<MainMenuLevel>();
	}

	void ScoreBriefingLevel::SpawnBackground()
	{
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
}
