#include "framework/Object.h"

namespace ly
{
	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}
}
