#ifndef ASTROGLADE_ENGINE_FRAMEWORK_PLATFORM_H
#define ASTROGLADE_ENGINE_FRAMEWORK_PLATFORM_H

#include <filesystem>

namespace ly
{
	// The folder that contains the running executable, wherever the program was started from.
	// Falls back to the current working directory on platforms where it cannot be determined.
	[[nodiscard]] std::filesystem::path GetExecutableDirectory();
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_PLATFORM_H
