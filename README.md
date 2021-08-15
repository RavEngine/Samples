# RavEngine Samples

This repository contains sample programs to demonstrate how to use the [RavEngine C++ game library](https://github.com/Ravbug/RavEngine).

## Samples
1. AirHockey
   - A simple air hockey game demonstrating RavEngine fundamentals (WIP)
2. Playground
   - A testing zone, subject to change
3. Perf-ECS
   - ECS raw number crunching benchmark
4. Perf-Draw
   - autobatched instancing benchmark
5. Perf-DrawAnimated
   - A stress test for high object count with animated lights
6. Perf-Network
   - A networking stress test. Contains both the server and client code in the same target. Launch with no arguments for client, and any argument for server
7. Perf-Lighting
   - GPU-centric lighting and materials performance test with high-polygon models
8. GUI
   - A demonstration of all the different supported GUI widgets
9. Animation
   - Demonstrates the skinned mesh blending capabilities of RavEngine

## How to build
1. Ensure RavEngine supports your platform.
2. Ensure you have the minimum required CMake version (see `CMakeLists.txt`), as well as a C++17-compatible compiler (clang++), and required SDKs for your platform. See the RavEngine repository for additional software requirements.  
3. Execute in terminal: `git clone https://github.com/Ravbug/RavEngine-Samples --depth=1 --recurse-submodules` 
   - Do not use GitHub's Download as Zip, this will not include the required submodules.
4. Navigate your terminal into the `RavEngine-Samples/config` directory, and execute the build script for your system.
   - macOS: `./build-mac.sh`
   - Windows: `build-win.bat`
   - Linux: `./build-linux.sh`
   - iOS (device): `./init-ios.sh`   (project gen only, open Xcode for code signing)
   - tvOS (device): `./init-tvos.sh` (project gen only, open Xcode for code signing)
5. Navigate your terminal to the `build/release` directory, and run the samples.
