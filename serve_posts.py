#!/usr/bin/env python3
"""
posts_content.json 생성 + 로컬 HTTP 서버 시작
브라우저에서 fetch('http://localhost:8000/posts_content.json')으로 내용을 가져와
updatePost 뮤테이션 실행 가능
"""
import re, json, http.server, threading
from pathlib import Path

import sys
if sys.stdout.encoding and sys.stdout.encoding.lower() not in ('utf-8','utf8'):
    import io
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

MD_DIR = Path("MD")

DAY_META = {
    1:  {"topic": "C언어 기초 & 입출력",              "tags": ["VEDA","개발공부","강의노트","C언어","기초문법","입출력"]},
    2:  {"topic": "함수 & 배열",                    "tags": ["VEDA","개발공부","강의노트","C언어","함수","배열"]},
    3:  {"topic": "포인터 기초",                    "tags": ["VEDA","개발공부","강의노트","C언어","포인터","메모리"]},
    4:  {"topic": "포인터 심화 & 문자열",              "tags": ["VEDA","개발공부","강의노트","C언어","포인터","문자열"]},
    5:  {"topic": "아스키코드 & 다차원 배열",            "tags": ["VEDA","개발공부","강의노트","C언어","배열","아스키코드"]},
    6:  {"topic": "문자열 함수 & 변수 영역",            "tags": ["VEDA","개발공부","강의노트","C언어","문자열","변수영역","static"]},
    7:  {"topic": "이중 포인터 & 동적 할당",            "tags": ["VEDA","개발공부","강의노트","C언어","이중포인터","동적할당","malloc"]},
    8:  {"topic": "구조체 & C++ 입문",               "tags": ["VEDA","개발공부","강의노트","C언어","구조체","C++","cin","cout"]},
    9:  {"topic": "C++ 심화 & OOP 입문",             "tags": ["VEDA","개발공부","강의노트","C++","레퍼런스","예외처리","OOP"]},
    10: {"topic": "객체지향 프로그래밍",               "tags": ["VEDA","개발공부","강의노트","C++","OOP","클래스","캡슐화","상속"]},
    11: {"topic": "상속과 다형성",                   "tags": ["VEDA","개발공부","강의노트","C++","상속","다형성","가상함수","virtual"]},
    12: {"topic": "복사 생성자 & 정적 멤버",            "tags": ["VEDA","개발공부","강의노트","C++","복사생성자","static","깊은복사"]},
    13: {"topic": "템플릿 & 표준 라이브러리",           "tags": ["VEDA","개발공부","강의노트","C++","Template","STL","string"]},
    14: {"topic": "STL 컨테이너 & 알고리즘",           "tags": ["VEDA","개발공부","강의노트","C++","STL","vector","map","iterator"]},
    16: {"topic": "Qt 입문 & 기초",                 "tags": ["VEDA","개발공부","강의노트","Qt","GUI","Signal","Slot","QMainWindow"]},
    17: {"topic": "Qt 위젯 & 디자이너",              "tags": ["VEDA","개발공부","강의노트","Qt","QCheckBox","QComboBox","Designer"]},
    18: {"topic": "Qt 레이아웃 & 데이터 타입",         "tags": ["VEDA","개발공부","강의노트","Qt","Layout","QString","QMap"]},
    19: {"topic": "Qt Signal/Slot 심화 & Dialog",   "tags": ["VEDA","개발공부","강의노트","Qt","Signal","Slot","QDialog"]},
    20: {"topic": "QMainWindow & Model/View & QPainter","tags":["VEDA","개발공부","강의노트","Qt","MVC","QPainter","ModelView"]},
    21: {"topic": "Thread Programming",             "tags": ["VEDA","개발공부","강의노트","멀티스레드","Thread","Mutex","DeadLock"]},
    22: {"topic": "Qt 계좌 관리 프로그램",             "tags": ["VEDA","개발공부","강의노트","Qt","C++","계좌관리"]},
    24: {"topic": "임베디드 기초 & MCU HW",           "tags": ["VEDA","개발공부","강의노트","임베디드","MCU","ARM","RISC","인터럽트"]},
    25: {"topic": "크로스 개발환경 & ARM ASM",         "tags": ["VEDA","개발공부","강의노트","임베디드","ARM","어셈블리","ASM","크로스컴파일"]},
}

def find_day_dirs():
    days = []
    for week_dir in sorted(MD_DIR.iterdir()):
        if not week_dir.is_dir() or not week_dir.name.startswith("Week"):
            continue
        for day_dir in sorted(week_dir.iterdir()):
            if not day_dir.is_dir():
                continue
            m = re.match(r"Day\s+(\d+)$", day_dir.name)
            if m:
                days.append((int(m.group(1)), day_dir))
    return sorted(days, key=lambda x: x[0])

def clean(text):
    # Obsidian 이미지 링크 제거
    text = re.sub(r'!\[\[[^\]]+\.(?:png|jpg|jpeg|gif|webp)(?:\|[^\]]+)?\]\]', '', text, flags=re.IGNORECASE)
    # Obsidian 내부 링크 → 텍스트
    text = re.sub(r'\[\[([^\]]+)\]\]', r'\1', text)
    return text.strip()

def read_day(day_num, day_dir):
    parts = []
    for fname, header in [(f"Day {day_num}.md",""), ("CodeBase.md","## 📝 코드베이스"), ("QnA.md","## ❓ Q&A")]:
        fp = day_dir / fname
        if fp.exists():
            txt = fp.read_text(encoding="utf-8").strip()
            if txt:
                parts.append(f"\n{header}\n\n{clean(txt)}" if header else clean(txt))
    return "\n\n---\n\n".join(parts)

# 포스트 데이터 생성
posts = []
for day_num, day_dir in find_day_dirs():
    meta = DAY_META.get(day_num, {"topic": f"Day {day_num}", "tags": ["VEDA"]})
    week_num = (day_num - 1) // 5 + 1
    content = read_day(day_num, day_dir)
    
    header = f"# [VEDA] Day {day_num} - {meta['topic']}\n\n"
    header += f"> 📅 **Week {week_num}** | VEDA C언어/임베디드 교육과정 강의 노트\n\n---\n\n"
    body = header + content if content else header + "*(내용 준비 중)*"

    posts.append({
        "day": day_num,
        "slug": f"veda-day-{day_num}",
        "title": f"[VEDA] Day {day_num} - {meta['topic']}",
        "body": body,
        "tags": meta["tags"],
    })
    print(f"  Day {day_num}: {len(body)} chars")

# JSON 저장
out = Path("posts_content.json")
out.write_text(json.dumps(posts, ensure_ascii=False, indent=2), encoding="utf-8")
print(f"\n[OK] posts_content.json 생성 완료: {len(posts)}개 포스트")

# CORS 허용 HTTP 서버 시작
class CORSHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Headers", "*")
        super().end_headers()
    def log_message(self, fmt, *args):
        pass  # 로그 억제

PORT = 8000
server = http.server.HTTPServer(("", PORT), CORSHandler)
print(f"[HTTP] http://localhost:{PORT}/posts_content.json 서버 시작")
print("브라우저에서 fetch로 접근 가능합니다. Ctrl+C로 종료.")
server.serve_forever()
