cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(Meronia
	VERSION 1.0.0
	DESCRIPTION "A Terraria Clone"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SFML)

set(IS_DEBUG $<BOOL:$<CONFIG:Debug>>)

if (NOT ${IS_DEBUG})
	if (APPLE)
		set(GUI_TYPE MACOSX_BUNDLE)
	elseif (WIN32)
		set(GUI_TYPE WIN32)
	endif()
else()
	if (WIN32)
		set(GUI_TYPE "")
	endif()
endif()

add_executable(${PROJECT_NAME} ${GUI_TYPE} src/main.cpp)

target_sources(${PROJECT_NAME} PRIVATE
	src/base/Engine.cpp
	src/base/Engine.h
	src/base/Entity.h
	src/base/BaseInterfaces.h
	src/base/systems/EntityManager.h
	src/base/systems/EntityManager.cpp
	src/base/Helpers.h
	src/entities/DebugEntity.h
	src/entities/DebugEntity.cpp
	src/base/systems/UIManager.h
	src/base/systems/UIManager.cpp
	src/base/Contexts.h
	src/entities/map/Map.h
	src/entities/map/Map.cpp
	src/entities/map/MapData.h
	src/entities/map/MapData.cpp
	src/noise/SimplexNoise.hpp
	src/noise/SimplexNoise.cpp
 "src/base/systems/UUIDGenerator.h" "src/base/systems/InputManager.h" "src/base/systems/InputManager.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-system sfml-window)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} PUBLIC sfml-main)
endif()
