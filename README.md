# 🟣 stage/qt — Qt 프레임워크 학습 노트 & 실습 코드

> VEDA 교육과정 中 **Qt 프레임워크** 강의 노트와 실습 코드를 담은 브랜치입니다.

---

## 🗂️ 브랜치 구조

```
stage/qt/
├── MD/
│   └── Week4/     # Qt 강의 노트 (Day16~20)
└── workspace/
    └── Week4/     # Qt 실습 프로젝트
        ├── Day16/ # QMainWindow, CMake/QMake 빌드 실습
        ├── Day17/ # CheckBox, ComboBox, Designer 실습
        ├── Day18/ # Layout, Widgets, Container 실습
        └── Day19/ # Dialog, Signal/Slot, QMainWindow 실습
```

---

## 📅 학습 커리큘럼

| 주차 | 일차 | 주제 | 핵심 내용 |
|------|------|------|-----------|
| **Week 4** | Day 16 | Qt 입문 & 기초 | **Qt 아키텍처**(MVC), CMake/QMake 빌드, **QMainWindow**, 이벤트 처리, Signal/Slot |
| **Week 4** | Day 17 | Qt 위젯 & 디자이너 | **QCheckBox**, **QComboBox**, Qt Designer, connect 함수, resources 에셋 |
| **Week 4** | Day 18 | Qt 레이아웃 & 데이터 타입 | **Layout**(QHBox/QVBox/QGrid/QForm), **QString/QChar**, QVariant, QMap/QHash, QSet |
| **Week 4** | Day 19 | Signal/Slot 심화 & Dialog | **Signal/Slot** 심화, emit, **QDialog**(QInputDialog/QFileDialog/QMessageBox), Modal/Modeless |
| **Week 4** | Day 20 | QMainWindow & Model/View & QPainter | **QMainWindow** 구조, Stream, **Model-View** 아키텍처, **QPainter** 2D 그래픽스 |

---

## 🔑 핵심 학습 목표

- ✅ **Qt 프레임워크** — MVC 아키텍처, CMake/QMake 빌드, QMainWindow, Signal/Slot
- ✅ **Qt 위젯** — QLabel, QPushButton, QCheckBox, QComboBox, QGroupBox, QLCDNumber, QTabWidget
- ✅ **Qt 데이터 타입** — QString, QChar, QLatin1String, QVariant, QByteArray
- ✅ **Qt 컨테이너** — QMap, QHash, QPair, QList, QSet
- ✅ **Qt Signal/Slot 심화** — emit, Old/New Style connect, 시그널 전파
- ✅ **Qt Dialog** — QInputDialog, QFileDialog, QMessageBox, Modal/Modeless
- ✅ **Qt Model/View 아키텍처** — QAbstractItemModel, QStringListModel, QListView, Delegate
- ✅ **Qt Stream & File I/O** — QTextStream, QDataStream, QFileDialog
- ✅ **QPainter 2D 그래픽스** — paintEvent, QPainter begin/end, setPen, drawLine

---

## 🔗 관련 브랜치

| 브랜치 | 내용 |
|--------|------|
| [`main`](../../tree/main) | 전체 프로젝트 소개 |
| [`stage/c-cpp`](../../tree/stage/c-cpp) | C / C++ 기초~OOP (Week1~3) |
| [`stage/embedded`](../../tree/stage/embedded) | 임베디드 시스템 (Week5~6) |
| [`stage/linux`](../../tree/stage/linux) | Linux / Bash (Week6~7) |
| [`group-study`](../../tree/group-study) | 알고리즘 스터디 |
