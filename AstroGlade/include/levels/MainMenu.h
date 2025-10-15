#pragma once
#include "framework/World.h"

namespace ly
{
    class MainMenu : public World
    {
    public:
        MainMenu(Application* app);
    private:
        virtual void BeginPlay() override;
        void OnPlay();
        void OnQuit();
    };
}