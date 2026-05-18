#!/bin/bash

for i in $(seq 2 1 9) # for ((base=2;base<=9;base++))
do
	for j in $(seq 1 1 9) # for((mult=1;mult<=0;mult++)) for mult in {1..9..1}
	do
		#"$i * $j = $(expr $i \* $j)" expr을 사용한 old style 범용성 높은 표현
		echo "$i x $j = $((i*j))"
	done
done
