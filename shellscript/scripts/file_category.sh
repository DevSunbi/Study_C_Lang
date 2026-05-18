#!/bin/bash

mkdir txt log scripts

for file in *; do
   case "$file" in
	   *.txt)
		   mv "$file" txt/
		   ;;
	   *.log)
		   mv "$file" log/
		   ;;
	   *.sh)
		   mv "$file" scripts/
		   ;;
    esac
done
