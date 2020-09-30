cmake_minimum_required(VERSION 3.17)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory("RavEngine")

project("RavEngine_Samples")

macro (add_sample sample_dir)
	# create the test executable
	SET(APPNAME "RavEngine_Sample_${sample_dir}")

	file(GLOB TEST_SOURCES "${sample_dir}/*.cpp" "${sample_dir}/*.hpp" "${sample_dir}/*.h")

	# creates a mac app if applicable
	add_executable("${APPNAME}" ${TEST_SOURCES})
	set_target_properties("${APPNAME}" 
		PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
		VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
	)
	target_link_libraries("${APPNAME}" PUBLIC "RavEngine" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${APPNAME}")

	file(GLOB meshes "${sample_dir}/meshes/*.obj")
	add_meshes("${APPNAME}" "${meshes}")

	pack_resources("${APPNAME}")

	# fixup mac bundle
	INSTALL(CODE 
		"include(BundleUtilities)
		fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.app\" \"\" \"\")
		" 
		COMPONENT Runtime
	)
endmacro()

#startup project	
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${PROJECT_NAME}_Test")

add_sample("AirHockey")
add_sample("Playground")

compile_shader_dir("RavEngine_Sample_Playground" "${CMAKE_CURRENT_SOURCE_DIR}/Playground/shaders")
