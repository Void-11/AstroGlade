#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "F:/C++/C++ Projects/LightYears-master/AstroGlade/assets/";
#endif
}
