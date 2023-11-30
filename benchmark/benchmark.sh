#!/bin/bash

benchmark_dir_path=$(dirname $(readlink -f $0))

if [ -z $1 ]; then
	echo "Usage: ./run.sh <path/to/build/dir>"
else
	build_dir_path=$(readlink -f "$1")
	if [ -d $build_dir_path ]; then
		for f in $benchmark_dir_path/*/run.sh; do
			cd $(dirname $f) ; ./run.sh $build_dir_path &
		done
	else
		echo "$1 does not exist or is not a directory"
	fi
fi
 
