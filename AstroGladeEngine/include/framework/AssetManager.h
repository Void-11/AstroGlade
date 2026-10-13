#ifndef ASTROGLADE_ENGINE_FRAMEWORK_ASSETMANAGER_H
#define ASTROGLADE_ENGINE_FRAMEWORK_ASSETMANAGER_H

#include <filesystem>
#include <string>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	// Process-wide cache of textures and fonts, loaded relative to the asset root directory.
	// Assets that nothing else references any more are released by CleanCycle().
	class AssetManager
	{
	public:
		[[nodiscard]] static AssetManager& Get();

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		[[nodiscard]] shared<sf::Texture> LoadTexture(const std::string& path);
		[[nodiscard]] shared<sf::Font> LoadFont(const std::string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const std::filesystem::path& directory);
		[[nodiscard]] std::string ResolveAssetPath(const std::string& relativePath) const;
	private:
		AssetManager() = default;

		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
		std::filesystem::path mRootDirectory;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_ASSETMANAGER_H
