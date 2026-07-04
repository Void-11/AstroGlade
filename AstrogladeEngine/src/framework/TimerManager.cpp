#include "framework/TimerManager.h"

namespace ly
{
	unsigned int TimerHandle::timerKeyCounter = 0;

	TimerHandle::TimerHandle()
		: mTimerKey{GetNextTimerKey()}
	{

	}
	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: mListener{ weakRef, callback },
		mDuration{ duration },
		mRepeat{ repeat },
		mTimeCounter{ 0.f },
		mIsExpired{ false }
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

	unique<TimerManager> TimerManager::timerManager{ nullptr };
	
	TimerManager::TimerManager()
		: mTimers{},
		mPendingTimers{},
		mIsUpdating{false}
	{
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
		mIsUpdating = true;
		for (auto iter = mTimers.begin(); iter != mTimers.end();)
		{
			if (iter->second.Expired())
			{
				iter = mTimers.erase(iter);
			}
			else
			{
				iter->second.TickTime(deltaTime);
				if (iter->second.Expired())
				{
					iter = mTimers.erase(iter);
				}
				else
				{
					++iter;
				}
			}
		}
		mIsUpdating = false;

		for (auto& pendingTimer : mPendingTimers)
		{
			if (!pendingTimer.second.Expired())
			{
				mTimers.insert(pendingTimer);
			}
		}
		mPendingTimers.clear();
	}

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		auto iter = mTimers.find(timerHandle);
		if (iter != mTimers.end())
		{
			iter->second.SetExpired();
			return;
		}

		for (auto& pendingTimer : mPendingTimers)
		{
			if (pendingTimer.first == timerHandle)
			{
				pendingTimer.second.SetExpired();
				return;
			}
		}
	}
}
