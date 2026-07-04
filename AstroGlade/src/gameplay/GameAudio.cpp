#include "gameplay/GameAudio.h"

#include "Enemy/Boss.h"
#include "Enemy/EnemySpaceship.h"
#include "framework/AudioManager.h"
#include "player/PlayerSpaceship.h"
#include "player/Reward.h"
#include "spaceship/Spaceship.h"
#include "weapon/FrontalWiper.h"
#include "weapon/LaserShooter.h"
#include "weapon/Shooter.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	namespace
	{
		const char* const kMenuMusic = "Audio/Music/menu_claimed_by_the_void_loop.mp3";
		const char* const kGameplayMusic = "Audio/Music/gameplay_specular_city.mp3";
		const char* const kBossMusic = "Audio/Music/boss_brute_force_loop.mp3";

		const char* const kPlayerLaser = "Audio/SFX/KenneySciFi/laserSmall_000.ogg";
		const char* const kPlayerThreeWay = "Audio/SFX/KenneySciFi/laserRetro_001.ogg";
		const char* const kPlayerFrontalWiper = "Audio/SFX/KenneySciFi/laserLarge_001.ogg";
		const char* const kEnemyLaser = "Audio/SFX/KenneySciFi/laserSmall_003.ogg";
		const char* const kBossLaser = "Audio/SFX/KenneySciFi/laserLarge_004.ogg";
		const char* const kEnemyHit = "Audio/SFX/KenneySciFi/impactMetal_000.ogg";
		const char* const kEnemyDeath = "Audio/SFX/KenneySciFi/explosionCrunch_001.ogg";
		const char* const kBossDeath = "Audio/SFX/KenneySciFi/lowFrequency_explosion_000.ogg";

		const char* const kZap = "SpaceShooterRedux/Bonus/sfx_zap.ogg";
		const char* const kShieldUp = "SpaceShooterRedux/Bonus/sfx_shieldUp.ogg";
		const char* const kShieldDown = "SpaceShooterRedux/Bonus/sfx_shieldDown.ogg";
		const char* const kTwoTone = "SpaceShooterRedux/Bonus/sfx_twoTone.ogg";
		const char* const kLose = "SpaceShooterRedux/Bonus/sfx_lose.ogg";

		void PlaySound(const char* path, float volume, float pitch = 1.f, float cooldown = 0.f)
		{
			AudioManager::Get().PlaySound(path, volume, pitch, cooldown);
		}
	}

	void GameAudio::PlayMenuMusic()
	{
		AudioManager::Get().PlayMusic(kMenuMusic, 32.f, true);
	}

	void GameAudio::PlayGameplayMusic()
	{
		AudioManager::Get().PlayMusic(kGameplayMusic, 34.f, true);
	}

	void GameAudio::PlayBossMusic()
	{
		AudioManager::Get().PlayMusic(kBossMusic, 36.f, true);
	}

	void GameAudio::PauseMusic()
	{
		AudioManager::Get().PauseMusic();
	}

	void GameAudio::ResumeMusic()
	{
		AudioManager::Get().ResumeMusic();
	}

	void GameAudio::StopMusic()
	{
		AudioManager::Get().StopMusic();
	}

	void GameAudio::PlayPlayerShoot(const Shooter& shooter)
	{
		if (dynamic_cast<const FrontalWiper*>(&shooter))
		{
			PlaySound(kPlayerFrontalWiper, 42.f);
		}
		else if (dynamic_cast<const ThreeWayShooter*>(&shooter))
		{
			PlaySound(kPlayerThreeWay, 42.f);
		}
		else
		{
			PlaySound(kPlayerLaser, 45.f);
		}
	}

	void GameAudio::PlayEnemyShoot()
	{
		PlaySound(kEnemyLaser, 22.f, 1.f, 0.04f);
	}

	void GameAudio::PlayBossShoot()
	{
		PlaySound(kBossLaser, 28.f, 0.95f, 0.08f);
	}

	void GameAudio::PlayLaserCancel()
	{
		PlaySound(kZap, 25.f, 1.1f, 0.05f);
	}

	void GameAudio::PlayShipHit(const Spaceship& spaceship)
	{
		if (dynamic_cast<const PlayerSpaceship*>(&spaceship))
		{
			PlaySound(kShieldDown, 35.f, 1.f, 0.12f);
		}
		else if (dynamic_cast<const Boss*>(&spaceship))
		{
			PlaySound(kEnemyHit, 22.f, 0.8f, 0.08f);
		}
		else
		{
			PlaySound(kEnemyHit, 18.f, 1.f, 0.05f);
		}
	}

	void GameAudio::PlayShipDeath(const Spaceship& spaceship)
	{
		if (dynamic_cast<const Boss*>(&spaceship))
		{
			PlaySound(kBossDeath, 60.f);
		}
		else if (dynamic_cast<const PlayerSpaceship*>(&spaceship))
		{
			PlaySound(kShieldDown, 45.f, 0.85f);
		}
		else if (dynamic_cast<const EnemySpaceship*>(&spaceship))
		{
			PlaySound(kEnemyDeath, 38.f);
		}
	}

	void GameAudio::PlayRewardPickup(RewardAudioType audioType)
	{
		switch (audioType)
		{
		case RewardAudioType::Health:
			PlaySound(kShieldUp, 40.f);
			break;
		case RewardAudioType::Weapon:
			PlaySound(kTwoTone, 38.f);
			break;
		case RewardAudioType::Life:
			PlaySound(kShieldUp, 45.f, 1.2f);
			break;
		case RewardAudioType::ScoreMultiplier:
			PlaySound(kTwoTone, 40.f, 1.25f);
			break;
		default:
			PlaySound(kTwoTone, 35.f);
			break;
		}
	}

	void GameAudio::PlayUIButton()
	{
		PlaySound(kTwoTone, 35.f, 1.f, 0.06f);
	}

	void GameAudio::PlayPauseToggle()
	{
		PlaySound(kZap, 20.f, 0.9f, 0.08f);
	}

	void GameAudio::PlayStageClear()
	{
		PlaySound(kTwoTone, 45.f, 1.1f);
	}

	void GameAudio::PlayWin()
	{
		PlaySound(kTwoTone, 55.f, 1.3f);
	}

	void GameAudio::PlayGameOver()
	{
		PlaySound(kLose, 55.f);
	}
}
