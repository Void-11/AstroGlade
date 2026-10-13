#include <algorithm>

#include "framework/TimerManager.h"

namespace ly
{
	Timer::Timer(weak<Object> listener, std::function<void()> callback, float duration, bool repeat)
		: mListener{ std::move(listener) },
		mCallback{ std::move(callback) },
		mDuration{ duration },
		mRepeat{ repeat }
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
			mCallback();

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
		if (mIsExpired)
		{
			return true;
		}

		const shared<Object> listener = mListener.lock();
		return !listener || listener->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	TimerManager& TimerManager::Get()
	{
		static TimerManager timerManager;
		return timerManager;
	}

	void TimerManager::UpdateTimer(float deltaTime)
	{
		mIsUpdating = true;
		for (auto iter = mTimers.begin(); iter != mTimers.end();)
		{
			Timer& timer = iter->second;
			timer.TickTime(deltaTime);

			if (timer.Expired())
			{
				iter = mTimers.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		mIsUpdating = false;

		for (auto& [timerHandle, timer] : mPendingTimers)
		{
			if (!timer.Expired())
			{
				mTimers.try_emplace(timerHandle, std::move(timer));
			}
		}
		mPendingTimers.clear();
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		if (!timerHandle.IsValid())
		{
			return;
		}

		if (const auto iter = mTimers.find(timerHandle); iter != mTimers.end())
		{
			iter->second.SetExpired();
			return;
		}

		const auto pendingIter = std::find_if(mPendingTimers.begin(), mPendingTimers.end(),
			[timerHandle](const auto& pendingTimer) { return pendingTimer.first == timerHandle; });

		if (pendingIter != mPendingTimers.end())
		{
			pendingIter->second.SetExpired();
		}
	}
}
