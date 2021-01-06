@echo OFF

init-win.bat && cd build && cmake --build . --config release --target RavEngine_Sample_AirHockey RavEngine_Sample_Playground RavEngine_Sample_Performance_C RavEngine_Samples_TestBasics
