#!/bin/bash

exec >> "/var/log/cleanup.log" 2>&1

result=$(find /var/log/myapp -type f -name "*.log" -mtime +6 -size +99M)

if [ -n "$result" ]; then
	echo "Creating archive: old_large_logs.tar.gz"

	find /var/log/myapp -type f -name "*.log" -mtime +6 -size +99M | tar -czvf /var/log/old_large_logs.tar.gz --files-from=-
	if [ $? -eq 0 ]; then
		find /var/log/myapp -type f -name "*.log" -mtime +6 -size +99M -delete
	fi
else
	echo "No .log files older than 7 days and larger than 100MB"
fi
