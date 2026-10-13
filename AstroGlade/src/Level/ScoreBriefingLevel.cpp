#include "Level/GameLevelOne.h"
#include "Level/MainMenuLevel.h"
#include "Level/MenuBackground.h"
#include "Level/ScoreBriefingLevel.h"
#include "framework/Application.h"
#include "gameplay/GameAudio.h"
#include "widgets/ScoreBriefingHUD.h"

namespace ly
{
	ScoreBriefingLevel::ScoreBriefingLevel(Application* owningApplication)
		: World{ owningApplication },
		mScoreBriefingHUD{ SpawnHUD<ScoreBriefingHUD>() }
	{
	}

	void ScoreBriefingLevel::BeginPlay()
	{
		GameAudio::PlayMenuMusic();
		SpawnMenuBackground(*this);

		if (const shared<ScoreBriefingHUD> scoreBriefingHUD = mScoreBriefingHUD.lock())
		{
			scoreBriefingHUD->onStartRunClicked.BindAction(GetWeakRef(), &ScoreBriefingLevel::StartRun);
			scoreBriefingHUD->onBackClicked.BindAction(GetWeakRef(), &ScoreBriefingLevel::ReturnToMainMenu);
		}
	}

	void ScoreBriefingLevel::StartRun()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void ScoreBriefingLevel::ReturnToMainMenu()
	{
		GetApplication()->LoadWorld<MainMenuLevel>();
	}
}
