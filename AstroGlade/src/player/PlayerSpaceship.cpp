#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "gameplay/GameAudio.h"
#include "weapon/LaserShooter.h"
#include "framework/World.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{owningWorld, path},
		mMoveInput{},
		mSpeed{200.f, 200.f},
		mBoostSpeedMultiplier{1.6f},
		mShooter{ new LaserShooter{this, .35f, {50.f, 0.f}} },
		mInvulnerableTime{2.f},
		mInvulnerable{true},
	mInvulnerableFlashInterval{0.5f},
		mInvulnerableFlashTimer{0.f},
		mInvulnerableFlashDir{1}
	{
		SetTeamID(1);

		sf::Vector2u windowSize = owningWorld->GetWindowSize();
		float scaleX = windowSize.x / 600.f;
		float scaleY = windowSize.y / 980.f;
		mSpeed.x *= scaleX;
		mSpeed.y *= scaleY;
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		HandleInput();
		ConsumeInput(deltaTime);
		Spaceship::Tick(deltaTime);
		UpdateInvulnerable(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter && mShooter->Shoot())
		{
			GameAudio::PlayPlayerShoot(*mShooter);
		}
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newsShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newsShooter.get()))
		{
			mShooter->IncrementLevel();
			return;
		}

		mShooter = std::move(newsShooter);
	}

	void PlayerSpaceship::ApplyDefaultWeapon(int weaponLevel)
	{
		mShooter = unique<Shooter>{new LaserShooter{this, .35f, {50.f, 0.f}}};
		mShooter->SetCurrentLevel(weaponLevel);
	}

	void PlayerSpaceship::ApplyDefaultWeaponLevelIfUsingLaser(int weaponLevel)
	{
		LaserShooter* laserShooter = dynamic_cast<LaserShooter*>(mShooter.get());
		if (laserShooter)
		{
			laserShooter->SetCurrentLevel(weaponLevel);
		}
	}

	void PlayerSpaceship::ApplyDamage(float amt)
	{
		if (!mInvulnerable)
		{
			Spaceship::ApplyDamage(amt);
		}
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, mInvulnerableTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mMoveInput.y = 1.f;
		}
		 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mMoveInput.x = 1.f;
		}

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}
	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		sf::FloatRect actorBounds = GetActorGlobalBounds();
		float halfWidth = actorBounds.width / 2.f;
		float halfHeight = actorBounds.height / 2.f;

		if (actorLocation.x - halfWidth <= 0.f && mMoveInput.x < 0.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.x + halfWidth >= GetWindowSize().x && mMoveInput.x > 0.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y - halfHeight <= 0.f && mMoveInput.y < 0.f)
		{
			mMoveInput.y = 0.f;
		}

		if (actorLocation.y + halfHeight >= GetWindowSize().y && mMoveInput.y > 0.f)
		{
			mMoveInput.y = 0.f;
		}
	}
	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		float boostSpeedMultiplier = IsBoosting() ? mBoostSpeedMultiplier : 1.f;
		SetVelocity({mMoveInput.x * mSpeed.x * boostSpeedMultiplier, mMoveInput.y * mSpeed.y * boostSpeedMultiplier});
		mMoveInput.x = mMoveInput.y = 0.f;
	}

	bool PlayerSpaceship::IsBoosting() const
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({255,255,255,255});
		mInvulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
	{
		if (!mInvulnerable) return;
		
	mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDir;
		if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
		{
			mInvulnerableFlashDir *= -1;
		}

		GetSprite().setColor(LerpColor({255,255, 255, 64} ,{255, 255, 255, 128}, mInvulnerableFlashTimer/mInvulnerableFlashInterval));
	}
}
