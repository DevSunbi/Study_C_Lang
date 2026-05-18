#!/bin/bash

for ((i=0;i<5;i++)) #산술 평가 명령
do
	echo "loop index: $i"
done

for n in $(seq 1 2 10) # seq(시작값 증가값 종료값)
do
	echo "ranged: $n"
done
