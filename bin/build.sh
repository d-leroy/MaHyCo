rm -rf build/*
cmake -DSCIHOOK_ENABLED=1 -DSCIHOOK_INSTALL_PREFIX=~/scihook/install -S . -B build
cmake --build build