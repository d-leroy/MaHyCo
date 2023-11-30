#!/bin/bash

if [ -z $1 ]; then
	echo "Usage: ./run.sh <path/to/build/dir>"
elif [ -d $1 ]; then
	ccc_mprun -p a100 -n 1 -c 32 $1/src/Mahyco -A,AcceleratorRuntime=cuda -A,MaxIteration=100 Data.arc
else
	echo "$1 does not exist or is not a directory"
fi
