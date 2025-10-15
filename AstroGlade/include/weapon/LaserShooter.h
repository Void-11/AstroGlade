#pragma once
#include "weapon/Shooter.h"
#include "SFML/System.hpp"

namespace ly
{
    class LaserShooter : public Shooter
    {
    public:

        LaserShooter(Actor* owner, float cooldownTime = 1.f, const sf::Vector2f& localPositionOffset = {0.f, 0.f}, float localRotationOffset = 0.f, const std::string& texturePath = "PNG/Lasers/laserRed01.png");
        virtual bool IsOnCoolDown() const override;
        void SetTexturePath(const std::string& path) { mTexturePath = path; }

    private:

        sf::Clock mCooldownClock;
        float mCooldownTime;
        sf::Vector2f mLocalPositionOffset;
        float mLocalRotationOffset;
        std::string mTexturePath;
        
        virtual void ShootExecution() override;
    };
}
