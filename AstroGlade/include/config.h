#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG  //release build
    
    return "assets/";

#else
    
    return "E:/C++ Projects/AstroGlade/AstroGlade/assets/";

#endif  
}
