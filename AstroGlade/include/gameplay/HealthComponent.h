#pragma once
#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:

        HealthComponent(float health, float maxHealth);
        void ModifyHealth(float amount);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const { return mMaxHealth; }

        Delegate<float,float,float> onHealthModified;

    private:

        float mHealth;
        float mMaxHealth;

        void TakenDamage(float amount);
        void HealthEmpty();
        void HealthRegenerate(float amount);
    };
}
