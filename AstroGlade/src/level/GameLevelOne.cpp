#include "enemy/BossStage.h"
#include "enemy/ChaosStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "enemy/VanguardStage.h"
#include "framework/Application.h"
#include "framework/BackdropActor.h"
#include "framework/BackgroundLayer.h"
#include "framework/TimerManager.h"
#include "gameplay/GameAudio.h"
#include "gameplay/ResolutionScale.h"
#include "gameplay/WaitStage.h"
#include "level/GameLevelOne.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	namespace
	{
		template<typename... StageTypes>
		[[nodiscard]] bool IsAnyOf(const GameStage& stage)
		{
			return (... || (dynamic_cast<const StageTypes*>(&stage) != nullptr));
		}
	}

	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{ owningApp }
	{
	}

	void GameLevelOne::AllGameStageFinished()
	{
		FinishGame(true);
	}

	void GameLevelOne::OnGameStageStarted(GameStage& startedStage)
	{
		mBossFightActive = IsAnyOf<BossStage>(startedStage);
		if (mBossFightActive)
		{
			GameAudio::PlayBossMusic();
		}
	}

	void GameLevelOne::OnGameStageFinished(GameStage& finishedStage)
	{
		if (IsAnyOf<VanguardStage, TwinBladeStage, HexagonStage, UFOStage, ChaosStage>(finishedStage))
		{
			GameAudio::PlayStageClear();
			if (Player* const player = PlayerManager::Get().GetPlayer())
			{
				player->IncreaseDefaultWeaponLevel();
			}
		}

		if (IsAnyOf<BossStage>(finishedStage))
		{
			mBossFightActive = false;
		}
	}

	void GameLevelOne::BeginPlay()
	{
		GameAudio::PlayGameplayMusic();
		SpawnCosmetics();

		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		BindPlayerSpaceship();

		mGameplayHUD = SpawnHUD<GameplayHUD>();
		if (const shared<GameplayHUD> gameplayHUD = mGameplayHUD.lock())
		{
			gameplayHUD->onQuitBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
			gameplayHUD->onRestartBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
			gameplayHUD->onResumeBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::ResumeGame);
		}
	}

	void GameLevelOne::PlayerSpaceshipDestroyed([[maybe_unused]] Actor* destroyedPlayerSpaceship)
	{
		if (mGameFinished)
		{
			return;
		}

		if (Player* const player = PlayerManager::Get().GetPlayer(); player && player->ConsumeLife())
		{
			TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::RespawnPlayerSpaceship, mRespawnDelay);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(std::make_shared<WaitStage>(this, 5.f));
		AddStage(std::make_shared<VanguardStage>(this));

		AddStage(std::make_shared<WaitStage>(this, 10.f));
		AddStage(std::make_shared<TwinBladeStage>(this));

		AddStage(std::make_shared<WaitStage>(this, 10.f));
		AddStage(std::make_shared<HexagonStage>(this));

		AddStage(std::make_shared<WaitStage>(this, 10.f));
		AddStage(std::make_shared<UFOStage>(this));

		AddStage(std::make_shared<WaitStage>(this, 10.f));
		AddStage(std::make_shared<ChaosStage>(this));

		AddStage(std::make_shared<WaitStage>(this, 10.f));
		AddStage(std::make_shared<BossStage>(this));
	}

	bool GameLevelOne::DispatchEvent(const sf::Event& event)
	{
		if (mGameFinished)
		{
			return World::DispatchEvent(event);
		}

		if (IsPaused() && World::DispatchEvent(event))
		{
			return true;
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			GameAudio::PlayPauseToggle();
			SetPausedWithMusic(!IsPaused());
			return true;
		}

		return World::DispatchEvent(event);
	}

	void GameLevelOne::SetPausedWithMusic(bool paused)
	{
		SetPaused(paused);
		if (paused)
		{
			GameAudio::PauseMusic();
		}
		else
		{
			GameAudio::ResumeMusic();
		}

		if (const shared<GameplayHUD> gameplayHUD = mGameplayHUD.lock())
		{
			gameplayHUD->SetPause(paused);
		}
	}

	void GameLevelOne::ResumeGame()
	{
		if (mGameFinished)
		{
			return;
		}

		SetPausedWithMusic(false);
	}

	void GameLevelOne::QuitGame()
	{
		GameAudio::StopMusic();
		GetApplication()->QuitApplication();
	}

	void GameLevelOne::Restart()
	{
		GameAudio::StopMusic();
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::GameOver()
	{
		FinishGame(false);
	}

	void GameLevelOne::FinishGame(bool playerWon)
	{
		if (mGameFinished)
		{
			return;
		}

		mGameFinished = true;
		SetPaused(true);
		GameAudio::StopMusic();
		if (playerWon)
		{
			GameAudio::PlayWin();
		}
		else
		{
			GameAudio::PlayGameOver();
		}

		if (const shared<GameplayHUD> gameplayHUD = mGameplayHUD.lock())
		{
			gameplayHUD->GameFinished(playerWon);
		}
	}

	void GameLevelOne::RespawnPlayerSpaceship()
	{
		if (mGameFinished)
		{
			return;
		}

		Player* const player = PlayerManager::Get().GetPlayer();
		if (!player)
		{
			GameOver();
			return;
		}

		mPlayerSpaceship = player->SpawnSpaceship(this);
		const shared<PlayerSpaceship> playerSpaceship = mPlayerSpaceship.lock();
		if (!playerSpaceship)
		{
			GameOver();
			return;
		}

		if (mBossFightActive)
		{
			ApplyBossRespawnLoadout(*playerSpaceship);
		}

		BindPlayerSpaceship();
		if (const shared<GameplayHUD> gameplayHUD = mGameplayHUD.lock())
		{
			gameplayHUD->RefreshHealthBar();
		}
	}

	void GameLevelOne::BindPlayerSpaceship()
	{
		if (const shared<PlayerSpaceship> playerSpaceship = mPlayerSpaceship.lock())
		{
			playerSpaceship->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
	}

	void GameLevelOne::ApplyBossRespawnLoadout(PlayerSpaceship& playerSpaceship)
	{
		auto bossShooter = std::make_unique<ThreeWayShooter>(&playerSpaceship, 0.4f, sf::Vector2f{ 50.f, 0.f });
		bossShooter->SetCurrentLevel(3);
		playerSpaceship.SetShooter(std::move(bossShooter));
	}

	void GameLevelOne::SpawnCosmetics()
	{
		const float scaleY = GetResolutionScale(GetWindowSize()).y;

		SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/StellarDrift.png");

		if (const shared<BackgroundLayer> planets = SpawnActor<BackgroundLayer>().lock())
		{
			planets->SetAssets(
				{
					"SpaceShooterRedux/PNG/Planets/Planet1.png",
					"SpaceShooterRedux/PNG/Planets/Planet2.png",
					"SpaceShooterRedux/PNG/Planets/Planet3.png",
					"SpaceShooterRedux/PNG/Planets/Planet4.png",
					"SpaceShooterRedux/PNG/Planets/Planet5.png",
					"SpaceShooterRedux/PNG/Planets/Planet6.png",
					"SpaceShooterRedux/PNG/Planets/Planet7.png"
				}
			);

			planets->SetSpriteCount(1);
			planets->SetSizes(1.f, 1.5f);
			planets->SetVelocities({ 0.f, 30.f * scaleY }, { 0.f, 80.f * scaleY });
		}

		if (const shared<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>().lock())
		{
			meteors->SetAssets(
				{
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
					"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
				}
			);

			meteors->SetSpriteCount(20);
			meteors->SetSizes(0.2f, 0.5f);
			meteors->SetVelocities({ 0.f, 50.f * scaleY }, { 0.f, 200.f * scaleY });
		}
	}
}
