#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
    HealthComponent::HealthComponent(float health, float maxHealth)
        :mHealth{health},
        mMaxHealth{maxHealth}
    {
        
    }

    void HealthComponent::ModifyHealth(float amount)
    {
        if(amount == 0) return;
        if(mHealth == 0) return;

        mHealth += amount;
        if(mHealth < 0)
        {
            mHealth = 0;
        }

        if(mHealth > mMaxHealth)
        {
            mHealth = mMaxHealth;
        }

        if(amount < 0)
        {
            TakenDamage(-amount);
            if(mHealth <= 0)
            {
                HealthEmpty();
            }

            else
            {
                HealthRegenerate(amount);
            }
        }
    }

    void HealthComponent::TakenDamage(float amount)
    {
        LOG("Take Damage", amount, mHealth, mMaxHealth)
    }

    void HealthComponent::HealthEmpty()
    {
        LOG("Dead")
    }

    void HealthComponent::HealthRegenerate(float amount)
    {
        LOG("Health Regenerate", amount, mHealth, mMaxHealth)
    }
}
