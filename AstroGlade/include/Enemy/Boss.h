#ifndef ASTROGLADE_GAME_ENEMY_BOSS_H
#define ASTROGLADE_GAME_ENEMY_BOSS_H

#include "Enemy/EnemySpaceship.h"
#include "weapon/FrontalWiper.h"
#include "weapon/LaserShooter.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	// Sweeps left and right across the top of the screen. As its health drops it enters
	// stages 2 to 4, which level up its weapons and speed it up.
	class Boss : public EnemySpaceship
	{
	public:
		explicit Boss(World* world);
		void Tick(float deltaTime) override;
		void BeginPlay() override;

	private:
		void CheckMove();
		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();
		void ShootFinalStageShooters();
		void HealthChanged(float amt, float currentHealth, float maxHealth);
		void SetStage(int newStage);

		static constexpr int kFinalStage = 4;

		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge = 100.f;

		LaserShooter mBaseShooterLeft;
		LaserShooter mBaseShooterRight;

		ThreeWayShooter mThreeWayShooter;
		FrontalWiper mFrontalWiperLeft;
		FrontalWiper mFrontalWiperRight;

		LaserShooter mFinalStageShooterLeft;
		LaserShooter mFinalStageShooterRight;

		int mStage = 1;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_BOSS_H
