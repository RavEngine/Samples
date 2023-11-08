cmake_minimum_required(VERSION 3.16)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR} CACHE INTERNAL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_XCODE_ATTRIBUTE_EXCLUDED_ARCHS[sdk=iphonesimulator*] "arm64" CACHE INTERNAL "")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")    # disable codesign requirement
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
        "lib/sfizz/external/abseil-cpp/"
        "lib/sfizz/external/simde/"
        "lib/sfizz/external/filesystem/include/"
    )
	target_compile_features(${APPNAME} PRIVATE cxx_std_20)
	set_source_files_properties("${CMAKE_CURRENT_LIST_DIR}/Samples/logo.png" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "${APPNAME}")

	file(GLOB objects "${sample_dir}/objects/*.fbx" "${sample_dir}/objects/*.dae" "${sample_dir}/objects/*.ozz" "${sample_dir}/objects/*.obj" "${sample_dir}/objects/*.ply")
	file(GLOB textures "${sample_dir}/textures/*.jpg" "${sample_dir}/textures/*.png" "${sample_dir}/textures/*.svg")
	file(GLOB shaders "${sample_dir}/shaders/*.vsh" "${sample_dir}/shaders/*.csh" "${sample_dir}/shaders/*.fsh")
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
    elseif(TARGET_LINUX AND NOT TARGET_EMSCRIPTEN)
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

# sfizz
set(BUILD_TESTING OFF CACHE INTERNAL "")
set(SFIZZ_JACK OFF CACHE INTERNAL "")
set(SFIZZ_LV2 OFF CACHE INTERNAL "")
set(SFIZZ_LV2_UI OFF CACHE INTERNAL "")
set(SFIZZ_VST OFF CACHE INTERNAL "")
set(SFIZZ_AU OFF CACHE INTERNAL "")
set(SFIZZ_SHARED OFF CACHE INTERNAL "")
set(ENABLE_LTO OFF CACHE INTERNAL "")
set(SFIZZ_RENDER OFF CACHE INTERNAL "")
set(SFIZZ_STATIC_DEPENDENCIES OFF CACHE INTERNAL "")
add_subdirectory("lib/sfizz" EXCLUDE_FROM_ALL)

add_subdirectory("lib/midifile" EXCLUDE_FROM_ALL)


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

group_in("SamplesDeps/sfizz" "aiff;sfizz_pugixml;sfizz_spline;sfizz_tunings;sfizz_hiir_polyphase_iir2designer;sfizz_kissfft;sfizz_cephes;sfizz_cpuid;sfizz_filesystem_impl;sfizz_fmidi;\
st_audiofile;st_audiofile_formats;st_info;sfizz_parser;sfizz_messaging;sfizz_import;sfizz_spin_mutex;sfizz_internal;sfizz_match_definitions;sfizz_static;\
sfizz-generate-git-build-id;sfizz-git-build-id;Abseil")

group_in("SamplesDeps/Abseil" "absl_base;absl_raw_hash_set;absl_stacktrace;absl_symbolize;absl_failure_signal_handler;absl_demangle_internal;absl_leak_check;\
absl_leak_check_disable;absl_flags_program_name;absl_flags_internal;absl_hash;absl_int128;absl_status;absl_statusor;absl_strings;absl_cord;absl_synchronization;\
absl_time;absl_bad_optional_access;absl_bad_variant_access")

group_in("SamplesDeps/Abseil/internal" "absl_log_severity;absl_raw_logging_internal;absl_spinlock_wait;absl_malloc_internal;absl_throw_delegate;absl_scoped_set_env;\
absl_strerror;absl_hashtablez_sampler;absl_examine_stack;absl_debugging_internal;absl_flags_config;absl_flags_marshalling;absl_flags_commandlineflag_internal;\
absl_flags_commandlineflag;absl_flags_private_handle_accessor;absl_flags_reflection;absl_flags;absl_flags_usage_internal;absl_flags_usage;absl_flags_parse;\
absl_city;absl_low_level_hash;absl_exponential_biased;absl_periodic_sampler;absl_random_distributions;absl_random_seed_gen_exception;absl_random_seed_sequences;\
absl_random_internal_seed_material;absl_random_internal_pool_urbg;absl_random_internal_platform;absl_random_internal_randen;absl_random_internal_randen_slow;\
absl_random_internal_randen_hwaes;absl_random_internal_randen_hwaes_impl;absl_random_internal_distribution_test_util;absl_strings_internal;absl_str_format_internal;\
absl_cord_internal;absl_cordz_functions;absl_cordz_handle;absl_cordz_info;absl_cordz_sample_token;absl_graphcycles_internal;absl_civil_time;absl_time_zone;absl_bad_any_cast_impl")

group_in("SamplesDeps", "midifile;nfd")

add_sample("SoundDynamics")
target_link_libraries("RavEngineSoundDynamics" PUBLIC
	"sfizz_static"
	"sfizz_fmidi"
	"midifile"
)
if(UWP)
	# WINNT version is messed up when compiling for UWP, fixes here
	foreach(tgt "sfizz_static" "sfizz_fmidi" "aiff" "sfizz_internal" )
		target_compile_definitions(${tgt} PUBLIC "_CRT_SECURE_NO_WARNINGS" "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS" "_CRT_NONSTDC_NO_DEPRECATE" )
	endforeach()
endif()

# exlcude the SceneViewer from iOS, tvOS, UWP, and ARM linux 
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
	if (NOT IS_CROSSCOMP)
		add_sample("SceneViewer")

		# SceneViewer needs some additional dependencies
		add_subdirectory(lib/nativefiledialog-extended EXCLUDE_FROM_ALL)
		target_link_libraries("RavEngineSceneViewer" PUBLIC nfd)
	endif()
endif()
