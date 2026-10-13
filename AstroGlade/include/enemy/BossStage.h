#ifndef ASTROGLADE_GAME_ENEMY_BOSSSTAGE_H
#define ASTROGLADE_GAME_ENEMY_BOSSSTAGE_H

#include "gameplay/GameStage.h"

namespace ly
{
	class Actor;

	// Spawns the Boss and finishes when it is destroyed.
	class BossStage : public GameStage
	{
	public:
		explicit BossStage(World* world);
		void StartStage() override;

	private:
		void BossDestroyed(Actor* bossActor);
	};
}

#endif // ASTROGLADE_GAME_ENEMY_BOSSSTAGE_H
