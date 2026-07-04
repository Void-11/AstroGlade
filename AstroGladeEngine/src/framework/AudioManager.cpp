#include <algorithm>

#include "framework/AssetManager.h"
#include "framework/AudioManager.h"

namespace ly
{
	unique<AudioManager> AudioManager::audioManager{ nullptr };

	AudioManager& AudioManager::Get()
	{
		if (!audioManager)
		{
			audioManager = unique<AudioManager>{ new AudioManager };
		}

		return *audioManager;
	}

	void AudioManager::PlaySound(const std::string& path, float volume, float pitch, float cooldown)
	{
		if (cooldown > 0.f && IsSoundOnCooldown(path, cooldown))
		{
			return;
		}

		shared<sf::SoundBuffer> buffer = LoadSoundBuffer(path);
		if (!buffer)
		{
			return;
		}

		CleanCycle();

		unique<sf::Sound> sound{ new sf::Sound };
		sound->setBuffer(*buffer);
		sound->setVolume(ClampVolume(volume));
		sound->setPitch(pitch);
		sound->play();
		mActiveSounds.push_back(std::move(sound));

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
			LOG("Failed to load music: %s", path.c_str());
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
		for (auto iter = mActiveSounds.begin(); iter != mActiveSounds.end();)
		{
			if (!(*iter) || (*iter)->getStatus() == sf::SoundSource::Stopped)
			{
				iter = mActiveSounds.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	AudioManager::AudioManager()
		: mLoadedSoundBuffers{},
		mActiveSounds{},
		mSoundCooldownClocks{},
		mMusic{},
		mCurrentMusicPath{}
	{
	}

	shared<sf::SoundBuffer> AudioManager::LoadSoundBuffer(const std::string& path)
	{
		auto found = mLoadedSoundBuffers.find(path);
		if (found != mLoadedSoundBuffers.end())
		{
			return found->second;
		}

		shared<sf::SoundBuffer> buffer{ new sf::SoundBuffer };
		if (!buffer->loadFromFile(ResolveAssetPath(path)))
		{
			LOG("Failed to load sound: %s", path.c_str());
			return shared<sf::SoundBuffer>{ nullptr };
		}

		mLoadedSoundBuffers.insert({ path, buffer });
		return buffer;
	}

	std::string AudioManager::ResolveAssetPath(const std::string& path) const
	{
		return AssetManager::Get().GetAssetRootDirectory() + path;
	}

	float AudioManager::ClampVolume(float volume) const
	{
		return std::max(0.f, std::min(volume, 100.f));
	}

	bool AudioManager::IsSoundOnCooldown(const std::string& path, float cooldown) const
	{
		auto found = mSoundCooldownClocks.find(path);
		if (found == mSoundCooldownClocks.end())
		{
			return false;
		}

		return found->second.getElapsedTime().asSeconds() < cooldown;
	}
}
