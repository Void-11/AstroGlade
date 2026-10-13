#ifndef ASTROGLADE_ENGINE_FRAMEWORK_TIMERMANAGER_H
#define ASTROGLADE_ENGINE_FRAMEWORK_TIMERMANAGER_H

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	// Identifies a timer created by TimerManager::SetTimer.
	// A default constructed handle refers to no timer, so clearing it is a harmless no-op.
	class TimerHandle
	{
	public:
		TimerHandle() = default;

		[[nodiscard]] bool IsValid() const { return mTimerKey != 0; }
		[[nodiscard]] unsigned int GetTimerKey() const { return mTimerKey; }

		friend bool operator==(const TimerHandle& lhs, const TimerHandle& rhs) { return lhs.mTimerKey == rhs.mTimerKey; }
		friend bool operator!=(const TimerHandle& lhs, const TimerHandle& rhs) { return !(lhs == rhs); }

	private:
		friend class TimerManager;
		explicit TimerHandle(unsigned int timerKey) : mTimerKey{ timerKey } {}

		unsigned int mTimerKey = 0;
	};
}

namespace std
{
	template<>
	struct hash<ly::TimerHandle>
	{
		std::size_t operator()(const ly::TimerHandle& timerHandle) const noexcept
		{
			return std::hash<unsigned int>{}(timerHandle.GetTimerKey());
		}
	};
}

namespace ly
{
	class Timer
	{
	public:
		Timer(weak<Object> listener, std::function<void()> callback, float duration, bool repeat);

		void TickTime(float deltaTime);
		[[nodiscard]] bool Expired() const;
		void SetExpired();

	private:
		weak<Object> mListener;
		std::function<void()> mCallback;
		float mDuration = 0.f;
		bool mRepeat = false;
		float mTimeCounter = 0.f;
		bool mIsExpired = false;
	};

	class TimerManager
	{
	public:
		[[nodiscard]] static TimerManager& Get();

		TimerManager(const TimerManager&) = delete;
		TimerManager& operator=(const TimerManager&) = delete;

		// Calls callback on the listener every duration seconds (or once when repeat is false)
		// until the timer is cleared or the listener is destroyed.
		template<typename ClassName>
		TimerHandle SetTimer(weak<Object> listener, void(ClassName::* callback)(), float duration, bool repeat = false)
		{
			static_assert(std::is_base_of_v<Object, ClassName>, "Timer listeners must derive from ly::Object");

			const TimerHandle timerHandle{ ++mLastTimerKey };
			Timer timer{ listener, [listener, callback]
				{
					if (const shared<Object> owner = listener.lock())
					{
						std::invoke(callback, static_cast<ClassName*>(owner.get()));
					}
				}, duration, repeat };

			if (mIsUpdating)
			{
				mPendingTimers.emplace_back(timerHandle, std::move(timer));
			}
			else
			{
				mTimers.try_emplace(timerHandle, std::move(timer));
			}

			return timerHandle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);

	private:
		TimerManager() = default;

		Dictionary<TimerHandle, Timer> mTimers;
		List<std::pair<TimerHandle, Timer>> mPendingTimers;
		unsigned int mLastTimerKey = 0;
		bool mIsUpdating = false;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_TIMERMANAGER_H
