#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG  //release build
    
    return "assets/";

#else
    
    return "/Users/viv/Developer/AstroGlade/AstroGlade/assets/";

#endif  
}
