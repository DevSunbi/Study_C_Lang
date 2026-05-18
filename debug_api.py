import requests, os, json, time, re
from pathlib import Path

import sys
if sys.stdout.encoding and sys.stdout.encoding.lower() not in ('utf-8','utf8'):
    import io
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')

# 브라우저에서 캡처한 전체 쿠키 문자열 사용
FULL_COOKIE = "_ga=GA1.1.1263454724.1777189489; theme=light; access_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VyX2lkIjoiMDc3OTkwYTUtMzYyMi00ZDcxLTljMDYtMTkzNzEwZmVkMzViIiwiaWF0IjoxNzc3MTg5NDQwLCJleHAiOjE3NzcxOTMwNDAsImlzcyI6InZlbG9nLmlvIiwic3ViIjoiYWNjZXNzX3Rva2VuIn0.GKommEJctzIOTTjRQimZE22ixsWuBPK5cq8I3KVDKYI; _sharedID=f4455a65-02ba-4804-95eb-cd97231a259d; _sharedID_cst=zix7LPQsHA%3D%3D; _pubcid=73490113-cab3-41e8-9820-267eea2a0944"

MD_DIR = Path("MD")
LOG_FILE = Path("velog_upload_log.json")
VELOG_GQL = "https://api.velog.io/graphql"

DAY_META = {
    1:  {"topic": "C언어 기초 & 입출력",              "tags": ["C언어","기초문법","입출력"]},
    2:  {"topic": "함수 & 배열",                    "tags": ["C언어","함수","배열"]},
    3:  {"topic": "포인터 기초",                    "tags": ["C언어","포인터","메모리"]},
    4:  {"topic": "포인터 심화 & 문자열",              "tags": ["C언어","포인터","문자열"]},
    5:  {"topic": "아스키코드 & 다차원 배열",            "tags": ["C언어","배열","아스키코드"]},
    6:  {"topic": "문자열 함수 & 변수 영역",            "tags": ["C언어","문자열","변수영역","static"]},
    7:  {"topic": "이중 포인터 & 동적 할당",            "tags": ["C언어","이중포인터","동적할당","malloc"]},
    8:  {"topic": "구조체 & C++ 입문",               "tags": ["C언어","구조체","C++","cin","cout"]},
    9:  {"topic": "C++ 심화 & OOP 입문",             "tags": ["C++","레퍼런스","예외처리","OOP"]},
    10: {"topic": "객체지향 프로그래밍",               "tags": ["C++","OOP","클래스","캡슐화","상속"]},
    11: {"topic": "상속과 다형성",                   "tags": ["C++","상속","다형성","가상함수","virtual"]},
    12: {"topic": "복사 생성자 & 정적 멤버",            "tags": ["C++","복사생성자","static","깊은복사"]},
    13: {"topic": "템플릿 & 표준 라이브러리",           "tags": ["C++","Template","STL","string"]},
    14: {"topic": "STL 컨테이너 & 알고리즘",           "tags": ["C++","STL","vector","map","iterator"]},
    16: {"topic": "Qt 입문 & 기초",                 "tags": ["Qt","GUI","Signal","Slot","QMainWindow"]},
    17: {"topic": "Qt 위젯 & 디자이너",              "tags": ["Qt","QCheckBox","QComboBox","Designer"]},
    18: {"topic": "Qt 레이아웃 & 데이터 타입",         "tags": ["Qt","Layout","QString","QMap"]},
    19: {"topic": "Qt Signal/Slot 심화 & Dialog",   "tags": ["Qt","Signal","Slot","QDialog"]},
    20: {"topic": "QMainWindow & Model/View & QPainter","tags":["Qt","MVC","QPainter","ModelView"]},
    21: {"topic": "Thread Programming",             "tags": ["멀티스레드","Thread","Mutex","DeadLock"]},
    22: {"topic": "Qt 계좌 관리 프로그램",             "tags": ["Qt","C++","계좌관리"]},
    24: {"topic": "임베디드 기초 & MCU HW",           "tags": ["임베디드","MCU","ARM","RISC","인터럽트"]},
    25: {"topic": "크로스 개발환경 & ARM ASM",         "tags": ["임베디드","ARM","어셈블리","ASM","크로스컴파일"]},
}
COMMON_TAGS = ["VEDA","개발공부","강의노트"]

def make_headers():
    return {
        "Content-Type": "application/json",
        "Cookie": FULL_COOKIE,
        "Origin": "https://velog.io",
        "Referer": "https://velog.io/write",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/124.0 Safari/537.36",
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

def read_and_clean(day_num, day_dir):
    parts = []
    for fname, header in [(f"Day {day_num}.md",""), ("CodeBase.md","## 코드베이스"), ("QnA.md","## Q&A")]:
        fp = day_dir / fname
        if fp.exists():
            txt = fp.read_text(encoding="utf-8").strip()
            if txt:
                parts.append(f"\n{header}\n\n{txt}" if header else txt)
    content = "\n\n---\n\n".join(parts)
    content = re.sub(r'!\[\[[^\]]+\.(?:png|jpg|jpeg|gif|webp)(?:\|[^\]]+)?\]\]', '', content, flags=re.IGNORECASE)
    content = re.sub(r'\[\[([^\]]+)\]\]', r'\1', content)
    return content.strip()

def load_log():
    if LOG_FILE.exists():
        return json.loads(LOG_FILE.read_text(encoding="utf-8"))
    return {}

def save_log(log):
    LOG_FILE.write_text(json.dumps(log, ensure_ascii=False, indent=2), encoding="utf-8")

MUTATION = """
mutation WritePost($title:String,$body:String,$tags:[String],$is_markdown:Boolean,$is_temp:Boolean,$is_private:Boolean,$url_slug:String){
  writePost(title:$title,body:$body,tags:$tags,is_markdown:$is_markdown,is_temp:$is_temp,is_private:$is_private,url_slug:$url_slug){
    id title url_slug
    user { username }
  }
}
"""

def upload_post(variables):
    try:
        r = requests.post(VELOG_GQL, json={"query": MUTATION, "variables": variables},
                          headers=make_headers(), timeout=30)
        r.raise_for_status()
        data = r.json()
        if "errors" in data:
            print(f"    GraphQL 오류: {data['errors'][0].get('message','')}")
            return None
        result = data.get("data", {}).get("writePost")
        if result is None:
            print(f"    [!] null 반환")
        return result
    except Exception as e:
        print(f"    오류: {e}")
        return None

print("="*50)
print("  VEDA Velog 업로드 (전체쿠키 모드)")
print("="*50)

upload_log = load_log()
day_dirs = find_day_dirs()
success, fail, skip = [], [], []

for day_num, day_dir in day_dirs:
    print(f"--- Day {day_num} ---")
    log_key = f"day_{day_num}"
    if log_key in upload_log:
        print(f"  [SKIP] {upload_log[log_key].get('url','')}")
        skip.append(day_num)
        continue

    content = read_and_clean(day_num, day_dir)
    if not content:
        print(f"  [SKIP] 내용없음")
        fail.append(day_num)
        continue

    meta = DAY_META.get(day_num, {"topic": f"Day {day_num}", "tags": []})
    title = f"[VEDA] Day {day_num} - {meta['topic']}"
    week_num = (day_num - 1) // 5 + 1
    header = f"# [VEDA] Day {day_num} - {meta['topic']}\n\n> Week {week_num} | VEDA C언어/임베디드 강의 노트\n\n---\n\n"

    variables = {
        "title": title,
        "body": header + content,
        "tags": COMMON_TAGS + meta["tags"],
        "is_markdown": True,
        "is_temp": False,
        "is_private": False,
        "url_slug": f"veda-day-{day_num}",
    }

    print(f"  업로드: {title}")
    result = upload_post(variables)

    if result and result.get("id"):
        username = result.get("user", {}).get("username", "unknown")
        url = f"https://velog.io/@{username}/{result['url_slug']}"
        print(f"  [OK] {url}")
        upload_log[log_key] = {"day": day_num, "title": title, "url": url,
                                "uploaded_at": time.strftime("%Y-%m-%dT%H:%M:%S")}
        save_log(upload_log)
        success.append(day_num)
    else:
        fail.append(day_num)

    time.sleep(1.0)

print(f"\n{'='*50}")
print(f"성공: {len(success)} -> {success}")
print(f"실패: {len(fail)} -> {fail}")
print(f"건너뜀: {len(skip)}")
