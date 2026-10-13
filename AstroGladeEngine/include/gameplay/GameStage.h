#ifndef ASTROGLADE_ENGINE_GAMEPLAY_GAMESTAGE_H
#define ASTROGLADE_ENGINE_GAMEPLAY_GAMESTAGE_H

#include "framework/Core.h"
#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly
{
	class Actor;
	class World;

	// One step of a level. A spawning stage tracks the actors it spawns, calls FinishSpawning()
	// once it is done spawning, and then finishes on its own when every tracked actor is gone.
	class GameStage : public Object
	{
	public:
		explicit GameStage(World* world);

		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		[[nodiscard]] bool IsStageFinished() const { return mStageFinished; }

	protected:
		void TrackActor(const weak<Actor>& actor);
		void FinishStageIfTrackedActorsDestroyed();
		void ClearTrackedActors();

		void FinishSpawning();
		[[nodiscard]] bool IsSpawningFinished() const { return mSpawningFinished; }

	private:
		virtual void StageFinished();
		[[nodiscard]] bool HasActiveTrackedActors();

		World* mWorld;
		bool mStageFinished = false;
		bool mSpawningFinished = false;
		List<weak<Actor>> mTrackedActors;
	};
}

#endif // ASTROGLADE_ENGINE_GAMEPLAY_GAMESTAGE_H
