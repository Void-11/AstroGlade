#include "levels/MainMenu.h"
#include "widgets/Button.h"
#include "framework/Application.h"
#include "levels/LevelOne.h"

namespace ly
{
    MainMenu::MainMenu(Application* app) : World{app}
    {
    }

    void MainMenu::BeginPlay()
    {
        auto play = SpawnActor<Button>("Play");
        if (!play.expired())
        {
            play.lock()->SetWidgetLocation({ 420.f, 260.f });
            play.lock()->onButtonClicked.BindAction(GetWeakRef(), &MainMenu::OnPlay);
        }
        auto quit = SpawnActor<Button>("Quit");
        if (!quit.expired())
        {
            quit.lock()->SetWidgetLocation({ 420.f, 320.f });
            quit.lock()->onButtonClicked.BindAction(GetWeakRef(), &MainMenu::OnQuit);
        }
    }

    void MainMenu::OnPlay()
    {
        GetApplication()->QueueWorld<LevelOne>();
    }

    void MainMenu::OnQuit()
    {
        GetApplication()->QuitApplication();
    }
}