#!/bin/bash

function make_a_pizza()
{
	echo "in fuction num of args: $#"
	echo "command: $0"
	echo "1st arg: $1"	
}

echo "first function example"
make_a_pizza "first args"
