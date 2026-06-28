## 장치파일 생성
* Device driver로 사용할 장치 파일 생성
* 유저가 Device Driver File을 이용해 장치를 사용 가능
* 장치 파일을 생성하기 위해서는 mknod를 통해 장치 파일 생성
#### mknod
* 일반적으로 /dev 경로에 생성
* 장치 파일은 user와 Device Driver를 연결해주는 매개체, devfs에서 관리
* 구성
	* dentry 구조체 : 경로 관리 구조체
	* inode 구조체 : 파일 관리 구조체
	* 부모는 dentry.d_subdirs, 자식들은 dentry.d_child와 double linked list 구성
![[Pasted image 20260609104412.png]]
![[Pasted image 20260609104422.png]]
#### 장치 파일 생성
* 커널에 문자 디바이스 cdev 등록
	* `int cdev_add(struct cdev *cdev, dev_t dev, unsigned count);`
		* cdev - cdev 구조체 변수 주소
		* dev - 디바이스 번호(major/minor)
		* count - minor 개수
	* 커널에 char device 등록 함수, 디바이스 번호와 연결
	* 성공시 0, 실패 시 음수 에러 코드 반환
```
cdev_init(&my_cdev, &my_fops);
cdev_add(&my_cdev, my_dev, 1);
```
* class 생성
	* /sys/class/<class_name> 디렉 생성 함수
	* device_create가 이 class 아래에 장치를 생성할 수 있게 해줌
	* udev가 /dev 노드를 만들기 위한 준비 단계
	* `struct class *class_create(const char *name);`
	* name - sysfs class 이름
```c
led_class = class_name("my_class"); // /sys/class/my_class 생성
```
* 장치 노드(파일) 생성
	* /dev 노드를 자동으로 만들어주는 함수 : udev와 sysfs에 장치를 등록, 실제 /dev 파일 생성
	* 반드시 class_create() 먼저 호출
	* device_destroy() 함수로 제거
	* `struct device *device_create(struct class, struct device *parent, dev_t dev, void *drvdata, const char *fmt, ...);`
	* class - class_create()로 만든 class, 아래에 sysfs 노드 생성
	* parent - 부모 device, 일반적으로 NULL
	* drvdata - device에 연결할 private data(보통 NULL)
	* fmt - /dev/ 에 생성 할 장치 파일명
	* ... - printf 스타일 가변 인자
```c
alloc_chrdev_region(&dev, 0, 1, "mydev");
cdev_init(&cdev, &fops);
cdev_add(&cdev, dev, 1);

cls = class_create("my_class")l
device_create(cls, NULL, dev, NULL, "mydev");
```
* 장치 파일 권한 변경
	* 리눅스 커널에서는 보안 때문에 장치 파일의 권한을 기본적으로 crw------(0600) 설정
	* 장치파일의 권한 변경이 필요한 경우 class 생성 시 devnode 콜백 함수를 이용해 권한 설정 가능
![[Pasted image 20260609112813.png]]
* 장치 노드 삭제
	* device_create()로 만든 /dev/xxx 장치 파일과 sysfs의 /sys/class/...아래에 생성된 디바이스 엔트리 제거
	* `void device_destroy(const struct class *class, dev_t dev);`
	* class - class_create()로 생성한 class 구조체 포인터
	* dev - 제거할 디바이스의 디바이스 번호(device_create()에서 사용했던 것과 동일)
* 클래스 삭제
	* /sys/class/\<classname>/디렉토리 제거
	* class 내부에서 관리하던 디바이스 목록 정리
	* class에 연결된 uevent, devnode 등 콜백 해제
	* 내부적으로 reference count 감소 및 메모리
	* `void class_destory(struct class *cls);`
		* cls - class_create()로 생성한 class 구조체 포인터(반드시 class_create()에서 반환된 값 그대로 전달)
#### file_operations
* 유저 공간에서 명령어와 커널 공간의 드라이버 함수를 이어주는 연결고리
* linux/fs.h에서 정의하는 구조체, 함수 포인터 집합으로 구성
* 특정 동작 함수를 구현해 가리켜야 함
```c
struct file_operations {
    struct module *owner;
    fop_flags_t fop_flags;
    loff_t (*llseek) (struct file *, loff_t, int);
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
    ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
    int (*iopoll)(struct kiocb *kiocb, struct io_comp_batch *,
                  unsigned int flags);
    int (*iterate_shared) (struct file *, struct dir_context *);
    __poll_t (*poll) (struct file *, struct poll_table_struct *);
    long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
    long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
    int (*mmap) (struct file *, struct vm_area_struct *);
    int (*open) (struct inode *, struct file *);
    int (*flush) (struct file *, fl_owner_t id);
    int (*release) (struct inode *, struct file *);
    int (*fsync) (struct file *, loff_t, loff_t, int datasync);
    int (*fasync) (int, struct file *, int);
};
```
* `struct module *owner`
	* 파일 오퍼레이션의 소유자 명시, 보통 linux/module.h에 정의 되어있는 THIS_MODULE 매크로 사용해 초기화
* `loff_t (*llseek)(struct file*, loff_t, int)`
	* 디바이스 드라이버 파일 포인터 위치 강제 이동시키는 함수 지정
* `ssize_t (*read)(struct file *, char*, size_t, loff_t*);`
	* 디바이스에서 데이터 읽는데 사용, NULL이면 -EINVAL 반환
* `ssize_t (*write)(struct file *, const char *, size_t, loff_t *);`
	* 데이터를 디바이스로 보냄, NULL이면 -EINVAL 반환
* `unsigned int (*poll)(struct file *, struct poll_table_struct *);`
	* 다중 입출력 처리를 가능하게 해주는 poll, epoll, select의 백엔드
* `int (*unlocked_ioctl)(struct inode *, struct file *, unsigned int, unsigned long);`
	* 디바이스 관련 명령들 제어
```c title=Exam
struct file_operations xxx_fops = {
    .owner = THIS_MODULE,
    .llseek = xxx_llseek,
    .read = xxx_read,
    .ioctl = xxx_ioctl,
    .open = xxx_open,
    .release = xxx_release,
};
```
#### open/release
* open
	* 디바이스 관련 오류 확인(미준비, HW 문제)
	* 처음으로 디바이스 오픈한 경우 디바이스 초기화
	* 필요에 따라 f_op 포인터 갱신
	* 필요에 따라 자료구조 할당, `filp -> private_data`에 들어갈 값 채움
* release
	* device_close로 부르는 경우 존재
	* open이 `filp->private_data`에 할당한 데이터의 할당 삭제
	* 마지막 close 호출 시 디바이스 종료
* 호출의 기본 처리
	* 디바이스 드라이버가 처음 오픈한 경우 HW 초기화
	* 디바이스 드라이버의 동작에 필요한 에러 체크
		* ENODEV HW 존재 x
		* ENOMEM 커널 메모리 부족
		* EBUSY 디바이스 이미 사용
	* minor 번호에 대한 처리가 필요한 경우
		* file_operation 구조체 갱신
	* 프로세스 별 메모리 할당 및 초기화
		* file 구조체 filp의 private_data에 등록해 사용
			* `filp->private_data = vmalloc(1024);`
* 매개변수 반환 값 상관관계
	* open 함수의 pathname과 flags는 xxx_open() 함수에 직접 전달 X
		* 사전처리 해서 그럼
	* 적절히 inode와 filp 변수에 배분되어 전달
![[Pasted image 20260609115604.png]]
#### file structure
* file structure in <linux/fs.h>
	* 디바이스 드라이버가 사용하는 중요 커널 자료구조
	* 오픈 파일에 하나씩 할당
```c
struct file {
        struct file *                  f_next, **f_pprev;
        struct dentry *                f_dentry;
        struct file_operations *       f_op;
        mode_t                         f_mode;
        loff_t                         f_pos;
        unsigned int                   f_count, f_flags;
        unsigned long                  f_reada, f_ramax, f_raend,
                                       f_ralen, f_rawin;
        struct fown_struct             f_owner;
        unsigned int                   f_uid, f_gid;
        int                            f_error;
        unsigned long                  f_version;
        /* needed for tty drivers, and maybe others */
        void *                         private_data;
};
```
*  `mode_t f_mode`
	* FMODE_READ/FMODE_WRITE 비트로 결정
	* 파일 시스템 호출에서 R/W 권한 미리 검사
* `loff_t f_pos`
	* 현재 읽기 쓰기 위치
	* lseek/read/write 메소드에서 갱신
* `unsigned int f_flags`
	* O_RDONLY, O_NONBLOCK, O_SYNC...
	* 드라이버는 자신의 동작 제어를 위해 이 필드 참조
* `struct file_operations *f_op`
	* 드라이버 메소드 테이블을 가리키는 포인터
	* method overriding 될 수도 있음
* `void *private_data`
	* 드라이버/모듈들의 내부 데이터 유지
	* 커널이 file 구조체를 파괴하기 전에 미리 파괴해야 함
![[Pasted image 20260609115948.png]]
#### 읽기와 쓰기 구현
* read와 write를 구현하기 위해 알아야 할 사항
	* 사용자 메모리 공간과 커널 메모리 공간 사이의 데이터 이동
	* 처리 조건이 되지 않을 때의 처리
	* HW 제어 함수
	* 여러 프로세스가 동시에 접근했을 때의 경쟁 처리
	* 인터럽트 서비스 함수와의 경쟁 처리
![[Pasted image 20260609121640.png]]
#### 사용자 영역과 커널 영역 간의 메모리 복사 함수
* 사용자가 보낸 데이터 읽기 - `copy_from_user()`
	* `unsigned long copy_from_user(void* to, const void __user* from, unsigned long n);`
	* to - 데이터를 저장할 커널 공간의 버퍼 주소
	* from - 사용자가 보낸 데이터가 담긴 유저 공간의 버퍼 주소
	* n - 복사할 데이터의 크기(바이트 수)
	* 반환값 - 성공 0, 실패하면 복사하지 못한 남은 바이트 수 반환
* 사용자에게 데이터 보내기 - `copy_to_user()`
	* `unsigned long copy_to_user(void __user* to, const void* from, unsigned long n);`
		* to - 데이터를 받아갈 유저 공간의 버퍼 주소
		* from - 넘겨줄 데이터가 저장된 커널 공간의 버퍼 주소
		* n - 복사할 데이터의 크기(바이트 수)
		* 반환값 - 성공 0, 실패하면 복사하지 못한 남은 바이트 수 반환
#### write
![[Pasted image 20260609134230.png]]
* 주요 메서드
	* `ssize_t xxx_write(struct file *filp, char *buff, size_t count, loff_t *offp);`
		* 사용자 영역은 buff에서 count 바이트 만큼 읽은 후 디바이스의 offp 위치로 저장
	* `unsigned long copy_from_user(void* to, const void* from, unsigned long count);`
		* 사용자 메모리 from을 커널 메모리 to로 count만큼 복사
	* `get_user(x, ptr);`
		* x변수에 ptr의 사용자 메모리값 대입(매크로)
* 주요 에러
	* EAGAIN : O_NONBLOCK으로 열렸지만 write() 호풀 시 즉시 처리할 수 있는 상황이 아니다
	* EIO : I/O 에러 발생
	* EFAULT : 버퍼가 접근할 수 없는 주소 공간 지정
	* ENOSPC : 데이터를 위한 공간 부재
* 구현
	* `struct file *filp`
		* 읽기와 쓰기에 전달되는 file 구조체 변수의 선두 주소를 담은 filp는 디바이스 파일이 어떤 형식으로 열렸는가에 대한 정보 포함
		* `unsigned int f_flags`
			* 가장 많이 참조되는 태그 : O_RDONLY, O_NONBLOCK || O_NDELAY, O_SYNC
	* `loff_t f_pos`
		* f_pos 필드 변수에는 현재 읽기/쓰기 위치 담음
		* read, write, llse 다 ()과 같이 읽기 쓰기의 위치를 변경할 수 있는 함수에 의해 변경
```c
ssize_t xxx_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    if(!(데이터가 처리 가능한가?)) {
        if((filp->f_flags & O_NONBLOCK)) {
            // 블록 모드로 열렸다면 프로세스를 재운다.
        }
    }

    // 사용자 공간에 데이터를 가져온다.
    // copy_from_user, get_user

    // 하드웨어에서 데이터를 쓴다.
    // outb(), ..., writeb() 함수 사용
    // 또는 버퍼를 읽는다.

    return 처리된 데이터 개수;
}
```
#### read
![[Pasted image 20260609134838.png]]
* 디바이스 오픈할 때 옵션 사항
	* read 함수의 매개변수 중 `struct file *filp`를 참조해 판단
	* 응용 프로그램이 O_NONBLOCK이나 O_NDELAY를 지정하지 않은 상태로 디바이스 파일 열면 count 값이 만족될 때까지 대기
	* 그렇지 않으면 발생된 데이터만 버퍼에 써넣고 함수 종료
```c
ssize_t xxx_read(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    ...

    if (filp->f_flags & O_NONBLOCK) {
        // 즉시 처리한다.
    } else {
        // 블록 처리한다.
    }
}
```
* read 함수에서 하드웨어를 다루는 함수 
	* port-map I/O 
		* inb(), inw(), inl(), insb(), insw(), insl()  
	* memory-mapped I/O 
		* readb(), readw(), readl()  
	* I/O memory block 
		* memset_io(), memcpy_fromio(), memcpy_toio()
```c
ssize_t xxx_read(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
    if (!(준비된 데이터가 있는가?))
    {
        if (!(filp->f_flags & O_NONBLOCK))
        {
            // 블록 모드로 열렸다면 프로세스를 재운다.
        }
    }

    // 하드웨어에서 데이터를 읽는다.
    // inb(), ..., readb(), ... 등 함수 사용
    // 또는 버퍼를 읽는다.

    // 사용자 공간에 데이터를 전달한다.
    // copy_to_user, put_user

    return 0;
}
```
#### ioctl
* 목적
	* I/O Control 관련 작업 수행 함수
	* ioctl 구현은 cmd 인수 값에 따라 올바른 동작을 선택하는 switch문으로 구성
	* `int ioctl(int fd, int cmd, ...);`
* 커널 영역에서 ioctl 함수
	* `int (*unnlocked_ioctl)(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg);`
		* inode와 filp 포인터는 응용 프로그램의 파일 디스크립터 fd와 일치하는 인수
		* cmd 인수는 명령을 나타내는 응용 프로그램의 인수 전달
		* arg 인수는 명령 실행의 결과 데이터가 전달되는 unsigned long 형의 정수 또는 포인터
#### cmd
* cmd 명령의 해석 매크로 함수
	* \_IOC_NR 구분 번호 필드 값을 읽는 매크로
	* \_IOC_TYPE 매직 넘버 필드 값을 읽는 매크로
	* \_IOC_SIZE 데이터의 크기 필드 값을 읽는 매크로
	* \_IOC_DIR 읽기와 쓰기 속성 필드 값을 읽는 매크로
	* e.g ) `if(_IOC_TYPE(cmd)!=My_MAGIC) return -EINVAL`
* cmd 명령의 작성 매크로 함수
	* \_IO 부가적인 데이터가 없는 명령을 만든느 매크로
	* \_IOR 데이터를 읽어오기 위한 명령을 작성
	* \_IOW 데이터를 써 넣기 위한 명령을 작성
	* \_IOWR 디바이스 드라이버에서 읽고 쓰기 위한 명령을 작성하는 매크로
	* e.g ) \_IOW(매직 넘버, 구분 번호, 변수형)
![[Pasted image 20260609150547.png]]
* ioctl 구현 시 해당 디바이스의 명령들에 대한 고유의 상수 값을 지정
	* 타입, 시퀀스 번호, 전송 방향, 인수의 크기 등을 표시하는 비트 필드로 표현
	* include/asm/ioctl.h와 Documentation/ioctl-number.txt를 체크해서 중복되지 않도록 드라이버의 ioctl 번호를 선정
* 타입
	* 서로 중복되지 않는 8비트 고유 번호(매직 넘버)
	* Documentation/ioctl-number.txt를 참조하여 선정 (\_IOC_TYPEBITS)
* 시퀀스 번호
	* 8비트 크기의 시퀀스 번호(\_IOC_NRBITS)
* 방향
	* 명령의 데이터의 전송 방향 표시
	* \_IOC_NONE(데이터 전송이 없음), \_IOC_READ, \_IOC_WRITE, \_IOC_READ | \_IOC_WRITE (양방향 전송) 등의 값을 가짐
* 응용 프로그램과의 관계
![[Pasted image 20260609150756.png|594]]
```text
유저 앱
    ↓
ioctl(fd, SET_INTERVAL, &interval)

SET_INTERVAL
    ↓
_IOW('a', 1, int)로 만들어진 cmd 숫자

cmd 내부
    ├── TYPE = 'a'
    ├── NR   = 1
    ├── SIZE = sizeof(int)
    └── DIR  = WRITE

드라이버
    ↓
_IOC_TYPE(cmd)으로 'a' 확인
_IOC_NR(cmd)로 1번 명령 확인
_IOC_SIZE(cmd)로 int 크기 확인
_IOC_DIR(cmd)로 user → kernel 방향 확인
```

```c
#ifndef _SK_H_
#define _SK_H_

#define SK_MAGIC 'k'
#define SK_MAXNR 6

typedef struct {
    unsigned long size;
    unsigned char buf[128];
} __attribute__((packed)) sk_info;

#define SK_LED_OFF   _IO(SK_MAGIC, 0)
#define SK_LED_ON    _IO(SK_MAGIC, 1)
#define SK_GETSTATE  _IO(SK_MAGIC, 3)

#define SK_READ      _IOR(SK_MAGIC, 3, sk_info)
#define SK_WRITE     _IOW(SK_MAGIC, 4, sk_info)
#define SK_RW        _IOWR(SK_MAGIC, 5, sk_info)

#endif /* _SK_H_ */
```
```c
int sk_ioctl(struct inode *inode, struct file *filp,
             unsigned int cmd, unsigned long arg)
{
    sk_info ctrl_info;

    /* Check on cmd */
    if (_IOC_TYPE(cmd) != SK_MAGIC)
        return -EINVAL;

    if (_IOC_NR(cmd) != SK_MAXNR)
        return -EINVAL;

    size = _IOC_SIZE(cmd);

    if (size) {
        err = 0;

        if (_IOC_DIR(cmd) & _IOC_READ)
            err = verify_area(VERIFY_WRITE, (void *)arg, size);
        else if (_IOC_DIR(cmd) & _IOC_WRITE)
            err = verify_area(VERIFY_READ, (void *)arg, size);

        if (err)
            return err;
    }

    switch (cmd) {
    case SK_LED_OFF: {
        ...
    }
}
```
#### Register 직접 제어
![[Pasted image 20260610092805.png]]
* PinMap 확인
	* GPIO 18 사용 -> Bit 26-24 사용 => 해당 3비트만 사용해야함
```c
#if 0

#define BCM_IO_BASE 0x20000000 /* Raspberry Pi B/B+의 I/O Peripherals 주소 */

#define BCM_IO_BASE 0x3F000000 /* Raspberry Pi 2/3의 I/O Peripherals 주소 */

#else

#define BCM_IO_BASE 0xFE000000 /* Raspberry Pi 4의 I/O Peripherals 주소 */

#endif

  

#define GPIO_BASE (BCM_IO_BASE + 0x200000) /* GPIO 컨트롤러의 주소 */

#define GPIO_SIZE (256) /* 0x7E2000B0 – 0x7E2000000 + 4 = 176 + 4 = 180 */

  

/* GPIO 설정 매크로 */

#define GPIO_IN(g) (*(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))) /* 입력 설정 */

#define GPIO_OUT(g) (*(gpio+((g)/10)) |= (1<<(((g)%10)*3))) /* 출력 설정 */

  

#define GPIO_SET(g) (*(gpio+7) = 1<<g) /* 비트 설정 */

#define GPIO_CLR(g) (*(gpio+10) = 1<<g) /* 설정된 비트 해제 */

#define GPIO_GET(g) (*(gpio+13)&(1<<g)) /* 현재 GPIO의 비트에 대한 정보 획득 */
```
* BCM2711 확인해 사용 비트 확인 후 비트 연산 시행
* 상위 주소 범위가 어떤 큰 영역인지 정하고, 하위 offset이 그 안의 세부 장치를 정한다
	* ![[Pasted image 20260610093933.png]]
	* ![[Pasted image 20260610093951.png]]
-> Low Peripheral mode에서 ARM이 보는 물리주소 기준으로 변환하여 /dev/mem에 사용
* BCM2711 문서의 peripheral 주소는 legacy master address 기준이다.
* GPIO register base는 문서상 0x7E200000이다.

* Low Peripheral mode에서 ARM은 0x7Enn_nnnn peripheral 주소를
* 0x0_FEnn_nnnn 형태의 ARM physical address로 본다.

* 따라서 /dev/mem으로 GPIO를 mmap할 때는
* 0x7E200000이 아니라 ARM physical address인 0xFE200000을 사용한다.

* 문서상 GPIO 주소:0x7E200000 = 0x7E000000 + 0x00200000 legacy peripheral base + GPIO offset

* Low Peripheral mode에서 ARM physical peripheral base:0xFE000000

* 따라서 /dev/mem용 GPIO 주소:0xFE000000 + 0x00200000 = 0xFE200000