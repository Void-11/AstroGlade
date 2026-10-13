#ifndef ASTROGLADE_ENGINE_ENTRYPOINT_H
#define ASTROGLADE_ENGINE_ENTRYPOINT_H

#include <string_view>

#include "framework/Core.h"

namespace ly
{
	class Application;

	// Implemented by the game. Receives the command-line arguments and creates the application
	// that the engine's main() runs. Ownership is transferred to the caller.
	[[nodiscard]] unique<Application> CreateApplication(const List<std::string_view>& commandLine);
}

#endif // ASTROGLADE_ENGINE_ENTRYPOINT_H
