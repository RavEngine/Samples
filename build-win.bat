@echo OFF

init-win.bat && cd build && cmake --build . --config release --target install
