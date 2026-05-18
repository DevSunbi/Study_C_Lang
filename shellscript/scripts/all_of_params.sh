#!/bin/bash

echo "total number of params: $#"
echo "\$* is '$*'"
echo "\$@ is '$@'"


echo "1st result of $*"
for param in "$*"
do
	echo "\$*'s param: $param"
done

echo "2nd result of $@"
for param in "$@"
do
	echo "\$@'s param: $param"
done

