#ifndef ASTROGLADE_ENGINE_FRAMEWORK_LOG_H
#define ASTROGLADE_ENGINE_FRAMEWORK_LOG_H

#include <iostream>
#include <utility>

namespace ly
{
#ifdef NDEBUG
	inline constexpr bool kDebugLogging = false;
#else
	inline constexpr bool kDebugLogging = true;
#endif

	// Reports a problem worth knowing about in every build, such as an asset that failed to load.
	// Writes every argument to standard error, followed by a newline, e.g. LogError("Failed to load texture: ", path);
	template<typename... Args>
	void LogError(Args&&... args)
	{
		(std::cerr << ... << std::forward<Args>(args)) << '\n';
	}

	// Notes that only help while developing, such as stage changes.
	// Writes to standard output in Debug builds; in other builds the call compiles to nothing.
	template<typename... Args>
	void LogDebug([[maybe_unused]] Args&&... args)
	{
		if constexpr (kDebugLogging)
		{
			(std::cout << ... << std::forward<Args>(args)) << '\n';
		}
	}
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_LOG_H
