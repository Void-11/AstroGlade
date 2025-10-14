#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class AssetManager
    {
    public:

        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& path);
        shared<sf::Font> LoadFont(const std::string& path);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);
        
    protected:
        
        AssetManager();

    private:

        static unique<AssetManager> assetManager;
        dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
        std::string mRootDirectory;
    };
}
