#ifndef ASTROGLADE_ENGINE_GAMEPLAY_WAITSTAGE_H
#define ASTROGLADE_ENGINE_GAMEPLAY_WAITSTAGE_H

#include "gameplay/GameStage.h"

namespace ly
{
	// A pause between stages that finishes after a fixed duration.
	class WaitStage : public GameStage
	{
	public:
		explicit WaitStage(World* world, float waitDuration = 5.f);

		void StartStage() override;

	private:
		float mWaitDuration;
	};
}

#endif // ASTROGLADE_ENGINE_GAMEPLAY_WAITSTAGE_H
