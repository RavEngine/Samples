# RavEngine Samples

This repository contains sample programs to demonstrate how to use the [RavEngine C++ game library](https://github.com/RavEngine/RavEngine).

## Samples
1. AirHockey
   - A simple air hockey game demonstrating RavEngine fundamentals (WIP)
1. Playground
   - A testing zone, subject to change
1. Perf-ECS
   - ECS raw number crunching benchmark
1. Perf-Draw
   - InstancedStaticMesh demo
1. Perf-DrawAnimated
   - A stress test for high object count with animated lights
1. Perf-Network
   - A networking stress test. Contains both the server and client code in the same target. Launch with no arguments for client, and any argument for server
1. Perf-Lighting
   - GPU-centric lighting and materials performance test with high-polygon models
1. GUI
   - A demonstration of all the different supported GUI widgets
1. Animation
   - Demonstrates the skinned mesh blending capabilities of RavEngine
1. SoundDynamics
   - A virtual soundstage demonstrating the audio reverbation modeling feature 
1. Flags
   - Mixing skeletal and vertex animation, along using vector graphics on textures
1. Gravity
   - Creating orbits using PhysX forces
1. Navigation
   - Raycasting and pathfinding across 3D terrain
1. Occlusion
   - Test case for dynamic occlusion culling
1. Rendering
   - Demonstrate the various features of the render engine 

## How to try the samples without building
1. Sign in to GitHub in your browser. This is required for accessing the downloads.
2. Go to [Actions > Build Samples](https://github.com/RavEngine/Samples/actions/workflows/build.yml) on this repository
3. Find the latest run that has a build for your platform (check the failed runs as well) 
4. Download the Artifact for your platform

## How to build the samples
1. Ensure RavEngine [supports your platform](https://github.com/ravengine/ravengine#supported-platforms).
2. Ensure you have the minimum required CMake version (see `CMakeLists.txt`), as well as a C++20-compatible compiler and required SDKs for your platform. See the RavEngine repository for [additional dependency requirements](https://github.com/ravbug/ravengine#supported-platforms) for your platform.  
3. Execute in terminal: `git clone https://github.com/RavEngine/Samples --depth=1 --recurse-submodules` 
   - Do not use GitHub's Download as Zip, this will not include the required submodules.
4. Navigate your terminal into the `config` directory, and execute the build script for your system.
   - macOS: `./build-mac.sh`
   - Windows: `build-win.bat`
      - Note: Due to a known bug in the Windows configure process, you will need to execute this script twice to build successfully. 
   - Linux: `./build-linux.sh`
   - iOS (device): `./init-ios.sh`   (project gen only, open Xcode for code signing)
   - tvOS (device): `./init-tvos.sh` (project gen only, open Xcode for code signing)
   - UWP: `./init-uwp.bat` (project gen only, use Publish in Visual Studio to generate MSIX installers)
5. Navigate your terminal to the `build/release` directory, and run the samples.
