@echo OFF

init-winarm.bat && cd build\winarm && cmake --build . --config release --target install
PAUSE
