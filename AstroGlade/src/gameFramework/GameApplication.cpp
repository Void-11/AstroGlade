#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "config.h"
#include "enemy/Vanguard.h"
#include "levels/LevelOne.h"

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
        weak<LevelOne> newWorld = LoadWorld<LevelOne>();
    }
}
