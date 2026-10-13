#include <string>
#include <system_error>

#include "framework/Platform.h"

#if defined(_WIN32)
#include <windows.h>
#endif

namespace ly
{
	std::filesystem::path GetExecutableDirectory()
	{
#if defined(_WIN32)
		// The wide API keeps paths with non-ASCII characters intact; grow the buffer until the full path fits.
		std::wstring buffer(MAX_PATH, L'\0');
		while (true)
		{
			const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
			if (length == 0)
			{
				break;
			}

			if (length < buffer.size())
			{
				buffer.resize(length);
				return std::filesystem::path{ buffer }.parent_path();
			}

			buffer.resize(buffer.size() * 2);
		}
#elif defined(__linux__)
		std::error_code linkError;
		const std::filesystem::path executable = std::filesystem::read_symlink("/proc/self/exe", linkError);
		if (!linkError)
		{
			return executable.parent_path();
		}
#endif

		std::error_code error;
		return std::filesystem::current_path(error);
	}
}
