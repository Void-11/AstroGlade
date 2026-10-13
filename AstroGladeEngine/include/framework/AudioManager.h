#ifndef ASTROGLADE_ENGINE_FRAMEWORK_AUDIOMANAGER_H
#define ASTROGLADE_ENGINE_FRAMEWORK_AUDIOMANAGER_H

#include <string>

#include <SFML/Audio.hpp>

#include "framework/Core.h"

namespace ly
{
	class AudioManager
	{
	public:
		[[nodiscard]] static AudioManager& Get();

		AudioManager(const AudioManager&) = delete;
		AudioManager& operator=(const AudioManager&) = delete;

		void PlaySound(const std::string& path, float volume = 100.f, float pitch = 1.f, float cooldown = 0.f);
		void PlayMusic(const std::string& path, float volume = 100.f, bool loop = true);
		void PauseMusic();
		void ResumeMusic();
		void StopMusic();
		void SetMusicVolume(float volume);
		void CleanCycle();

	private:
		AudioManager() = default;

		[[nodiscard]] shared<sf::SoundBuffer> LoadSoundBuffer(const std::string& path);
		[[nodiscard]] bool IsSoundOnCooldown(const std::string& path, float cooldown) const;

		Dictionary<std::string, shared<sf::SoundBuffer>> mLoadedSoundBuffers;
		List<unique<sf::Sound>> mActiveSounds;
		Dictionary<std::string, sf::Clock> mSoundCooldownClocks;
		sf::Music mMusic;
		std::string mCurrentMusicPath;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_AUDIOMANAGER_H
