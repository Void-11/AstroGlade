#include "Level/GameLevelOne.h"
#include "Enemy/UFO.h"
#include "Enemy/Vanguard.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/BackdropActor.h"
#include "framework/BackgroundLayer.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"
#include "Enemy/Hexagon.h"
#include "Enemy/BossStage.h"
#include "Enemy/ChaosStage.h"

#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"
#include "weapon/ThreeWayShooter.h"

#include <utility>

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{owningApp},
		mGameFinished{false},
		mBossFightActive{false},
		mRespawnTimerHandle{},
		mRespawnDelay{1.5f}
	{
		
	}

	void GameLevelOne::AllGameStageFinished()
	{
		FinishGame(true);
	}

	void GameLevelOne::OnGameStageStarted(GameStage& startedStage)
	{
		mBossFightActive = dynamic_cast<BossStage*>(&startedStage) != nullptr;
		if (mBossFightActive)
		{
			GameAudio::PlayBossMusic();
		}
	}

	void GameLevelOne::OnGameStageFinished(GameStage& finishedStage)
	{
		bool combatStageFinished = dynamic_cast<VanguardStage*>(&finishedStage)
			|| dynamic_cast<TwinBladeStage*>(&finishedStage)
			|| dynamic_cast<HexagonStage*>(&finishedStage)
			|| dynamic_cast<UFOStage*>(&finishedStage)
			|| dynamic_cast<ChaosStage*>(&finishedStage);

		if (combatStageFinished)
		{
			GameAudio::PlayStageClear();
			Player* player = PlayerManager::Get().GetPlayer();
			if (player)
			{
				player->IncreaseDefaultWeaponLevel();
			}
		}

		if (dynamic_cast<BossStage*>(&finishedStage))
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
	mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->onQuitBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->onRestartBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
		mGameplayHUD.lock()->onResumeBtnClicked.BindAction(GetWeakRef(), &GameLevelOne::ResumeGame);
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		if (mGameFinished)
		{
			return;
		}

		Player* player = PlayerManager::Get().GetPlayer();
		if (player && player->ConsumeLife())
		{
			mRespawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::RespawnPlayerSpaceship, mRespawnDelay);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
		AddStage(shared<VanguardStage>{new VanguardStage{this}});
		
		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
		
		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
		AddStage(shared<ChaosStage>{new ChaosStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 10.f }});
		AddStage(shared<BossStage>{new BossStage{ this }});
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
			bool isPaused = !IsPaused();
			SetPaused(isPaused);
			GameAudio::PlayPauseToggle();
			if (isPaused)
			{
				GameAudio::PauseMusic();
			}
			else
			{
				GameAudio::ResumeMusic();
			}
			if (!mGameplayHUD.expired())
			{
				mGameplayHUD.lock()->SetPause(isPaused);
			}
			return true;
		}
		
		return World::DispatchEvent(event);
	}

	void GameLevelOne::ResumeGame()
	{
		if (mGameFinished)
		{
			return;
		}

		SetPaused(false);
		GameAudio::ResumeMusic();
		if (!mGameplayHUD.expired())
		{
			mGameplayHUD.lock()->SetPause(false);
		}
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
		if (!mGameplayHUD.expired())
		{
			mGameplayHUD.lock()->GameFinished(playerWon);
		}
	}

	void GameLevelOne::RespawnPlayerSpaceship()
	{
		if (mGameFinished)
		{
			return;
		}

		Player* player = PlayerManager::Get().GetPlayer();
		if (!player)
		{
			GameOver();
			return;
		}

		mPlayerSpaceship = player->SpawnSpaceship(this);
		if (!mPlayerSpaceship.expired())
		{
			if (mBossFightActive)
			{
				ApplyBossRespawnLoadout(*mPlayerSpaceship.lock());
			}

			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
			if (!mGameplayHUD.expired())
			{
				mGameplayHUD.lock()->RefreshHealthBar();
			}
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::ApplyBossRespawnLoadout(PlayerSpaceship& playerSpaceship)
	{
		unique<Shooter> bossShooter{new ThreeWayShooter{&playerSpaceship, 0.4f, {50.f, 0.f}}};
		bossShooter->SetCurrentLevel(3);
		playerSpaceship.SetShooter(std::move(bossShooter));
	}

	void GameLevelOne::SpawnCosmetics()
	{
		auto windowSize = GetWindowSize();
		float scaleX = windowSize.x / 600.f;
		float scaleY = windowSize.y / 980.f;

		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/StellarDrift.png");
		weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
		planets.lock()->SetAssets(
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

		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(1, 1.5f);
		planets.lock()->SetVelocities({0, 30.f * scaleY} ,{0, 80.f * scaleY});


		weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
		meteors.lock()->SetAssets(
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

		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(.2f, .5f);
		meteors.lock()->SetVelocities({ 0, 50.f * scaleY }, { 0, 200.f * scaleY });
	}
}
