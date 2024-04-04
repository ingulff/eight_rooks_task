cmake_minimum_required(VERSION 3.20)

project(program
	VERSION 0.0.1
	DESCRIPTION "Simple http server"
	LANGUAGES C CXX
)


#-----------------------------------------------------------------------------------------------------------------------------------------
# General options
#-----------------------------------------------------------------------------------------------------------------------------------------

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRING "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(EXECUTABLE_TARGET_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_TARGET_NAME})


# other options

#-----------------------------------------------------------------------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------------------------------------------------------------------

# other dependecies


#------------------------------------------------------------------------------------------------------------------------------------------
# Sources
#------------------------------------------------------------------------------------------------------------------------------------------

set(${EXECUTABLE_TARGET_NAME}_source
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/board/board.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/error/error.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/figures/rook.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/logger/logger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/settings/settings.cpp
)

# other source

#------------------------------------------------------------------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------------------------------------------------------------------

target_sources(${EXECUTABLE_TARGET_NAME}
	PRIVATE
		${${EXECUTABLE_TARGET_NAME}_source}
)

target_compile_definitions(${EXECUTABLE_TARGET_NAME}
	PRIVATE
		ROOK_COUNT=${ROOK_COUNT}
		MIN_MOVE_TIMEOUT=${MIN_MOVE_TIMEOUT}
		MAX_MOVE_TIMEOUT=${MAX_MOVE_TIMEOUT}
		WAIT_MOVE_TIMEOUT=${WAIT_MOVE_TIMEOUT}
		MOVE_COUNT=${MOVE_COUNT}
)

set(COMPILE_OPTIONS)
if(MSVC)
	list(APPEND
		COMPILE_OPTIONS
		/std:c++17
		/Zc:__cplusplus
		/bigobj
	)
else()
	list(APPEND
		COMPILE_OPTIONS
		-std=c++17
	)
endif()

target_compile_options(${EXECUTABLE_TARGET_NAME}
	PRIVATE
		${COMPILE_OPTIONS}
)

# target_link_options()

target_include_directories(${EXECUTABLE_TARGET_NAME}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

if(UNIX)
    target_link_libraries(${EXECUTABLE_TARGET_NAME} pthread)
endif(UNIX)

#target_link_libraries(${EXECUTABLE_TARGET_NAME}
#	PRIVATE
#)


set_target_properties(${EXECUTABLE_TARGET_NAME}
	PROPERTIES
		SOVERSION ${PROJECT_VERSION_MAJOR}
		VERSION ${PROJECT_VERSION}
)

