#ifndef ASTROGLADE_GAME_LEVEL_SCOREBRIEFINGLEVEL_H
#define ASTROGLADE_GAME_LEVEL_SCOREBRIEFINGLEVEL_H

#include "framework/World.h"

namespace ly
{
	class ScoreBriefingHUD;

	// Explains the scoring rules before a run starts.
	class ScoreBriefingLevel : public World
	{
	public:
		explicit ScoreBriefingLevel(Application* owningApplication);

	private:
		void BeginPlay() override;
		void StartRun();
		void ReturnToMainMenu();

		weak<ScoreBriefingHUD> mScoreBriefingHUD;
	};
}

#endif // ASTROGLADE_GAME_LEVEL_SCOREBRIEFINGLEVEL_H
