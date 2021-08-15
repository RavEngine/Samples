@echo OFF

init-win.bat && cd build\win && cmake --build . --config release --target install
