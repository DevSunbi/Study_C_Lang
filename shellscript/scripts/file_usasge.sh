#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <file_or_dir>"
	exit 1
fi

file_name=$1

if [ ! -e "$file_name" ]; then
	echo "Error : '$file_name' does not exist"
	exit 1
fi

total=$(du -s . | awk '{print $1}')
file_size=$(du -s -- "$file_name" | awk '{print $1}')

percent=$(( file_size * 100 / total))

echo "disk usage percent: ${percent}%"
