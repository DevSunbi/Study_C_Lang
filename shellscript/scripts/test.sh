#!/bin/bash

echo "-------system information------"

echo "User: $(whoami)"
echo "Current Direcotry: $(pwd)"
echo "Date: $(date)"
echo "OS: $(uname -a)"

proc_count=$(ps -ef | wc -l)
echo "process count: ${proc_count}"
echo $num
