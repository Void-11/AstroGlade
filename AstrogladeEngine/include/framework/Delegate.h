#pragma once
#include "Core.h"
#include "Object.h"

namespace ly
{
    template<typename ... Args>
    class Delegate
    {
    public:

        template<typename ClassName>
        void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...))
        {
            
        }
    };
}
