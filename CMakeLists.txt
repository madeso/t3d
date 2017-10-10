cmake_minimum_required(VERSION 3.0.2)
project(t3d)

set_property(GLOBAL PROPERTY USE_FOLDERS OFF)

# compiler flags
if(WIN32)
	ADD_DEFINITIONS(/D _CRT_SECURE_NO_WARNINGS)
	
	# character set to Not Set=ASCII/SBCS http://public.kitware.com/Bug/view.php?id=12189
	ADD_DEFINITIONS(/D _SBCS)
endif(WIN32)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# force visual studio and the like to only have debug and release builds
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Reset the configurations to what we need" FORCE)
endif()

find_package(OpenGL REQUIRED)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(external/euphoria)
include_directories(external/euphoria)
add_subdirectory(t3d)
