#!/bin/bash
mpiexec -n 1 /home/leroyd/git/MaHyCoModane/build/src/Mahyco -A,scihook_path=/home/leroyd/git/MaHyCoModane/python -A,scihook_script=instrumentation "$@"
