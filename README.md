# RavEngine Samples

This repository contains sample programs to demonstrate how to use the [RavEngine C++ game library](https://github.com/Ravbug/RavEngine).

## Samples
1. AirHockey
   - A simple air hockey game demonstrating RavEngine fundamentals (WIP)
2. Playground
   - A testing zone, subject to change

## How to build
1. Ensure RavEngine supports your platform.
2. Ensure you have the minimum required CMake version (see `CMakeLists.txt`), as well as a C++17-compatible compiler, and required graphics SDKs for your platform. 
3. Execute in terminal: `git clone https://github.com/Ravbug/RavEngine-Samples --depth=1 --recurse-submodules` 
   - Do not use GitHub's Download as Zip, this will not include the required submodules.
4. Navigate your terminal into the `RavEngine-Samples` directory, and execute the build script for your system.
   - macOS: `./build-mac.sh`
   - Windows: `build-win.bat`
   - Linux: `./build-linux.sh`
5. Navigate your terminal to the `build/release` directory, and run the samples.

Note: There are build scripts for Linux, but they currently do not work.
