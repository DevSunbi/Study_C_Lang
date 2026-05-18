#!/bin/bash

for file in ./*txt
do
	old_name="${file#./}"
	new_file="${file%.txt}.log"
	new_name="${new_file#./}"

	echo "Renaming $old_name to $new_name"

	mv -- "$file" "$new_file"
done
