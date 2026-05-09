1. 특정 확장자 파일 일괄 이름 변경
상황)
수백 개의 이미지 파일 확장자를 한꺼번에 바꿔야 합니다.
작업내용)
현재 디렉토리의 모든 .txt 파일을 .log 확장자로 변경합니다.
변경할 때마다 "Renaming file_a.txt to file_a.log"와 같이 진행 상황을 출력하세요.
파일명에 공백이 포함되어 있어도 오류 없이 작동해야 합니다.

```shell
❯ cat change_file_name.sh
#!/bin/bash

for file in ./*txt
do
        old_name="${file#./}"
        new_file="${file%.txt}.log"
        new_name="${new_file#./}"

        echo "Renaming $old_name to $new_name"

        mv -- "$file" "$new_file"
done
```
```shell
for file in *.txt;
do
	new_name="${file%.txt}.log"
	echo "Renaming $file to $new_name"
	mv "$file" "$new_name"
```


2. 파일 용량 퍼센트 계산 및 조건문 (리소스 모니터링)
상황)
현재 디렉토리의 특정 파일이 전체 할당량(예: 1GB) 중 몇 퍼센트를 차지하는지 계산합니다. (du -s 와  awk '${print $1}' 사용)
파일 이름은 첫번째 인자로 전달됩니다.
인자 개수를 체크하여 1개가 아니면 사용법을 알려줍니다.
```bash
❯ cat file_usasge.sh
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
```
```shell
if [ $# -ne 1 ]; then
	echo "Usage: $0 filename"
	exit 1
fi

dir_size=$(du -sb | awk '{print $1}')
file_size=$(du -sb "$1"| awk '{print $1}')
usage_percent=$(( (file_size * 100) / dir_size))

echo "File $1 usage : ${usage_percent}% (${file_size}/${dir_Size})"

if((usage_percent >= 80)); then
	echo "Warning: Quota exceeded 80%!"
fi

```

3. 로그 파일 자동 압축 및 정리
상황 )
서버의 로그 폴더(/var/log/myapp/)에 파일이 계속 쌓여 용량이 부족해집니다.
작업내용)
	1) 수정된 지 7일 이상이며 크기가 100M 이상인 .log 파일을 찾습니다.    (find 명령  -mtime, -size 옵션 사용)
	2) 해당 파일들을 archive_날짜.tar.gz로 압축합니다.   (tar -cvzf 사용)
	3) 압축에 성공하면 원본 로그 파일들을 삭제합니다.
	4) 작업 결과를 /var/log/cleanup.log에 기록하세요.
```shell
❯ cat clean_log.sh
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
```
```shell

LOG_DIR="/home/sunbi/log/myapp"
ARCHIVE_NAME="archive $(date +%Y%m%d).tar.gz"
REPORT="/home/sunbi/log/cleanup.log"

FILES=$(find $LOG_DIR -name "*.log" -mtime +7 -size +100M)

if [ -n "$FILES" ]; then
	tar -czf "$LOG_DIR/$ARCHIVE_NAME" $FILES
	if[ $? -eq 0 ]; then
		rm $FILES
		echo "[$(date)] Success: Archived and removed lod logs." >> $REPROT
	else
		echo "[$(date)] Error: Compression failed." >> $REPORT
	fi
else
	echo "[$(date)] No files to cleanup." >> $REPORT
fi 
```