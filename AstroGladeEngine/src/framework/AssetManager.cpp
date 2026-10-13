#include <system_error>

#include "framework/AssetManager.h"
#include "framework/Log.h"

namespace ly
{
	namespace
	{
		template<typename T>
		shared<T> LoadAsset(const std::string& path, const std::string& resolvedPath, Dictionary<std::string, shared<T>>& container)
		{
			if (path.empty())
			{
				return nullptr;
			}

			if (const auto found = container.find(path); found != container.end())
			{
				return found->second;
			}

			auto newAsset = std::make_shared<T>();
			if (!newAsset->loadFromFile(resolvedPath))
			{
				return nullptr;
			}

			container.try_emplace(path, newAsset);
			return newAsset;
		}

		// Releases every cached asset that is referenced only by the cache itself.
		template<typename T>
		void CleanUniqueRef(Dictionary<std::string, shared<T>>& container)
		{
			for (auto iter = container.begin(); iter != container.end();)
			{
				if (iter->second.use_count() == 1)
				{
					LogDebug("Unloaded unused asset: ", iter->first);
					iter = container.erase(iter);
				}
				else
				{
					++iter;
				}
			}
		}
	}

	AssetManager& AssetManager::Get()
	{
		static AssetManager assetManager;
		return assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return LoadAsset(path, ResolveAssetPath(path), mLoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset(path, ResolveAssetPath(path), mLoadedFontMap);
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueRef(mLoadedFontMap);
		CleanUniqueRef(mLoadedTextureMap);
	}

	void AssetManager::SetAssetRootDirectory(const std::filesystem::path& directory)
	{
		mRootDirectory = directory;

		std::error_code error;
		if (!std::filesystem::is_directory(mRootDirectory, error))
		{
			LogError("Asset root directory not found: ", mRootDirectory.string());
		}
	}

	std::string AssetManager::ResolveAssetPath(const std::string& relativePath) const
	{
		return (mRootDirectory / relativePath).string();
	}
}
