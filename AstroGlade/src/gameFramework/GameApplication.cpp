#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

ly::Application *GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        :Application{980,600,"Astro Glade", sf::Style::Titlebar | sf::Style::Close}
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
        actorToDestroy.lock()->SetTexture(GetResourceDir() +  "PNG/playerShip2_red.png");
        actorToDestroy.lock()->SetActorLocation(sf::Vector2f(300.f,490.f));
        actorToDestroy.lock()->SetActorRotation(0.f);
        counter = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        // counter += deltaTime;
        // if(counter > 2.f)
        // {
        //     if(!actorToDestroy.expired())
        //     {
        //         actorToDestroy.lock()->Destroy();
        //     }
        // }
    }
}
