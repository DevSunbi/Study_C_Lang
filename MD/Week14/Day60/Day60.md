## 영상 처리 시스템
#### 영상처리시스템
- 실세계->카메라->디지털 영상처리 시스템(필터링, 에지검출, 모폴로지)->처리된 영상
#### 컬러
- 실 색상을 디지털 수치화 -> 컬러 값
- 기본 색상 => 물리학자 맥스웨르이 3가지 컬러를 이용해 표현
#### 디지털 영상의 생성
- 각 수치들의 조합으로 디지털 영상 생성
#### 표본화와 양자화
- 아날로그 영상 -> 픽셀로 변환, 이후 수치를 양자화
- 표본화 - 공간 영역에서 픽셀의 개수를 제한 == 해상도
#### 영상의 종류
- 그레이스케일 영상/컬러 영상
#### 영상의 좌표계
- 각 화소 값의 배치 기준
- 원점은 좌상단
---
## OpenCV
#### 개요
- 오픈소스 라이브러리
- BSD 라이선스, 계산 효율성 및 실시간 응용 프로그램에 중점을 두고 설계
#### 내부 구성
- 영상 처리 - 필터링, 에지 검출, 변환
- 특징 분석 - 물체 감지, 트랙킹, 얼굴 인식
- 기타 - 기계 학습, 영상 피라미드, 스테레오 비전
#### 가능 작업
- 영상 파일 읽기 쓰기
- 비디오 캡처 및 저장
- 영상 처리(필터, 변환)
- 영상이나 비디오에서 얼굴, 눈, 자동차와 같은 특정 물체 감지
- 비디오 분석, 움직임 추정, 배경 제거, 특정 물체 추적
- ML 알고리즘을 이용한 물체 인식
#### 라이브러리 모듈
- Core
- Video
- Imgproc
- Calib3D
- ML
- Objdetect
- Features2D
- Gpu
- Highgui
```
sunbi@Sunbi:~ $ pkg-config --cflags opencv4
-I/usr/include/opencv4 
sunbi@Sunbi:~ $ 
```
-> 컴파일 위치
```bash
sunbi@Sunbi:~ $ pkg-config --libs opencv4
-lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_signal -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_ml -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
```
## Mat Class
- OpenCV에서 영상을 담을 때 사용하는 데이터, OpenCV 라이브러리의 핵심 요소
- 동적 메모리 할당을 진행하는 스마트 포인터
#### 화소의 자료형 지정
- cv_(화소 비트 수)(부호 여부)(채널의 개수)