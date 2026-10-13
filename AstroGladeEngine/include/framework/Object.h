#ifndef ASTROGLADE_ENGINE_FRAMEWORK_OBJECT_H
#define ASTROGLADE_ENGINE_FRAMEWORK_OBJECT_H

#include <memory>

#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object() = default;
		virtual ~Object() = default;

		// An Object has identity (a unique ID, bound delegates, weak references to it),
		// so it can be neither copied nor moved.
		Object(const Object&) = delete;
		Object& operator=(const Object&) = delete;

		virtual void Destroy();
		[[nodiscard]] bool IsPendingDestroy() const { return mIsPendingDestroy; }

		// weak_from_this (C++17) yields an empty reference instead of throwing when the
		// Object is not owned by a shared_ptr.
		weak<Object> GetWeakRef() { return weak_from_this(); }
		weak<const Object> GetWeakRef() const { return weak_from_this(); }
		Delegate<Object*> onDestroy;
		[[nodiscard]] unsigned int GetUniqueID() const { return mUniqueID; }

	private:
		static unsigned int GetNextAvailableID() { return sUniqueIDCounter++; }

		inline static unsigned int sUniqueIDCounter = 0;

		bool mIsPendingDestroy = false;
		unsigned int mUniqueID = GetNextAvailableID();
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_OBJECT_H
