#ifndef ASTROGLADE_GAME_GAMEPLAY_GAMEAUDIO_H
#define ASTROGLADE_GAME_GAMEPLAY_GAMEAUDIO_H

namespace ly
{
	class Shooter;
	class Spaceship;
	enum class RewardAudioType;

	// The game's music and sound effect cues, with their mixing levels, in one place.
	namespace GameAudio
	{
		void PlayMenuMusic();
		void PlayGameplayMusic();
		void PlayBossMusic();
		void PauseMusic();
		void ResumeMusic();
		void StopMusic();

		void PlayPlayerShoot(const Shooter& shooter);
		void PlayEnemyShoot();
		void PlayBossShoot();
		void PlayLaserCancel();
		void PlayShipHit(const Spaceship& spaceship);
		void PlayShipDeath(const Spaceship& spaceship);
		void PlayRewardPickup(RewardAudioType audioType);
		void PlayUIButton();
		void PlayPauseToggle();
		void PlayStageClear();
		void PlayWin();
		void PlayGameOver();
	}
}

#endif // ASTROGLADE_GAME_GAMEPLAY_GAMEAUDIO_H
