#include <typeinfo>
#include <utility>

#include <SFML/System.hpp>

#include "framework/MathUtility.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "gameplay/ResolutionScale.h"
#include "player/PlayerSpaceship.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mSpeed{ ScaleToResolution({ 200.f, 200.f }, owningWorld->GetWindowSize()) },
		mShooter{ CreateDefaultShooter() }
	{
		SetTeamID(1);
	}

	// Defined here, where Shooter is a complete type, so unique<Shooter> can be destroyed.
	PlayerSpaceship::~PlayerSpaceship() = default;

	void PlayerSpaceship::Tick(float deltaTime)
	{
		HandleInput();
		ConsumeInput();
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

	void PlayerSpaceship::SetShooter(unique<Shooter> newShooter)
	{
		if (!newShooter)
		{
			return;
		}

		if (mShooter)
		{
			const Shooter& currentShooter = *mShooter;
			const Shooter& offeredShooter = *newShooter;
			if (typeid(currentShooter) == typeid(offeredShooter))
			{
				mShooter->IncrementLevel();
				return;
			}
		}

		mShooter = std::move(newShooter);
	}

	void PlayerSpaceship::ApplyDefaultWeapon(int weaponLevel)
	{
		mShooter = CreateDefaultShooter();
		mShooter->SetCurrentLevel(weaponLevel);
	}

	void PlayerSpaceship::ApplyDefaultWeaponLevelIfUsingLaser(int weaponLevel)
	{
		if (auto* const laserShooter = dynamic_cast<LaserShooter*>(mShooter.get()))
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

	unique<Shooter> PlayerSpaceship::CreateDefaultShooter()
	{
		return std::make_unique<LaserShooter>(this, 0.35f, sf::Vector2f{ 50.f, 0.f });
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
		const sf::Vector2f actorLocation = GetActorLocation();
		const sf::FloatRect actorBounds = GetActorGlobalBounds();
		const float halfWidth = actorBounds.width / 2.f;
		const float halfHeight = actorBounds.height / 2.f;
		const sf::Vector2u windowSize = GetWindowSize();

		if (actorLocation.x - halfWidth <= 0.f && mMoveInput.x < 0.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.x + halfWidth >= static_cast<float>(windowSize.x) && mMoveInput.x > 0.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y - halfHeight <= 0.f && mMoveInput.y < 0.f)
		{
			mMoveInput.y = 0.f;
		}

		if (actorLocation.y + halfHeight >= static_cast<float>(windowSize.y) && mMoveInput.y > 0.f)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceship::ConsumeInput()
	{
		const float boostSpeedMultiplier = IsBoosting() ? mBoostSpeedMultiplier : 1.f;
		SetVelocity({ mMoveInput.x * mSpeed.x * boostSpeedMultiplier, mMoveInput.y * mSpeed.y * boostSpeedMultiplier });
		mMoveInput = sf::Vector2f{};
	}

	bool PlayerSpaceship::IsBoosting() const
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor(sf::Color::White);
		mInvulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
	{
		if (!mInvulnerable) return;

		mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDir;
		if (mInvulnerableFlashTimer < 0.f || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
		{
			mInvulnerableFlashDir = -mInvulnerableFlashDir;
		}

		GetSprite().setColor(LerpColor({ 255, 255, 255, 64 }, { 255, 255, 255, 128 }, mInvulnerableFlashTimer / mInvulnerableFlashInterval));
	}
}
