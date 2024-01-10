#!/bin/bash
mpiexec -n 1 /home/leroyd/git/MaHyCoModane/build/src/Mahyco -arcane_opt max_iteration 10 -A,scihook_path=/home/leroyd/git/MaHyCoModane/python -A,scihook_script=instrumentation $1
