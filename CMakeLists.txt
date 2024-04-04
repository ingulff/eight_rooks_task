cmake_minimum_required(VERSION 3.20)

project(test_task
	VERSION 0.0.1
	DESCRIPTION "Test Task"
	LANGUAGES C CXX
)

#-----------------------------------------------------------------------------------------------------------------------------------------
# General options
#-----------------------------------------------------------------------------------------------------------------------------------------

#add_compile_definitions(_WIN32_WINNT=0x0601)

option(TT_BUILD_TESTS "Enable build unit tests" ON)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRING "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(MAIN_TARGET_NAME "${PROJECT_NAME}")
add_custom_target(${MAIN_TARGET_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#include(3rdparty)

set(DEFAULT_ROOK_COUNT 6)
set(DEFAULT_MIN_MOVE_TIMEOUT 200)
set(DEFAULT_MAX_MOVE_TIMEOUT 300)
set(DEFAULT_WAIT_MOVE_TIMEOUT 5000)
set(DEFAULT_MOVE_COUNT 50)

set(ROOK_COUNT ${DEFAULT_ROOK_COUNT})
if(DEFINED TT_ROOK_COUNT)
	set(ROOK_COUNT ${TT_ROOK_COUNT})
endif()

set(MIN_MOVE_TIMEOUT ${DEFAULT_MIN_MOVE_TIMEOUT})
if(DEFINED TT_MIV_MOVE_TIMEOUT)
	set(MIN_MOVE_TIMEOUT ${MIN_MOVE_TIMEOUT})
endif()

set(MAX_MOVE_TIMEOUT ${DEFAULT_MAX_MOVE_TIMEOUT})
if(DEFINED TT_MAX_MOVE_TIMEOUT)
	set(MAX_MOVE_TIMEOUT ${TT_MAX_MOVE_TIMEOUT})
endif()

set(WAIT_MOVE_TIMEOUT ${DEFAULT_WAIT_MOVE_TIMEOUT})
if(DEFINED TT_WAIT_MOVE_TIMEOUT)
	set(WAIT_MOVE_TIMEOUT ${TT_WAIT_MOVE_TIMEOUT})
endif()

set(MOVE_COUNT ${DEFAULT_MOVE_COUNT})
if(DEFINED TT_MOVE_COUNT)
	set(MOVE_COUNT ${TT_MOVE_COUNT})
endif()

message(STATUS "taget:${MAIN_TARGET_NAME} option TT_BUILD_TESTS=${TT_BUILD_TESTS}")
message(STATUS "target:${MAIN_TARGET_NAME} option ROOK_COUNT=${ROOK_COUNT}")
message(STATUS "target:${MAIN_TARGET_NAME} option MIN_MOVE_TIMEOUT=${MIN_MOVE_TIMEOUT}")
message(STATUS "target:${MAIN_TARGET_NAME} option MAX_MOVE_TIMEOUT=${MAX_MOVE_TIMEOUT}")
message(STATUS "target:${MAIN_TARGET_NAME} option WAIT_MOVE_TIMEOUT=${WAIT_MOVE_TIMEOUT}")
message(STATUS "target:${MAIN_TARGET_NAME} option MOVE_COUNT=${MOVE_COUNT}")

# other option

#-----------------------------------------------------------------------------------------------------------------------------------------
# Dependencies
#-----------------------------------------------------------------------------------------------------------------------------------------

set(${MAIN_TARGET_NAME}_depencies
	program
)

if(TT_BUILD_TESTS)
	list(APPEND 
		${MAIN_TARGET_NAME}_depencies
		tests
	)
endif()

add_dependencies(${MAIN_TARGET_NAME}
	${${MAIN_TARGET_NAME}_depencies}
)

# other dependencies

#------------------------------------------------------------------------------------------------------------------------------------------
# Sources
#------------------------------------------------------------------------------------------------------------------------------------------

# other source


#------------------------------------------------------------------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------------------------------------------------------------------

add_subdirectory(source)

if(TT_BUILD_TESTS)
	message(STATUS "Tests add to build")
	add_subdirectory(tests)
	enable_testing()
endif()

