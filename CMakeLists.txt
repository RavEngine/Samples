cmake_minimum_required(VERSION 3.17)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

# linux detection
if(UNIX AND NOT APPLE)
	set(LINUX TRUE CACHE INTERNAL "")
endif()

if(LINUX)
	set(CMAKE_CXX_STANDARD_LIBRARIES -latomic) # need libatomic on linux
endif()

if(MSVC)
  add_definitions(/MP)
  add_definitions(/Qpar)
endif()

project("RavEngine_Samples")
#set(CMAKE_OSX_SYSROOT iphoneos CACHE INTERNAL "")
add_subdirectory("RavEngine")

function (add_sample sample_dir)
	# create the test executable
	SET(APPNAME "RavEngine_Sample_${sample_dir}")

	file(GLOB TEST_SOURCES "${sample_dir}/*.cpp" "${sample_dir}/*.hpp" "${sample_dir}/*.h")

	# creates a mac app if applicable
	add_executable("${APPNAME}" ${TEST_SOURCES})
	set_target_properties("${APPNAME}" 
		PROPERTIES 
		MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
	)
	target_link_libraries("${APPNAME}" PUBLIC "RavEngine" )

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${APPNAME}")

	file(GLOB meshes "${sample_dir}/meshes/*.obj")
	file(GLOB textures "${sample_dir}/textures/*")
	file(GLOB shaders "${sample_dir}/shaders/*.cmake")
	file(GLOB uis "${sample_dir}/ui/*.rml" "${sample_dir}/ui/*.rcss" "${sample_dir}/ui/*.png")
	file(GLOB sounds "${sample_dir}/sounds/*")

	pack_resources(TARGET "${APPNAME}" 
		MESHES ${meshes}
		SHADERS ${shaders}
		TEXTURES ${textures}
		UIS ${uis}
		SOUNDS ${sounds}
	)

	# fixup mac bundle
	INSTALL(CODE 
		"include(BundleUtilities)
		fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.app\" \"\" \"\")
		" 
		COMPONENT Runtime
	)
endfunction()

add_sample("AirHockey")
add_sample("Playground")
add_sample("Performance_C")
add_sample("GUIKitchenSink")

# tests
include(CTest)
add_executable("${PROJECT_NAME}_TestBasics" "Test/basics.cpp")
target_link_libraries("${PROJECT_NAME}_TestBasics" PUBLIC "RavEngine" )

macro(test name executable)
add_test(
	NAME ${name} 
	COMMAND ${executable} "${name}" -C $<CONFIGURATION> 
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>
)
endmacro()

test("CTTI" "${PROJECT_NAME}_TestBasics")