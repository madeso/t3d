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

# wxWidgets_USE_DEBUG
# wxWidgets_USE_UNICODE
# wxWidgets_USE_UNIVERSAL
SET(wxWidgets_USE_STATIC, ON)

find_package(wxWidgets COMPONENTS core base gl REQUIRED)
find_package(OpenGL REQUIRED)
include( "${wxWidgets_USE_FILE}" )

message(STATUS "wxWidgets_FOUND = ${wxWidgets_FOUND}")
message(STATUS "wxWidgets_INCLUDE_DIRS = ${wxWidgets_INCLUDE_DIRS}")
message(STATUS "wxWidgets_LIBRARIES = ${wxWidgets_LIBRARIES}")
message(STATUS "wxWidgets_LIBRARY_DIRS = ${wxWidgets_LIBRARY_DIRS}")
message(STATUS "wxWidgets_DEFINITIONS = ${wxWidgets_DEFINITIONS}")
message(STATUS "wxWidgets_DEFINITIONS_DEBUG = ${wxWidgets_DEFINITIONS_DEBUG}")
message(STATUS "wxWidgets_CXX_FLAGS = ${wxWidgets_CXX_FLAGS}")
message(STATUS "wxWidgets_USE_FILE = ${wxWidgets_USE_FILE}")

include_directories(${CMAKE_SOURCE_DIR})


include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(t3d)
