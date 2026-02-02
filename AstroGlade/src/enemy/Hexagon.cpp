#include "Enemy/Hexagon.h"
#include "weapon/LaserShooter.h"
#include "framework/World.h"
namespace ly
{
	Hexagon::Hexagon(World* owingWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{owingWorld, texturePath},
		mShooter1{ new LaserShooter{this, 1.f, sf::Vector2f{20.f, 50.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter2{ new LaserShooter{this, 1.f, sf::Vector2f{20.f, -50.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter3{ new LaserShooter{this, 1.f, sf::Vector2f{50.f, 0.0f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter4{ new LaserShooter{this, 1.f, sf::Vector2f{-50.f, 0.0f}, -180.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		mShooter5{ new LaserShooter{this, 1.f, sf::Vector2f{-20.f, 50.0f}, 120.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		        mShooter6{ new LaserShooter{this, 2.5f, {-50.f, -20.f}, 130.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
		    {
		        sf::Vector2u windowSize = owingWorld->GetWindowSize();
		        float scaleX = windowSize.x / 600.f;
		        float scaleY = windowSize.y / 980.f;
		        SetVelocity({velocity.x * scaleX, velocity.y * scaleY});
		        SetActorRotation(90.f);
		    }	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
	void Hexagon::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
		mShooter4->Shoot();
		mShooter5->Shoot();
		mShooter6->Shoot();
	}
}