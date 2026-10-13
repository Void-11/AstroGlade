add_library(${ASTRO_GLADE_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/BackdropActor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/BackdropActor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/BackgroundLayer.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/BackgroundLayer.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AudioManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AudioManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtility.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/PhysicsSystem.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/PhysicsSystem.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Platform.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Platform.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Delegate.h

	${CMAKE_CURRENT_SOURCE_DIR}/include/vfx/Particle.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/vfx/Particle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/TimerManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/TimerManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Log.h

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/GameStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/GameStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/WaitStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/WaitStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/HUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/HUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/Widget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/Widget.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/TextWidget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/TextWidget.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/ValueGauge.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/ValueGauge.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/ImageWidget.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/ImageWidget.cpp


	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/Button.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/Button.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp
)

target_include_directories(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

# The engine headers use C++17 features, so every consumer must compile as C++17 too.
target_compile_features(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC cxx_std_17)
target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PRIVATE AstroGladeCompilerOptions)

# Keep <windows.h> lean and stop its min/max macros from clashing with std::min and std::max.
if(WIN32)
	target_compile_definitions(${ASTRO_GLADE_ENGINE_TARGET_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

include(FetchContent)

# Let the plain variables below override option() defaults in the older third-party CMake projects.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SFML_LIB_NAME SFML)

# Only the SFML modules the engine uses are built.
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)

# SYSTEM marks the third-party headers as external, so our warning level does not apply to them.
FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.6.1
	GIT_SHALLOW FALSE
	SYSTEM
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC sfml-audio)

set(BOX2D_LIB_NAME Box2D)

# The Box2D testbed and unit tests are not needed to build the game.
set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_DOCS OFF)

FetchContent_Declare(
	${BOX2D_LIB_NAME}
	GIT_REPOSITORY https://github.com/erincatto/box2d
	GIT_TAG v2.4.1
	GIT_SHALLOW FALSE
	SYSTEM
)

FetchContent_MakeAvailable(${BOX2D_LIB_NAME})
target_link_libraries(${ASTRO_GLADE_ENGINE_TARGET_NAME} PUBLIC box2d)

# OpenAL ships with SFML as a prebuilt DLL rather than a CMake target, so it is not part of
# $<TARGET_RUNTIME_DLLS:...>. Record it on the engine so the executable can copy it next to itself.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(SFML_OPENAL_ARCH_DIR "x64")
else()
	set(SFML_OPENAL_ARCH_DIR "x86")
endif()

# FetchContent_MakeAvailable defines <lowercase name>_SOURCE_DIR for every fetched dependency.
set(SFML_OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/${SFML_OPENAL_ARCH_DIR}/openal32.dll")
if(EXISTS "${SFML_OPENAL_DLL}")
	set_property(TARGET ${ASTRO_GLADE_ENGINE_TARGET_NAME} PROPERTY ASTROGLADE_EXTRA_RUNTIME_FILES "${SFML_OPENAL_DLL}")
endif()
