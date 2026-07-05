#pragma once

#include "framework/World.h"

namespace ly
{
	class ScoreBriefingHUD;

	class ScoreBriefingLevel : public World
	{
	public:
		ScoreBriefingLevel(Application* owningApplication);
		virtual void BeginPlay() override;

	private:
		weak<ScoreBriefingHUD> mScoreBriefingHUD;

		void StartRun();
		void ReturnToMainMenu();
		void SpawnBackground();
	};
}
