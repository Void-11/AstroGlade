cmake_minimum_required(VERSION 3.27.7)

project(AstroGlade
	VERSION 1.0.0
	LANGUAGES C CXX
)

# Everything in the build, including the fetched SFML and Box2D sources, is compiled as ISO C++17.
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

option(ASTROGLADE_WARNINGS_AS_ERRORS "Treat compiler warnings in the AstroGlade engine and game code as errors" ON)

# Warning and conformance settings shared by the engine and the game.
# Linked PRIVATE so they never leak onto third-party code.
add_library(AstroGladeCompilerOptions INTERFACE)
target_compile_features(AstroGladeCompilerOptions INTERFACE cxx_std_17)
if(MSVC)
	target_compile_options(AstroGladeCompilerOptions INTERFACE
		/W4
		/permissive-
		/Zc:__cplusplus
		/utf-8
		$<$<BOOL:${ASTROGLADE_WARNINGS_AS_ERRORS}>:/WX>
	)
else()
	target_compile_options(AstroGladeCompilerOptions INTERFACE
		-Wall
		-Wextra
		-Wpedantic
		$<$<BOOL:${ASTROGLADE_WARNINGS_AS_ERRORS}>:-Werror>
	)
endif()

# creates a variable.
set(ASTRO_GLADE_ENGINE_TARGET_NAME AstroGladeEngine)
set(ASTRO_GLADE_GAME_TARGET_NAME AstroGlade)

add_subdirectory(AstroGladeEngine)
add_subdirectory(AstroGlade)
