#include "levels/LevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/World.h"
#include "framework/Application.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"
#include "widgets/Button.h"
#include "background/MovingSpriteActor.h"
#include "background/BackgroundLayer.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/WaitStage.h"
#include "Enemy/Hexagon.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"

namespace ly
{
    LevelOne::LevelOne(Application* owningApp)
        : World{owningApp},
          mPlayerSpaceship{},
          mGameplayHUD{}
    {
    }

    void LevelOne::BeginPlay()
    {
        SpawnCosmetics();
        SetupPlayer();
        // HUD
        mGameplayHUD = SpawnActor<GameplayHUD>();
        if (!mGameplayHUD.expired())
        {
            mGameplayHUD.lock()->onQuitBtnClicked.BindAction(GetWeakRef(), &LevelOne::QuitGame);
            mGameplayHUD.lock()->onRestartBtnClicked.BindAction(GetWeakRef(), &LevelOne::Restart);
        }
    }

    void LevelOne::Tick(float deltaTime)
    {
        (void)deltaTime;
        CheckRespawn();
    }

    void LevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
        
        AddStage(shared<WaitStage>{new WaitStage{this, 10.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        AddStage(shared<WaitStage>{new WaitStage{this, 8.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{this, 8.f}});
        AddStage(shared<UFOStage>{new UFOStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{this, 8.f}});
        AddStage(shared<ChaosStage>{new ChaosStage{ this }});

        AddStage(shared<WaitStage>{new WaitStage{this, 8.f}});
        AddStage(shared<BossStage>{new BossStage{ this }});
    }

    void LevelOne::SpawnCosmetics()
    {
        // Backdrop
        auto win = GetWindowSize();
        weak<Actor> backdrop = SpawnActor<Actor>("Backgrounds/darkPurple.png");
        if (!backdrop.expired())
        {
            backdrop.lock()->SetActorLocation(sf::Vector2f(win.x / 2.f, win.y / 2.f));
        }

        // Planets layer
        {
            std::vector<std::string> planets = {
                "PNG/Planets/Planet1.png","PNG/Planets/Planet2.png","PNG/Planets/Planet3.png",
                "PNG/Planets/Planet4.png","PNG/Planets/Planet5.png","PNG/Planets/Planet6.png","PNG/Planets/Planet7.png"
            };
            auto layer = SpawnActor<BackgroundLayer>();
            if (!layer.expired())
            {
                layer.lock()->SetAssets(planets);
                layer.lock()->SetSpriteCount(1);
                layer.lock()->SetSizes(1.f, 1.5f);
                layer.lock()->SetVelocities({0.f, 20.f}, {0.f, 40.f});
            }
        }
        // Meteors layer
        {
            std::vector<std::string> meteors = {
                "PNG/Meteors/meteorGrey_tiny1.png","PNG/Meteors/meteorGrey_tiny2.png",
                "PNG/Meteors/meteorBrown_big1.png","PNG/Meteors/meteorBrown_big2.png","PNG/Meteors/meteorBrown_big3.png","PNG/Meteors/meteorBrown_big4.png",
                "PNG/Meteors/meteorBrown_med1.png","PNG/Meteors/meteorBrown_med3.png","PNG/Meteors/meteorBrown_small1.png","PNG/Meteors/meteorBrown_small2.png",
                "PNG/Meteors/meteorBrown_tiny1.png","PNG/Meteors/meteorBrown_tiny2.png","PNG/Meteors/meteorGrey_big1.png","PNG/Meteors/meteorGrey_big2.png",
                "PNG/Meteors/meteorGrey_big3.png","PNG/Meteors/meteorGrey_big4.png","PNG/Meteors/meteorGrey_med1.png","PNG/Meteors/meteorGrey_med2.png",
                "PNG/Meteors/meteorGrey_small1.png","PNG/Meteors/meteorGrey_small2.png"
            };
            auto layer = SpawnActor<BackgroundLayer>();
            if (!layer.expired())
            {
                layer.lock()->SetAssets(meteors);
                layer.lock()->SetSpriteCount(20);
                layer.lock()->SetSizes(0.2f, 0.5f);
                layer.lock()->SetVelocities({0.f, 50.f}, {0.f, 120.f});
            }
        }
    }

    void LevelOne::SetupPlayer()
    {
        Player* player = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = PlayerManager::Get().SpawnSpaceship(this);
        if (mGameplayHUD.expired())
        {
            // will be set in BeginPlay after spawn
        }
        // init HUD values
        if (player)
        {
            if (!mGameplayHUD.expired())
            {
                mGameplayHUD.lock()->SetLives(player->GetLifeCount());
                mGameplayHUD.lock()->SetScore(player->GetScore());
            }
        }
    }

    void LevelOne::CheckRespawn()
    {
        if (mPlayerSpaceship.expired())
        {
            // current ship destroyed -> decrement life and respawn if any
            Player* player = PlayerManager::Get().GetPlayer();
            if (!player) return;
            if (player->GetLifeCount() > 0)
            {
                PlayerManager::Get().HandleSpaceshipDestroyed(this);
                mPlayerSpaceship = player->GetCurrentSpaceship();
            }
            else
            {
                GameOver();
            }
        }
    }

    void LevelOne::GameOver()
    {
        if (!mGameplayHUD.expired())
        {
            mGameplayHUD.lock()->SetGameOver(false);
        }
    }

    void LevelOne::AllGameStageFinished()
    {
        if (!mGameplayHUD.expired())
        {
            mGameplayHUD.lock()->SetGameOver(true);
        }
    }

    void LevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }

    void LevelOne::Restart()
    {
        PlayerManager::Get().Reset();
        GetApplication()->QueueWorld<LevelOne>();
    }
}
