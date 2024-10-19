#include <SFML/Graphics.hpp>
#include <memory>
#include "framework/Application.h" 

int main()
{
    //Heap Alocation
    // ly::Application* app = new ly::Application();
    std::unique_ptr<ly::Application> app = std::make_unique<ly::Application>();
    app->Run();
}