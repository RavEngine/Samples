#!/bin/sh

./init-linux.sh
cd build;
cmake --build . --config release --target RavEngine_Sample_AirHockey RavEngine_Sample_Playground RavEngine_Samples_TestBasics
