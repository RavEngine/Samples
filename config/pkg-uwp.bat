@echo OFF
cd ..
mkdir build
cd build
mkdir uwp
cd uwp
cmake -G "Visual Studio 16 2019" -Ax64 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION="10.0" -DCMAKE_BUILD_TYPE=Release -Wno-dev ..\..
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSbuild.exe" "RavEngine_Samples.sln" /p:Configuration=Release;AppxBundle=Always;AppxBundlePlatforms="x64"
cd ..\..
