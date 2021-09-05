# RavEngine Samples

This repository contains sample programs to demonstrate how to use the [RavEngine C++ game library](https://github.com/Ravbug/RavEngine).

## Samples
1. Hello Cube
   - A getting started guide for using RavEngine
1. AirHockey
   - A simple air hockey game demonstrating RavEngine fundamentals (WIP)
1. Playground
   - A testing zone, subject to change
1. Perf-ECS
   - ECS raw number crunching benchmark
1. Perf-Draw
   - autobatched instancing benchmark
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

## How to try the samples without building
1. Sign in to GitHub in your browser. This is required for accessing the downloads.
2. Go to [Actions->Build Samples](https://github.com/Ravbug/RavEngine-Samples/actions/workflows/build.yml) on this repository
3. Find the latest run that has a build for your platform (check the failed runs as well) 
4. Download the Artifact for your platform

## How to build the samples
1. Ensure RavEngine [supports your platform](https://github.com/ravbug/ravengine#supported-platforms).
2. Ensure you have the minimum required CMake version (see `CMakeLists.txt`), as well as a C++17-compatible compiler and required SDKs for your platform. See the RavEngine repository for [additional dependency requirements](https://github.com/ravbug/ravengine#supported-platforms) for your platform.  
3. Execute in terminal: `git clone https://github.com/Ravbug/RavEngine-Samples --depth=1 --recurse-submodules` 
   - Do not use GitHub's Download as Zip, this will not include the required submodules.
4. Navigate your terminal into the `RavEngine-Samples/config` directory, and execute the build script for your system.
   - macOS: `./build-mac.sh`
   - Windows: `build-win.bat`
   - Linux: `./build-linux.sh`
   - iOS (device): `./init-ios.sh`   (project gen only, open Xcode for code signing)
   - tvOS (device): `./init-tvos.sh` (project gen only, open Xcode for code signing)
   - UWP: `./init-uwp.bat` (project gen only, use Publish in Visual Studio to generate MSIX installers)
5. Navigate your terminal to the `build/release` directory, and run the samples.
