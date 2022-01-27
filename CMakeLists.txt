cmake_minimum_required(VERSION 3.16)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE INTERNAL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64" CACHE INTERNAL "")

# linux detection
if(UNIX AND NOT APPLE)
	set(LINUX TRUE CACHE INTERNAL "")
endif()

if(LINUX)
	set(atomic_lib atomic CACHE INTERNAL "") # need libatomic on linux
endif()

if(MSVC)
  add_definitions(/MP)
endif()

#Enable iPad as well as iPhone (Universal)
set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2,3" CACHE INTERNAL "")

project("RavEngine_Samples")

set(RAVENGINE_BUILD_TESTS ON CACHE INTERNAL "")
add_subdirectory("RavEngine")

file(GLOB COMMON_FILES "Samples/Common/*.hpp" "Samples/Common/*.cpp")
if(CMAKE_SYSTEM_NAME MATCHES Emscripten)
	set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

function (add_sample sample_dir)
	# create the test executable
	SET(APPNAME "RavEngine${sample_dir}")
	SET(sample_dir "Samples/${sample_dir}")

	# create the helper header file
	make_directory("${APPNAME}")
	configure_file("Samples/AppInfo.hpp" "${CMAKE_BINARY_DIR}/${APPNAME}/" @ONLY)

	file(GLOB TEST_SOURCES "${sample_dir}/*.cpp" "${sample_dir}/*.hpp" "${sample_dir}/*.h" "${CMAKE_BINARY_DIR}/${APPNAME}/*.hpp" )

	# creates a mac app if applicable
	add_executable("${APPNAME}" ${TEST_SOURCES} ${COMMON_FILES} "Samples/logo.png" "Samples/windows.rc" "Samples/iosLaunchScreen.storyboard")
	set_target_properties("${APPNAME}" 
		PROPERTIES 
		MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Samples/Info.plist.in"
		XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.ravbug.${APPNAME}"		# with templated plist we can set this
		XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.ravbug.${APPNAME}"
		VS_GLOBAL_OutputType AppContainerExe
	)
	target_link_libraries("${APPNAME}" PUBLIC "RavEngine" ${atomic_lib})
	target_include_directories("${APPNAME}" PUBLIC "${CMAKE_BINARY_DIR}/${APPNAME}" "${CMAKE_CURRENT_LIST_DIR}/Samples/Common")
	target_compile_features(${APPNAME} PRIVATE cxx_std_17)
	set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/Samples/logo.png" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${APPNAME}")

	# UWP / Winstore deployment things
	set(WINSTORE_MANIFEST "${CMAKE_CURRENT_LIST_DIR}/Samples/Sample.appxmanifest.in")
	set(WINSTORE_ICONS "${CMAKE_CURRENT_LIST_DIR}/Samples/logo.png")
	set_property(SOURCE WINSTORE_MANIFEST PROPERTY VS_DEPLOYMENT_CONTENT 1)
	set_property(SOURCE "${WINSTORE_ICONS}" PROPERTY VS_DEPLOYMENT_CONTENT 1)
	set_property(SOURCE "${WINSTORE_ICONS}" PROPERTY VS_DEPLOYMENT_LOCATION "")

	file(GLOB objects "${sample_dir}/objects/*.fbx" "${sample_dir}/objects/*.dae" "${sample_dir}/objects/*.ozz" "${sample_dir}/objects/*.obj", "${sample_dir}/objects/*.ply")
	file(GLOB textures "${sample_dir}/textures/*.jpg", "${sample_dir}/textures/*.png" "${sample_dir}/textures/*.svg")
	file(GLOB shaders "${sample_dir}/shaders/*.cmake")
	file(GLOB uis "${sample_dir}/ui/*.rml" "${sample_dir}/ui/*.rcss" "${sample_dir}/ui/*.png" "${sample_dir}/ui/*.json" "${sample_dir}/ui/*.ids")
	file(GLOB sounds "${sample_dir}/sounds/*.mp3", "${sample_dir}/sounds/*.wav", "${sample_dir}/sounds/*.ogg", "${sample_dir}/sounds/*.midi")

	pack_resources(TARGET "${APPNAME}"
		OBJECTS ${objects}
		SHADERS ${shaders}
		TEXTURES ${textures}
		UIS ${uis}
		SOUNDS ${sounds}
	)

	# fixup mac bundle, or generate Linux AppImage
	if(APPLE)
		target_compile_options("${APPNAME}" PUBLIC -ftemplate-backtrace-limit=0)	# clang arg to facilitate template debugging
		INSTALL(CODE 
			"include(BundleUtilities)
			fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.app\" \"\" \"\")
			" 
			COMPONENT Runtime
		)
    elseif(LINUX)
        if(CMAKE_BUILD_TYPE STREQUAL Release)
        	if (NOT DEFINED TARGET_ARCH)
        		set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR} CACHE INTERNAL "")
        	endif()
        	if(${TARGET_ARCH} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR})
        		set(IS_CROSSCOMP OFF CACHE INTERNAL "")
        	else()
				set(IS_CROSSCOMP ON CACHE INTERNAL "")
        	endif()

            INSTALL(CODE
                "include(${CMAKE_CURRENT_SOURCE_DIR}/appimage.cmake)
                make_appimage(
                    EXE \"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}\"
                    NAME \"${APPNAME}\"
                    ICON \"${CMAKE_CURRENT_SOURCE_DIR}/Samples/logo.png\"
                    DIR_ICON \"${CMAKE_CURRENT_SOURCE_DIR}/Samples/logo.png\"
                    OUTPUT_NAME \"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.AppImage\"
                    OUTPUT_ARCH \"${TARGET_ARCH}\"
                    CROSSCOMP ${IS_CROSSCOMP}
                    ASSETS \"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.rvedata\"
                )
                "
                COMPONENT Runtime
            )
        endif()
	endif()

    # Strip binary for release builds
    if (CMAKE_BUILD_TYPE STREQUAL Release)
		if(LINUX)
			#add_custom_command(TARGET ${APPNAME} POST_BUILD COMMAND ${CMAKE_STRIP} ${CMAKE_BUILD_TYPE}/${APPNAME})
		elseif(APPLE)
			#add_custom_command(TARGET ${APPNAME} POST_BUILD COMMAND ${CMAKE_STRIP} ${CMAKE_BUILD_TYPE}/${APPNAME}.app/Contents/MacOS/${APPNAME})
		endif()
    endif ()

endfunction()

add_sample("AirHockey")
add_sample("Playground")
add_sample("Animation")
add_sample("Perf-ECS")
add_sample("Perf-Draw")
add_sample("Perf-DrawAnimated")
add_sample("Perf-RigidBodies")
add_sample("Perf-Network")
add_sample("Perf-Lighting")
add_sample("GUI")
add_sample("SoundDynamics")
add_sample("Flags")
add_sample("Navigation")
add_sample("HelloCube")
add_sample("Gravity")
add_sample("SystemInfo")
