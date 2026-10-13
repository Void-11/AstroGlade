#include <algorithm>

#include "framework/AssetManager.h"
#include "framework/AudioManager.h"
#include "framework/Log.h"

namespace ly
{
	namespace
	{
		float ClampVolume(float volume)
		{
			return std::clamp(volume, 0.f, 100.f);
		}

		std::string ResolveAssetPath(const std::string& path)
		{
			return AssetManager::Get().ResolveAssetPath(path);
		}
	}

	AudioManager& AudioManager::Get()
	{
		static AudioManager audioManager;
		return audioManager;
	}

	void AudioManager::PlaySound(const std::string& path, float volume, float pitch, float cooldown)
	{
		if (cooldown > 0.f && IsSoundOnCooldown(path, cooldown))
		{
			return;
		}

		const shared<sf::SoundBuffer> buffer = LoadSoundBuffer(path);
		if (!buffer)
		{
			return;
		}

		CleanCycle();

		const unique<sf::Sound>& sound = mActiveSounds.emplace_back(std::make_unique<sf::Sound>(*buffer));
		sound->setVolume(ClampVolume(volume));
		sound->setPitch(pitch);
		sound->play();

		if (cooldown > 0.f)
		{
			mSoundCooldownClocks[path].restart();
		}
	}

	void AudioManager::PlayMusic(const std::string& path, float volume, bool loop)
	{
		if (mCurrentMusicPath == path && mMusic.getStatus() != sf::SoundSource::Stopped)
		{
			mMusic.setVolume(ClampVolume(volume));
			mMusic.setLoop(loop);
			if (mMusic.getStatus() == sf::SoundSource::Paused)
			{
				mMusic.play();
			}
			return;
		}

		StopMusic();
		if (!mMusic.openFromFile(ResolveAssetPath(path)))
		{
			LogError("Failed to load music: ", path);
			return;
		}

		mCurrentMusicPath = path;
		mMusic.setVolume(ClampVolume(volume));
		mMusic.setLoop(loop);
		mMusic.play();
	}

	void AudioManager::PauseMusic()
	{
		if (mMusic.getStatus() == sf::SoundSource::Playing)
		{
			mMusic.pause();
		}
	}

	void AudioManager::ResumeMusic()
	{
		if (mMusic.getStatus() == sf::SoundSource::Paused)
		{
			mMusic.play();
		}
	}

	void AudioManager::StopMusic()
	{
		mMusic.stop();
		mCurrentMusicPath.clear();
	}

	void AudioManager::SetMusicVolume(float volume)
	{
		mMusic.setVolume(ClampVolume(volume));
	}

	void AudioManager::CleanCycle()
	{
		const auto finished = [](const unique<sf::Sound>& sound)
		{
			return !sound || sound->getStatus() == sf::SoundSource::Stopped;
		};
		mActiveSounds.erase(std::remove_if(mActiveSounds.begin(), mActiveSounds.end(), finished), mActiveSounds.end());
	}

	shared<sf::SoundBuffer> AudioManager::LoadSoundBuffer(const std::string& path)
	{
		if (const auto found = mLoadedSoundBuffers.find(path); found != mLoadedSoundBuffers.end())
		{
			return found->second;
		}

		auto buffer = std::make_shared<sf::SoundBuffer>();
		if (!buffer->loadFromFile(ResolveAssetPath(path)))
		{
			LogError("Failed to load sound: ", path);
			return nullptr;
		}

		mLoadedSoundBuffers.try_emplace(path, buffer);
		return buffer;
	}

	bool AudioManager::IsSoundOnCooldown(const std::string& path, float cooldown) const
	{
		if (const auto found = mSoundCooldownClocks.find(path); found != mSoundCooldownClocks.end())
		{
			return found->second.getElapsedTime().asSeconds() < cooldown;
		}

		return false;
	}
}
