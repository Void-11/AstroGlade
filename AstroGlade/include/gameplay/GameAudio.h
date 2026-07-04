#pragma once

namespace ly
{
	class Shooter;
	class Spaceship;
	enum class RewardAudioType;

	class GameAudio
	{
	public:
		static void PlayMenuMusic();
		static void PlayGameplayMusic();
		static void PlayBossMusic();
		static void PauseMusic();
		static void ResumeMusic();
		static void StopMusic();

		static void PlayPlayerShoot(const Shooter& shooter);
		static void PlayEnemyShoot();
		static void PlayBossShoot();
		static void PlayLaserCancel();
		static void PlayShipHit(const Spaceship& spaceship);
		static void PlayShipDeath(const Spaceship& spaceship);
		static void PlayRewardPickup(RewardAudioType audioType);
		static void PlayUIButton();
		static void PlayPauseToggle();
		static void PlayStageClear();
		static void PlayWin();
		static void PlayGameOver();
	};
}
