cmake_minimum_required(VERSION 3.25)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE INTERNAL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64" CACHE INTERNAL "")
set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym" CACHE INTERNAL "")	# don't embed symbols in the binaries themselves

# linux detection
if(UNIX AND NOT APPLE)
	set(LINUX TRUE CACHE INTERNAL "")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(atomic_lib atomic CACHE INTERNAL "") # need libatomic on linux
endif()

if(MSVC)
  add_definitions(/MP)			# parallelize each target
endif()

#Enable iPad as well as iPhone (Universal)
set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2,3" CACHE INTERNAL "")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "")
	if (APPLE)
		set(TARGET_NAME "macOS")
	elseif(MSVC)
		set(TARGET_NAME "win32")
	elseif(UNIX AND NOT APPLE)
		set(TARGET_NAME "Linux")
	endif()
else()
	set(TARGET_NAME ${CMAKE_SYSTEM_NAME})
endif()

# set the project name to include the target system, because 
# sometimes one works on multiple targets on the same host
# and it can get confusing when using Open Recent without this
project("RavEngine_Samples_${TARGET_NAME}")

# ensure that cmake doesn't forget what architecture we are compiling
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR} CACHE INTERNAL "")
add_subdirectory("RavEngine")

file(GLOB COMMON_FILES "Samples/Common/*.hpp" "Samples/Common/*.cpp")
if(CMAKE_SYSTEM_NAME MATCHES Emscripten)
	set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
	# required for higher memory, atomics, and threads
	add_definitions(-pthread)
	add_definitions(-fexceptions)
endif()

if(TARGET_EMSCRIPTEN)
	add_definitions(-sUSE_SDL=2)
endif()

string(TIMESTAMP CURRENTYEAR "%Y")

function (add_sample sample_dir)
	# create the test executable
	SET(APPNAME "RavEngine${sample_dir}")
	SET(sample_dir "${CMAKE_CURRENT_LIST_DIR}/Samples/${sample_dir}")

	# create the helper header file
	make_directory("${APPNAME}")
	configure_file("Samples/AppInfo.hpp" "${CMAKE_BINARY_DIR}/${APPNAME}/" @ONLY)
	configure_file("Samples/Sample.appxManifest" "${CMAKE_BINARY_DIR}/${APPNAME}" @ONLY)
	source_group("Resources" FILES "${CMAKE_BINARY_DIR}/${APPNAME}/Sample.appxManifest")

	file(GLOB TEST_SOURCES "${sample_dir}/*.cpp" "${sample_dir}/*.hpp" "${sample_dir}/*.h" "${CMAKE_BINARY_DIR}/${APPNAME}/*.hpp" )

	# creates a mac app if applicable
	add_executable("${APPNAME}" ${TEST_SOURCES} ${COMMON_FILES} "Samples/logo.png" "Samples/windows.rc" "Samples/iosLaunchScreen.storyboard" "${CMAKE_BINARY_DIR}/${APPNAME}/Sample.appxManifest")

	if(CMAKE_SYSTEM_NAME MATCHES "WindowsStore")
		target_sources("${APPNAME}" PRIVATE "Samples/logo44.png" "Samples/logo150.png" "Samples/logo50.png" "Samples/logo620x300.png")
	endif()
	
	target_include_directories("${APPNAME}" PUBLIC
        "${CMAKE_BINARY_DIR}/${APPNAME}"
        "${CMAKE_CURRENT_LIST_DIR}/Samples/Common"
    )
	target_compile_features(${APPNAME} PRIVATE cxx_std_20)
	set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/Samples/logo.png" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${APPNAME}")

	file(GLOB objects "${sample_dir}/objects/*.fbx" "${sample_dir}/objects/*.dae" "${sample_dir}/objects/*.ozz" "${sample_dir}/objects/*.obj" "${sample_dir}/objects/*.ply")
	file(GLOB textures "${sample_dir}/textures/*.jpg" "${sample_dir}/textures/*.png" "${sample_dir}/textures/*.svg" "${sample_dir}/textures/*.tiff")
	file(GLOB shaders "${sample_dir}/shaders/*.vsh" "${sample_dir}/shaders/*.csh" "${sample_dir}/shaders/*.fsh" "${sample_dir}/particles/*.csh")
	file(GLOB uis "${sample_dir}/ui/*.rml" "${sample_dir}/ui/*.rcss" "${sample_dir}/ui/*.png" "${sample_dir}/ui/*.json" "${sample_dir}/ui/*.ids")
	file(GLOB sounds "${sample_dir}/sounds/*.mp3" "${sample_dir}/sounds/*.wav" "${sample_dir}/sounds/*.ogg" "${sample_dir}/sounds/*.mid")
	file(GLOB_RECURSE streaming "${sample_dir}/streaming/*.ogg" "${sample_dir}/streaming/*.sfz")

	pack_resources(TARGET "${APPNAME}"
		OUTPUT_FILE DATA_PACK
		OBJECTS ${objects}
		SHADERS ${shaders}
		TEXTURES ${textures}
		UIS ${uis}
		SOUNDS ${sounds}
		STREAMING_ASSETS ${streaming}
		STREAMING_INPUT_ROOT "${sample_dir}/streaming/"
	)

	set_target_properties("${APPNAME}" 
		PROPERTIES 
		MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Samples/Info.plist.in"
		XCODE_ATTRIBUTE_BUNDLE_IDENTIFIER "com.ravbug.${APPNAME}"		# with templated plist we can set this
		XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.ravbug.${APPNAME}"
		XCODE_ATTRIBUTE_CURRENTYEAR "${CURRENTYEAR}"
		VS_GLOBAL_OutputType AppContainerExe
		VS_WINDOWS_TARGET_PLATFORM_VERSION "10.0.19041.0"				# be runnable on Windows 10
		VS_WINDOWS_TARGET_PLATFORM_MIN_VERSION "10.0.19041.0"
	)

	rve_enable_IPO(${APPNAME})


	if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
		if (EXISTS "${sample_dir}/streaming/")
			set(EM_PRELOAD "--preload-file \"${sample_dir}/streaming/@${APPNAME}_Streaming/\"")
		endif()
		get_filename_component(packname "${DATA_PACK}" NAME)

		set(EM_LINK "--preload-file ${DATA_PACK}@${packname}"
					${EM_PRELOAD}
					"-s MAX_WEBGL_VERSION=2" 
					"-s MIN_WEBGL_VERSION=2" 
					"-s FULL_ES3=1" 
					"-s USE_WEBGPU" 
					"-s GL_ASSERTIONS=1" 
					"-s OFFSCREEN_FRAMEBUFFER=1" 
					"-s OFFSCREENCANVAS_SUPPORT=1" 
					"-s GL_DEBUG=1" 
					"-fexceptions" 
					"-s PROXY_TO_PTHREAD" 
					"-s USE_PTHREADS" 
					"-s LLD_REPORT_UNDEFINED" 
					"-s NO_DISABLE_EXCEPTION_CATCHING" 
					"-s NO_DISABLE_EXCEPTION_THROWING" 
					"-s PTHREAD_POOL_SIZE=4" 
					"-s ASSERTIONS=1" 
					"-s ALLOW_MEMORY_GROWTH=1" 
					"-s MAXIMUM_MEMORY=4GB"
					"-s USE_SDL=2"
					"-s WASM_BIGINT"
					"-s TOTAL_MEMORY=150MB"
				)
	endif()

	target_link_libraries("${APPNAME}" PUBLIC "RavEngine" ${atomic_lib} ${EM_LINK})

	# fixup mac bundle, or generate Linux AppImage
	if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
		target_compile_options("${APPNAME}" PUBLIC -ftemplate-backtrace-limit=0)	# clang arg to facilitate template debugging
		INSTALL(CODE 
			"include(BundleUtilities)
			fixup_bundle(\"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.app\" \"\" \"\")
			" 
			COMPONENT Runtime
		)
    elseif(LINUX AND NOT TARGET_EMSCRIPTEN)
        if(CMAKE_BUILD_TYPE STREQUAL Release)
        	if (NOT DEFINED CMAKE_SYSTEM_PROCESSOR)
        		set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR} CACHE INTERNAL "")
        	endif()
        	if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR})
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
                    OUTPUT_ARCH \"${CMAKE_SYSTEM_PROCESSOR}\"
                    CROSSCOMP ${IS_CROSSCOMP}
                    ASSETS \"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}.rvedata\" \"${CMAKE_INSTALL_PREFIX}/$<CONFIGURATION>/${APPNAME}Streaming/\"
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
add_sample("Perf_ECS")
add_sample("Perf_Draw")
add_sample("Perf_DrawAnimated")
add_sample("Perf_RigidBodies")
add_sample("Perf_Network")
add_sample("Perf_Lighting")
add_sample("GUI")
add_sample("Flags")
add_sample("Navigation")
add_sample("Gravity")
add_sample("SystemInfo")
add_sample("VR")
add_sample("Shadows")
add_sample("Occlusion")
add_sample("Transforms")
add_sample("Rendering")
add_sample("SoundDynamics")
add_sample("SceneViewer")
add_sample("Rats")
