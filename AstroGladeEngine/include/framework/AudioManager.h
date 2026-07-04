#pragma once

#include <SFML/Audio.hpp>
#include <string>

#include "framework/Core.h"

namespace ly
{
	class AudioManager
	{
	public:
		static AudioManager& Get();

		void PlaySound(const std::string& path, float volume = 100.f, float pitch = 1.f, float cooldown = 0.f);
		void PlayMusic(const std::string& path, float volume = 100.f, bool loop = true);
		void PauseMusic();
		void ResumeMusic();
		void StopMusic();
		void SetMusicVolume(float volume);
		void CleanCycle();

	private:
		AudioManager();

		shared<sf::SoundBuffer> LoadSoundBuffer(const std::string& path);
		std::string ResolveAssetPath(const std::string& path) const;
		float ClampVolume(float volume) const;
		bool IsSoundOnCooldown(const std::string& path, float cooldown) const;

		static unique<AudioManager> audioManager;
		Dictionary<std::string, shared<sf::SoundBuffer>> mLoadedSoundBuffers;
		List<unique<sf::Sound>> mActiveSounds;
		Dictionary<std::string, sf::Clock> mSoundCooldownClocks;
		sf::Music mMusic;
		std::string mCurrentMusicPath;
	};
}
