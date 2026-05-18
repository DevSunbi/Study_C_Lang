#!/usr/bin/env python3
"""
VEDA Velog Auto Uploader
========================
MD/Week*/Day */ 하위 강의 노트를 읽어 Velog에 Day 단위로 자동 업로드합니다.

사용법:
    python velog_uploader.py                  # 전체 Day 업로드
    python velog_uploader.py --day 1          # 특정 Day만 업로드
    python velog_uploader.py --dry-run        # 실제 업로드 없이 파싱 결과만 출력
    python velog_uploader.py --day 1 --series # 시리즈 포함 업로드

준비:
    1. pip install requests python-dotenv
    2. .env.velog 파일에 VELOG_ACCESS_TOKEN=<토큰> 입력
       (Velog 로그인 후 F12 → Application → Cookies → access_token)
"""

import os
import re
import sys
import json
import time
import argparse
import mimetypes
from pathlib import Path

# Windows PowerShell 인코딩 강제 UTF-8
if sys.stdout.encoding and sys.stdout.encoding.lower() not in ('utf-8', 'utf8'):
    import io
    sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
    sys.stderr = io.TextIOWrapper(sys.stderr.buffer, encoding='utf-8', errors='replace')

try:
    import requests
except ImportError:
    print("[ERROR] requests 패키지가 없습니다. 설치: pip install requests")
    sys.exit(1)

try:
    from dotenv import load_dotenv
    load_dotenv(".env.velog")
except ImportError:
    # python-dotenv 없어도 환경변수 직접 설정으로 대체 가능
    pass

# ─────────────────────────────────────────────
# 설정
# ─────────────────────────────────────────────
VELOG_GQL      = "https://api.velog.io/graphql"       # 실제 엔드포인트
VELOG_IMG_API  = "https://v2.velog.io/api/v2/files/upload"  # REST 이미지 업로드
BASE_DIR   = Path(__file__).parent
MD_DIR     = BASE_DIR / "MD"
IMG_DIR    = BASE_DIR          # Pasted image *.png 파일이 루트에 있음
LOG_FILE   = BASE_DIR / "velog_upload_log.json"

# Day별 주제 태그 매핑 (자동 추출 보완용)
DAY_META = {
    1:  {"topic": "C언어 기초 & 입출력",        "tags": ["C언어", "기초문법", "입출력"]},
    2:  {"topic": "함수 & 배열",               "tags": ["C언어", "함수", "배열"]},
    3:  {"topic": "포인터 기초",               "tags": ["C언어", "포인터", "메모리"]},
    4:  {"topic": "포인터 심화 & 문자열",        "tags": ["C언어", "포인터", "문자열"]},
    5:  {"topic": "아스키코드 & 다차원 배열",     "tags": ["C언어", "배열", "아스키코드"]},
    6:  {"topic": "문자열 함수 & 변수 영역",     "tags": ["C언어", "문자열", "변수영역", "static"]},
    7:  {"topic": "이중 포인터 & 동적 할당",     "tags": ["C언어", "이중포인터", "동적할당", "malloc"]},
    8:  {"topic": "구조체 & C++ 입문",         "tags": ["C언어", "구조체", "C++", "cin", "cout"]},
    9:  {"topic": "C++ 심화 & OOP 입문",       "tags": ["C++", "레퍼런스", "예외처리", "OOP"]},
    10: {"topic": "객체지향 프로그래밍",         "tags": ["C++", "OOP", "클래스", "캡슐화", "상속"]},
    11: {"topic": "상속과 다형성",             "tags": ["C++", "상속", "다형성", "가상함수", "virtual"]},
    12: {"topic": "복사 생성자 & 정적 멤버",    "tags": ["C++", "복사생성자", "static", "깊은복사"]},
    13: {"topic": "템플릿 & 표준 라이브러리",   "tags": ["C++", "Template", "STL", "string"]},
    14: {"topic": "STL 컨테이너 & 알고리즘",   "tags": ["C++", "STL", "vector", "map", "iterator"]},
    16: {"topic": "Qt 입문 & 기초",           "tags": ["Qt", "GUI", "Signal", "Slot", "QMainWindow"]},
    17: {"topic": "Qt 위젯 & 디자이너",       "tags": ["Qt", "QCheckBox", "QComboBox", "Designer"]},
    18: {"topic": "Qt 레이아웃 & 데이터 타입", "tags": ["Qt", "Layout", "QString", "QMap"]},
    19: {"topic": "Qt Signal/Slot 심화 & Dialog", "tags": ["Qt", "Signal", "Slot", "QDialog"]},
    20: {"topic": "QMainWindow & Model/View & QPainter", "tags": ["Qt", "MVC", "QPainter", "ModelView"]},
    21: {"topic": "Thread Programming",      "tags": ["멀티스레드", "Thread", "Mutex", "DeadLock"]},
    22: {"topic": "Qt 계좌 관리 프로그램",    "tags": ["Qt", "C++", "계좌관리"]},
    24: {"topic": "임베디드 기초 & MCU HW",  "tags": ["임베디드", "MCU", "ARM", "RISC", "인터럽트"]},
    25: {"topic": "크로스 개발환경 & ARM ASM","tags": ["임베디드", "ARM", "어셈블리", "ASM", "크로스컴파일"]},
}

COMMON_TAGS = ["VEDA", "개발공부", "강의노트"]

# ─────────────────────────────────────────────
# 인증
# ─────────────────────────────────────────────
def get_token() -> str:
    token = os.environ.get("VELOG_ACCESS_TOKEN", "").strip()
    if not token:
        print("\n[!] VELOG_ACCESS_TOKEN이 설정되지 않았습니다.")
        print("    Velog 로그인 → F12 → Application → Cookies → velog.io → access_token 복사")
        token = input("    access_token을 직접 입력하세요: ").strip()
    if not token:
        print("[ERROR] 토큰이 없으면 업로드할 수 없습니다.")
        sys.exit(1)
    return token

def make_headers(token: str) -> dict:
    return {
        "Content-Type": "application/json",
        "Cookie": f"access_token={token}",
        "Origin": "https://velog.io",
        "Referer": "https://velog.io/write",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/124.0 Safari/537.36",
    }

# ─────────────────────────────────────────────
# MD 파일 수집 및 파싱
# ─────────────────────────────────────────────
def find_day_dirs() -> list[tuple[int, Path]]:
    """MD/ 하위에서 Day 디렉토리를 찾아 (day_num, path) 목록 반환."""
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

def read_day_content(day_num: int, day_dir: Path) -> str:
    """Day 폴더의 md 파일들을 읽어 하나의 본문으로 합칩니다."""
    parts = []
    
    # 파일 우선순위 순서로 읽기
    file_order = [
        (f"Day {day_num}.md", ""),           # 메인 강의 노트 (섹션 헤더 없음)
        ("CodeBase.md", "## 📝 코드베이스"),  # 코드베이스
        ("QnA.md",      "## ❓ Q&A"),         # 질문과 답변
    ]
    
    for filename, section_header in file_order:
        fpath = day_dir / filename
        if fpath.exists():
            content = fpath.read_text(encoding="utf-8").strip()
            if content:
                if section_header:
                    parts.append(f"\n{section_header}\n\n{content}")
                else:
                    parts.append(content)
    
    return "\n\n---\n\n".join(parts)

# ─────────────────────────────────────────────
# Obsidian 문법 변환
# ─────────────────────────────────────────────
def extract_obsidian_images(content: str) -> list[str]:
    """![[Pasted image *.png]] 형태에서 이미지 파일명 추출."""
    # ![[파일명]] 또는 ![[파일명|크기]] 패턴 모두 처리
    return re.findall(r'!\[\[([^\]|]+\.(?:png|jpg|jpeg|gif|webp))(?:\|[^\]]+)?\]\]', content, re.IGNORECASE)

def remove_obsidian_images(content: str) -> str:
    """Obsidian 이미지 링크를 제거합니다 (이미지 업로드 실패 시 fallback)."""
    return re.sub(r'!\[\[[^\]]+\.(?:png|jpg|jpeg|gif|webp)(?:\|[^\]]+)?\]\]', '', content, flags=re.IGNORECASE)

def replace_obsidian_image(content: str, filename: str, cdn_url: str) -> str:
    """특정 이미지의 Obsidian 링크를 Markdown 이미지 링크로 교체."""
    # ![[파일명]] 과 ![[파일명|크기]] 패턴 모두 교체
    pattern = r'!\[\[' + re.escape(filename) + r'(?:\|[^\]]+)?\]\]'
    alt_text = Path(filename).stem
    replacement = f"![{alt_text}]({cdn_url})"
    return re.sub(pattern, replacement, content)

def convert_obsidian_links(content: str) -> str:
    """[[내부링크]] 형태를 텍스트로 변환."""
    return re.sub(r'\[\[([^\]]+)\]\]', r'\1', content)

# ─────────────────────────────────────────────
# 이미지 업로드 (createImageUploadUrl → S3 PUT)
# ─────────────────────────────────────────────
def upload_image(img_path: Path, token: str) -> str | None:
    """
    이미지를 Velog CDN에 업로드하고 최종 URL을 반환합니다.
    REST API: POST https://v2.velog.io/api/v2/files/upload (multipart/form-data)
    Response: { "path": "https://velog.velcdn.com/images/..." }
    """
    if not img_path.exists():
        print(f"    [WARN] 이미지 파일 없음: {img_path.name}")
        return None

    mime_type, _ = mimetypes.guess_type(str(img_path))
    mime_type = mime_type or "image/png"

    try:
        with open(img_path, "rb") as f:
            resp = requests.post(
                VELOG_IMG_API,
                files={"image": (img_path.name, f, mime_type)},
                headers={
                    "Cookie": f"access_token={token}",
                    "Origin": "https://velog.io",
                    "Referer": "https://velog.io/write",
                    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 Chrome/124.0 Safari/537.36",
                },
                timeout=60
            )
            resp.raise_for_status()
            data = resp.json()
            cdn_url = data.get("path")
            if cdn_url:
                print(f"    [OK] 이미지 업로드 완료: {img_path.name}")
                return cdn_url
            else:
                print(f"    [WARN] path 필드 없음: {data}")
                return None

    except requests.RequestException as e:
        print(f"    [WARN] 이미지 업로드 오류 ({img_path.name}): {e}")
        return None

# ─────────────────────────────────────────────
# 포스트 빌드
# ─────────────────────────────────────────────
def build_post(day_num: int, day_dir: Path, token: str, dry_run: bool = False) -> dict | None:
    """Day 폴더를 읽어 Velog 포스트 dict를 반환합니다."""
    raw_content = read_day_content(day_num, day_dir)
    if not raw_content.strip():
        print(f"  [SKIP] Day {day_num}: 내용이 없습니다.")
        return None

    # 이미지 처리
    image_filenames = extract_obsidian_images(raw_content)
    unique_images = list(dict.fromkeys(image_filenames))  # 순서 유지 중복 제거
    
    content = raw_content
    if unique_images:
        print(f"  이미지 {len(unique_images)}개 발견: {', '.join(unique_images[:3])}{'...' if len(unique_images) > 3 else ''}")
        
        if dry_run:
            content = remove_obsidian_images(content)
        else:
            for img_name in unique_images:
                img_path = IMG_DIR / img_name
                cdn_url = upload_image(img_path, token)
                if cdn_url:
                    content = replace_obsidian_image(content, img_name, cdn_url)
                else:
                    content = replace_obsidian_image(content, img_name, "")
                    content = re.sub(r'!\[\]\(\)', '', content)
                time.sleep(0.3)
    
    # 나머지 Obsidian 문법 변환
    content = convert_obsidian_links(content)
    content = content.strip()

    # 메타데이터 구성
    meta = DAY_META.get(day_num, {
        "topic": f"Day {day_num} 학습 내용",
        "tags": []
    })
    
    title    = f"[VEDA] Day {day_num} - {meta['topic']}"
    tags     = COMMON_TAGS + meta["tags"]
    url_slug = f"veda-day-{day_num}"
    
    # 헤더 추가 (포스트 상단 정보)
    week_num = (day_num - 1) // 5 + 1
    header = f"# [VEDA] Day {day_num} - {meta['topic']}\n\n"
    header += f"> 📅 **Week {week_num}** | VEDA C언어/임베디드 교육과정 강의 노트\n\n"
    header += "---\n\n"
    
    body = header + content

    return {
        "title": title,
        "body": body,
        "tags": tags,
        "is_markdown": True,
        "is_temp": False,
        "is_private": False,
        "url_slug": url_slug,
    }

# ─────────────────────────────────────────────
# Velog 포스트 업로드
# ─────────────────────────────────────────────
def write_post(post: dict, headers: dict) -> dict | None:
    """writePost GraphQL mutation 실행."""
    mutation = """
    mutation WritePost(
      $title: String
      $body: String
      $tags: [String]
      $is_markdown: Boolean
      $is_temp: Boolean
      $is_private: Boolean
      $url_slug: String
      $series_id: ID
    ) {
      writePost(
        title: $title
        body: $body
        tags: $tags
        is_markdown: $is_markdown
        is_temp: $is_temp
        is_private: $is_private
        url_slug: $url_slug
        series_id: $series_id
      ) {
        id
        title
        url_slug
        user { username }
      }
    }
    """
    payload = {"query": mutation, "variables": post}

    try:
        resp = requests.post(VELOG_GQL, json=payload, headers=headers, timeout=30)
        resp.raise_for_status()
        data = resp.json()

        if "errors" in data:
            err_msg = data["errors"][0].get("message", "알 수 없는 오류")
            print(f"    [ERROR] GraphQL 오류: {err_msg}")
            return None

        return data.get("data", {}).get("writePost")

    except requests.RequestException as e:
        print(f"    [ERROR] 네트워크 오류: {e}")
        return None

# ─────────────────────────────────────────────
# 시리즈 생성/조회
# ─────────────────────────────────────────────
def get_or_create_series(headers: dict, series_name: str = "VEDA 학습일지") -> str | None:
    """VEDA 시리즈를 생성하거나 기존 시리즈 ID를 반환합니다."""
    create_mutation = """
    mutation CreateSeries($name: String!, $url_slug: String!) {
      createSeries(name: $name, url_slug: $url_slug) {
        id
        name
      }
    }
    """
    payload = {
        "query": create_mutation,
        "variables": {"name": series_name, "url_slug": "veda-study-log"}
    }
    
    try:
        resp = requests.post(VELOG_GQL, json=payload, headers=headers, timeout=15)
        resp.raise_for_status()
        data = resp.json()
        
        if "errors" not in data and data.get("data", {}).get("createSeries"):
            series = data["data"]["createSeries"]
            print(f"  [OK] 시리즈 생성: {series['name']} (id: {series['id']})")
            return series["id"]
    except Exception as e:
        print(f"  [WARN] 시리즈 생성 실패: {e}")
    
    return None

# ─────────────────────────────────────────────
# 업로드 로그 관리
# ─────────────────────────────────────────────
def load_log() -> dict:
    if LOG_FILE.exists():
        try:
            return json.loads(LOG_FILE.read_text(encoding="utf-8"))
        except Exception:
            pass
    return {}

def save_log(log: dict):
    LOG_FILE.write_text(json.dumps(log, ensure_ascii=False, indent=2), encoding="utf-8")

# ─────────────────────────────────────────────
# 메인 실행
# ─────────────────────────────────────────────
def main():
    parser = argparse.ArgumentParser(description="VEDA Velog Auto Uploader")
    parser.add_argument("--day",     type=int, help="특정 Day만 업로드 (예: --day 1)")
    parser.add_argument("--series",  action="store_true", help="VEDA 시리즈로 묶어서 업로드")
    parser.add_argument("--dry-run", action="store_true", help="실제 업로드 없이 파싱 결과만 출력")
    parser.add_argument("--force",   action="store_true", help="이미 업로드된 Day도 다시 업로드")
    args = parser.parse_args()

    print("=" * 55)
    print("  VEDA Velog Auto Uploader")
    print("=" * 55)

    # 토큰 획득
    if args.dry_run:
        token = "dry-run-token"
        headers = {}
        print("[DRY-RUN 모드] 실제 업로드를 하지 않습니다.\n")
    else:
        token = get_token()
        headers = make_headers(token)

    # 시리즈 처리
    series_id = None
    if args.series and not args.dry_run:
        print("\n[시리즈] VEDA 시리즈 생성 중...")
        series_id = get_or_create_series(headers)

    # 업로드 로그 로드
    upload_log = load_log()

    # Day 디렉토리 탐색
    day_dirs = find_day_dirs()
    if not day_dirs:
        print(f"[ERROR] MD 디렉토리에서 Day 폴더를 찾을 수 없습니다: {MD_DIR}")
        sys.exit(1)

    # 특정 Day 필터
    if args.day:
        day_dirs = [(n, d) for n, d in day_dirs if n == args.day]
        if not day_dirs:
            print(f"[ERROR] Day {args.day}를 찾을 수 없습니다.")
            sys.exit(1)

    print(f"\n총 {len(day_dirs)}개 Day 처리 예정: {[n for n, _ in day_dirs]}\n")

    results = {"success": [], "skip": [], "fail": []}

    for day_num, day_dir in day_dirs:
        print(f"{'─'*45}")
        print(f"▶ Day {day_num} 처리 중... ({day_dir})")

        # 중복 업로드 방지
        log_key = f"day_{day_num}"
        if log_key in upload_log and not args.force:
            print(f"  [SKIP] 이미 업로드됨: {upload_log[log_key].get('url', '')}")
            results["skip"].append(day_num)
            continue

        # 포스트 빌드
        post = build_post(day_num, day_dir, token, dry_run=args.dry_run)
        if not post:
            results["fail"].append(day_num)
            continue

        # series_id 주입
        if series_id:
            post["series_id"] = series_id

        if args.dry_run:
            print(f"  [DRY-RUN] 제목: {post['title']}")
            print(f"  [DRY-RUN] 태그: {post['tags']}")
            print(f"  [DRY-RUN] slug: {post['url_slug']}")
            print(f"  [DRY-RUN] 본문 길이: {len(post['body'])} chars")
            results["success"].append(day_num)
            continue

        # 실제 업로드
        print(f"  업로드 중: {post['title']}")
        result = write_post(post, headers)

        if result:
            username = result.get("user", {}).get("username", "unknown")
            url = f"https://velog.io/@{username}/{result['url_slug']}"
            print(f"  [✓] 업로드 완료: {url}")
            
            upload_log[log_key] = {
                "day": day_num,
                "title": result["title"],
                "post_id": result["id"],
                "url": url,
                "uploaded_at": time.strftime("%Y-%m-%dT%H:%M:%S")
            }
            save_log(upload_log)
            results["success"].append(day_num)
        else:
            print(f"  [✗] 업로드 실패")
            results["fail"].append(day_num)

        # API 요청 간 딜레이
        if day_num != day_dirs[-1][0]:
            time.sleep(1.5)

    # 최종 결과 출력
    print(f"\n{'=' * 55}")
    print("  업로드 결과 요약")
    print(f"{'=' * 55}")
    print(f"  [OK] {len(results['success'])}개 성공 -> Day {results['success']}")
    print(f"  [->] {len(results['skip'])}개 건너뜀 -> Day {results['skip']}")
    print(f"  [X] {len(results['fail'])}개 실패 -> Day {results['fail']}")
    if not args.dry_run and results["success"]:
        print(f"\n  📋 업로드 로그: {LOG_FILE}")
    print()

if __name__ == "__main__":
    main()
