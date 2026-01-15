#pragma once
#include <string>

inline std::string GetResourceDir()
{
#ifdef NDEBUG // Release Build
	return "assets/";
#else // Debug Build
	return "F:/C++/C++ Projects/AstroGlade/AstroGlade/assets/";
#endif
}
