#include <initializer_list>

#include "enemy/Boss.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/HealthComponent.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	namespace
	{
		constexpr float kBossBaseSpeed = 100.f;
		constexpr float kBossHealth = 3000.f;
	}

	Boss::Boss(World* world)
		: EnemySpaceship{ world, "SpaceShooterRedux/PNG/Enemies/boss.png", 200.f },
		mSpeed{ kBossBaseSpeed * GetResolutionScale(world->GetWindowSize()).x },
		mBaseSpeed{ mSpeed },
		mBaseShooterLeft{ this, 1.f, { 50.f, -50.f } },
		mBaseShooterRight{ this, 1.f, { 50.f, 50.f } },
		mThreeWayShooter{ this, 4.f, { 100.f, 0.f } },
		mFrontalWiperLeft{ this, 5.f, { 80.f, -100.f } },
		mFrontalWiperRight{ this, 5.f, { 80.f, 100.f } },
		mFinalStageShooterLeft{ this, 0.3f, { 50.f, -150.f } },
		mFinalStageShooterRight{ this, 0.3f, { 50.f, 150.f } }
	{
		SetActorRotation(90.f);
		SetVelocity({ mSpeed, 0.f });
		SetRewardSpawnWeight(0.f);
		SetScoreAwardAmt(100);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootFrontalWipers();
		ShootThreeWayShooter();
		if (mStage == kFinalStage)
		{
			ShootFinalStageShooters();
		}
		CheckMove();
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();
		HealthComponent& healthComp = GetHealthComp();
		healthComp.SetInitialHealth(kBossHealth, kBossHealth);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
	}

	void Boss::CheckMove()
	{
		const float locationX = GetActorLocation().x;
		if (locationX > static_cast<float>(GetWindowSize().x) - mSwitchDistanceToEdge)
		{
			SetVelocity({ -mSpeed, 0.f });
		}
		else if (locationX < mSwitchDistanceToEdge)
		{
			SetVelocity({ mSpeed, 0.f });
		}
	}

	void Boss::ShootBaseShooters()
	{
		if (ShootAll(mBaseShooterLeft, mBaseShooterRight))
		{
			GameAudio::PlayBossShoot();
		}
	}

	void Boss::ShootThreeWayShooter()
	{
		if (mThreeWayShooter.Shoot())
		{
			GameAudio::PlayBossShoot();
		}
	}

	void Boss::ShootFrontalWipers()
	{
		if (ShootAll(mFrontalWiperLeft, mFrontalWiperRight))
		{
			GameAudio::PlayBossShoot();
		}
	}

	void Boss::ShootFinalStageShooters()
	{
		if (ShootAll(mFinalStageShooterLeft, mFinalStageShooterRight))
		{
			GameAudio::PlayBossShoot();
		}
	}

	void Boss::HealthChanged([[maybe_unused]] float amt, float currentHealth, float maxHealth)
	{
		const float percentLeft = currentHealth / maxHealth;
		if (percentLeft < 0.7f && percentLeft > 0.5f)
		{
			SetStage(2);
		}

		if (percentLeft < 0.5f && percentLeft > 0.3f)
		{
			SetStage(3);
		}

		if (percentLeft < 0.3f)
		{
			SetStage(kFinalStage);
		}
	}

	void Boss::SetStage(int newStage)
	{
		mStage = newStage;
		for (Shooter* shooter : std::initializer_list<Shooter*>{ &mBaseShooterLeft, &mBaseShooterRight, &mFrontalWiperLeft, &mFrontalWiperRight, &mThreeWayShooter })
		{
			shooter->SetCurrentLevel(mStage);
		}
		mSpeed = static_cast<float>(mStage) * mBaseSpeed;
	}
}
