#include "levels/LevelOne.h"
#include "Enemy/Vanguard.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "gameplay/GameStage.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application* owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
        testPlayerSpaceship.lock()->SetActorRotation(0.f);

        weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
        testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
    }

    void GameLevelOne::BeginPlay()
    {
        
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
    }
}
