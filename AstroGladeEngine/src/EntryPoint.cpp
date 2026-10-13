#include <cstdlib>
#include <exception>
#include <filesystem>
#include <string_view>
#include <system_error>

#include "EntryPoint.h"
#include "framework/Application.h"
#include "framework/Log.h"
#include "framework/Platform.h"

int main(int argc, char* argv[])
{
	// Relative paths, such as the Release build's assets folder, must resolve next to the executable
	// however the game was started (a shortcut with another "Start in" folder, a terminal, a launcher).
	// Moving the working directory keeps those paths short and relative, which also spares SFML 2's
	// narrow-string file APIs any non-ASCII characters in the install path.
	std::error_code workingDirectoryError;
	std::filesystem::current_path(ly::GetExecutableDirectory(), workingDirectoryError);
	if (workingDirectoryError)
	{
		ly::LogError("Could not switch to the executable's folder: ", workingDirectoryError.message());
	}

	// The arguments live for the whole run, so non-owning views into them are safe.
	const ly::List<std::string_view> commandLine(argv, argv + argc);

	try
	{
		const ly::unique<ly::Application> app = ly::CreateApplication(commandLine);
		app->Run();
	}
	catch (const std::exception& exception)
	{
		ly::LogError("Fatal error: ", exception.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
