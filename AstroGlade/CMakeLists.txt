add_executable(${ASTRO_GLADE_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/spaceship/Spaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/spaceship/Spaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Shooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Shooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/LaserShooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/LaserShooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/ThreeWayShooter.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/ThreeWayShooter.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/FrontalWiper.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/FrontalWiper.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Laser.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Laser.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/GameAudio.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/GameAudio.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/ResolutionScale.h

	${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/EnemySpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/EnemySpaceship.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/SpawnLocations.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/SpawnLocations.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Vanguard.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Vanguard.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/VanguardStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/VanguardStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/TwinBlade.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBlade.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/UFO.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFO.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/UFOStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/UFOStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Hexagon.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Hexagon.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/HexagonStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/HexagonStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/TwinBladeStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/TwinBladeStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/ChaosStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/ChaosStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/Boss.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/Boss.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Enemy/BossStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Enemy/BossStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Level/GameLevelOne.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Level/GameLevelOne.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Level/MainMenuLevel.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Level/MainMenuLevel.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Level/ScoreBriefingLevel.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Level/ScoreBriefingLevel.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/Level/MenuBackground.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Level/MenuBackground.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/Reward.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/Reward.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/Player.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/Player.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/GameplayHUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/GameplayHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/MainMenuHUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/MainMenuHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/ScoreBriefingHUD.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/ScoreBriefingHUD.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/MenuStyle.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/MenuStyle.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/widgets/ControlsPanel.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/widgets/ControlsPanel.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerManager.cpp
)

target_include_directories(${ASTRO_GLADE_GAME_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${ASTRO_GLADE_GAME_TARGET_NAME} PUBLIC ${ASTRO_GLADE_ENGINE_TARGET_NAME})
target_link_libraries(${ASTRO_GLADE_GAME_TARGET_NAME} PRIVATE AstroGladeCompilerOptions)

# Players get only the game window. Debug builds stay console programs, so the debug log is visible while developing.
# A Windows (non-console) program starts at WinMain; sfml-main provides one that forwards to the engine's main().
if(WIN32)
	set_target_properties(${ASTRO_GLADE_GAME_TARGET_NAME} PROPERTIES WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>)
	target_link_libraries(${ASTRO_GLADE_GAME_TARGET_NAME} PRIVATE sfml-main)
endif()

# Copy the SFML and Box2D DLLs (and OpenAL, recorded by the engine) next to the executable.
if(WIN32)
	add_custom_command(TARGET ${ASTRO_GLADE_GAME_TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_RUNTIME_DLLS:${ASTRO_GLADE_GAME_TARGET_NAME}>
		$<TARGET_PROPERTY:${ASTRO_GLADE_ENGINE_TARGET_NAME},ASTROGLADE_EXTRA_RUNTIME_FILES>
		$<TARGET_FILE_DIR:${ASTRO_GLADE_GAME_TARGET_NAME}>
		COMMAND_EXPAND_LISTS
	)
endif()

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
	TARGET ${ASTRO_GLADE_GAME_TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory_if_different
	${RESOURCE_SRC_DIR}
	$<TARGET_FILE_DIR:${ASTRO_GLADE_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

# config.h is generated into the build tree (it embeds a machine-specific path), never into the sources.
set(ASTRO_GLADE_GENERATED_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
configure_file(
	"config.h.in"
	"${ASTRO_GLADE_GENERATED_INCLUDE_DIR}/config.h" ESCAPE_QUOTES
)
target_include_directories(${ASTRO_GLADE_GAME_TARGET_NAME} PRIVATE
	${ASTRO_GLADE_GENERATED_INCLUDE_DIR}
)
