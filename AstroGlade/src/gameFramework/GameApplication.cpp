#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"
#include "enemy/Vanguard.h"

ly::Application *GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    class Vangaurd;

    GameApplication::GameApplication()
        :Application{980,600,"Astro Glade", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
        weak<World> newWorld = LoadWorld<World>();
        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f,490.f));
        testPlayerSpaceship.lock()->SetActorRotation(0.f);

        weak<Vangaurd> testSpaceship = newWorld.lock()->SpawnActor<Vangaurd>();
        testSpaceship.lock()->SetActorLocation(sf::Vector2f{100.f, 50.f});
        counter = 0.f;
    }

    void GameApplication::Tick(float deltaTime)
    {
        counter += deltaTime;
        // if(counter > 10.f)
        // {
        //     if(!testPlayerSpaceship.expired())
        //     {
        //         testPlayerSpaceship.lock()->Destroy();
        //     }
        // }
    }
}
