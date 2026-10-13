#ifndef ASTROGLADE_ENGINE_FRAMEWORK_DELEGATE_H
#define ASTROGLADE_ENGINE_FRAMEWORK_DELEGATE_H

#include <functional>
#include <type_traits>
#include <utility>

#include "framework/Core.h"

namespace ly
{
	class Object;

	// A multicast event. Callbacks are member functions of Objects; a callback is dropped
	// automatically once the Object that owns it has been destroyed.
	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...))
		{
			static_assert(std::is_base_of_v<Object, ClassName>, "Delegate callbacks must be member functions of an Object");

			mCallbacks.emplace_back([obj = std::move(obj), callback](Args... args)
			{
				if (const shared<Object> owner = obj.lock())
				{
					std::invoke(callback, static_cast<ClassName*>(owner.get()), args...);
					return true;
				}

				return false;
			});
		}

		void Broadcast(Args... args)
		{
			for (auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
			{
				if ((*iter)(args...))
				{
					++iter;
				}
				else
				{
					iter = mCallbacks.erase(iter);
				}
			}
		}

	private:
		List<std::function<bool(Args...)>> mCallbacks;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_DELEGATE_H
