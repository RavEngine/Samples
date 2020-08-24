cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RavEngine-AirHockey)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("RavEngine")
include_directories("RavEngine/include")

# create the test executable
file(GLOB TEST_SOURCES "src/*.cpp")
file(GLOB TEST_HEADERS "src/*.hpp")
file(GLOB TEST_CHEADERS "src/*.h")

# creates a mac app if applicable
add_executable("${PROJECT_NAME}" MACOSX_BUNDLE ${TEST_SOURCES} ${TEST_HEADERS} ${TEST_CHEADERS})
set_target_properties("${PROJECT_NAME}" PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/src/Info.plist")


target_link_libraries("${PROJECT_NAME}" "RavEngine" )

# copy DLLs
if (WIN32)
	if(NOT PX_GENERATE_STATIC_LIBRARIES)
		add_custom_command(TARGET "${PROJECT_NAME}" POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
				"${CMAKE_BINARY_DIR}/RavEngine/bin/win.x86_64.vc142.md/$<CONFIGURATION>"
				"$<TARGET_FILE_DIR:${PROJECT_NAME}>")
	endif()
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}")