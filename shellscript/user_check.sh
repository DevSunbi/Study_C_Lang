#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 username"
	exit 1
fi

user=$1

info=$(grep "^$user" /etc/passwd)

if [ -z "$info" ]; then
	echo "User not found"
else
	echo "user exists"
	echo $info
fi
