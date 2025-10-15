#include "enemy/Boss.h"
#include "framework/MathUtility.h"
#include "weapon/LaserShooter.h"

namespace ly
{
    Boss::Boss(World* world, const std::string& texturePath)
        : EnemySpaceship{world, texturePath, 300.f}, mTime{0.f}
    {
        // Spawn near top-center facing downwards
        SetActorLocation({ 480.f, 120.f });
        SetActorRotation(90.f);
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        mTime += deltaTime;
        // slow drift left-right
        float x = 480.f + std::sin(mTime) * 200.f;
        SetActorLocation({ x, GetActorLocation().y });
        if (std::fmod(mTime, 1.0f) < 0.02f)
        {
            Shoot();
        }
    }

    void Boss::Shoot()
    {
        // radial 8-way lasers
        for (int i = 0; i < 8; ++i)
        {
            float angle = i * 45.f;
            sf::Vector2f dir = RotationToVector(angle);
            auto shooter = std::make_unique<LaserShooter>(this, 0.1f, sf::Vector2f{0.f, 0.f}, angle, "PNG/Lasers/laserRed10.png");
            shooter->Shoot();
        }
    }
}