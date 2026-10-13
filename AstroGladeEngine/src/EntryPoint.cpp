#include <cstdlib>
#include <exception>
#include <string_view>

#include "EntryPoint.h"
#include "framework/Application.h"
#include "framework/Log.h"

int main(int argc, char* argv[])
{
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
