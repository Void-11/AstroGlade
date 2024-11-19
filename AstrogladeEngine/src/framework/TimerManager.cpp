#include "framework/TimerManager.h"

namespace ly
{
    unique<TimerManager> TimerManager::timerManager{ nullptr };
    
    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
        : mListener{ weakRef, callback },
        mDuration{ duration },
        mRepeat{ repeat },
        mTimeCounter{ 0.f },
        mIsExpired{ false }
    {
        
    }

    TimerManager::TimerManager() : mTimers{}
    {
    }
    
    void Timer::TickTime(float deltaTime)
    {
        if (Expired())
        {
            return;
        }

        mTimeCounter += deltaTime;
        if (mTimeCounter >= mDuration)
        {
            mListener.second();

            if (mRepeat)
            {
                mTimeCounter = 0.f;
            }
            else
            {
                SetExpired();
            }
        }   
    }

    bool Timer::Expired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }

    TimerManager& TimerManager::Get()
    {
        if (!timerManager)
        {
            timerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }

        return *timerManager;
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (Timer& timer : mTimers)
        {
            timer.TickTime(deltaTime);
        }
    }
}