/***************************************
 * Filename: sk.c
 * Title: Skeleton Device
 * Desc: module_init, module_exit
 ***************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include "sk_ioctl.h"
#include <linux/interrupt.h>

#define MY_MAJOR 200
#define MY_MINOR_BASE 0
#define MY_DEV_COUNT 1
#define MY_DEV_NAME "my_skeleton_dev"
#define BUFFER_SIZE 1024

#define GPIO_LED 530
#define GPIO_SW 534			// Switch

#define BCM_IO_BASE 0xFE000000 /* Raspberry Pi 4의 I/O Peripherals 주소 */

#define GPIO_BASE (BCM_IO_BASE + 0x200000) /* GPIO 컨트롤러의 주소 */
#define GPIO_SIZE (256)					   /* 0x7E2000B0 – 0x7E2000000 + 4 = 176 + 4 = 180 */

/* GPIO 설정 매크로 */
#define GPIO_IN(g) (*(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))) /* 입력 설정 */
#define GPIO_OUT(g) (*(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))) /* 출력 설정 */

#define GPIO_SET(g) (*(gpio + 7) = 1 << g)	  /* 비트 설정 */
#define GPIO_CLR(g) (*(gpio + 10) = 1 << g)	  /* 설정된 비트 해제 */
#define GPIO_GET(g) (*(gpio + 13) & (1 << g)) /* 현재 GPIO의 비트에 대한 정보 획득 */

volatile unsigned *gpio; /* I/O 접근을 위한 volatile 변수 */

static char kernel_buffer[BUFFER_SIZE];
static dev_t dev_num;			 // 디바이스 번호를 담을 변수
static struct cdev sk_cdev;		 // 문자 디바이스 관리 구조체
static struct class *sk_class;	 // 클래스 구조체 포인터 저장 변수
static struct device *sk_device; // 디바이스 구조체 포인터 저장 변수

static int switch_irq;		// Switch add

static struct task_struct *task;	// Task를 위한 구조체

/* 인터럽트 처리를 위한 인터럽트 서비스 루틴(Interrup Service Routine) */
static irqreturn_t isr_func(int irq, void *data)
{
    struct kernel_siginfo sinfo;		// 시그널 처리를 위한 구조체

    if (irq == switch_irq && !gpio_get_value(GPIO_LED)) {
        gpio_set_value(GPIO_LED, 1);        // LED ON
        kernel_buffer[0] = '1';
    } else if (irq == switch_irq && gpio_get_value(GPIO_LED)) {
        struct kernel_siginfo sinfo;
        memset(&sinfo, 0, sizeof(struct kernel_siginfo));
        sinfo.si_signo = SIGIO;
        sinfo.si_code = SI_USER;
        send_sig_info(SIGIO, &sinfo, task);	// 해당 프로세스에 시그널 보내기
        gpio_set_value(GPIO_LED, 0);        // LED OFF
        kernel_buffer[0] = '0';
    }
    return IRQ_HANDLED;
}



/* 3. open함수: 장치 파일을 열 때 호출 */
static int sk_open(struct inode *inode, struct file *file)
{
	pr_info("SK Device opened!\n");
	// GPIO_OUT(GPIO_LED);
	return 0;
}

/* 3. release 함수: 장치 파일을 닫을 때 호출 */
static int sk_release(struct inode *inode, struct file *file)
{
	pr_info("SK Device closed!\n");
	return 0;
}

/* 4. read 함수: 커널 버퍼의 내용을 유저에게 전송 (copy_to_user) */
static ssize_t sk_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int retval;

	/* 읽기 위치(Offset)가 0인 처음 상황에서만 딱 한번 읽도록 처리(무한 루프 방지) */
	if (*ppos > 0)
		return 0;

	kernel_buffer[0]= gpio_get_value(GPIO_SW)? '1':'0';
	kernel_buffer[1] = '\0'; 

	if (count > BUFFER_SIZE)
		count = BUFFER_SIZE;

	/* 커널 공간의 데이터를 유저 공간(buf)으로 안전하게 복사 */
	retval = copy_to_user(buf, kernel_buffer, count);
	if (retval != 0)
	{
		pr_err("Failed to send data to user\n");
		return -EFAULT; // 메모리 접근 에러 코드 반환
	}
	*ppos += count; // 읽은 만큼 위치 이동
	pr_info("Sent %zu bytes to user \n", count);
	return count;
}

/* 4. write 함수: 유저가 보낸 데이터를 커널 버퍼에 저장 (copy_from_user) */
static ssize_t sk_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int retval;
	int pid;
	char *endptr;

	/* 버퍼 사이즈 체크 */
	if (count > BUFFER_SIZE - 1)
		count = BUFFER_SIZE - 1;
	retval = copy_from_user(kernel_buffer, buf, count);
	if (retval != 0)
	{
		pr_err("Failed to receive data from user \n");
		return -EFAULT;
	}
	kernel_buffer[count] = '\0';

	//strcmp(kernel_buffer, "0")) ? gpio_set_value(GPIO_LED, 0) : gpio_set_value(GPIO_LED, 1);
	
	/* 오류 검출 + 시그널 발생 시 프로세스 ID를 등록함 */
	pid = simple_strtol(kernel_buffer, &endptr, 10);
	if(endptr != NULL) {
		task = pid_task(find_vpid(pid), PIDTYPE_PID);
		if(task == NULL) {
			pr_err("Error: Can't find PID from user application\n");
            return 0;
		}
	
	}
	pr_info("GPIO Device write: %s", kernel_buffer);
	pr_info("PID: %d\n", pid);

	return count;
}

static long sk_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch (cmd)
	{
	case SPEED_UP:
	{
		printk("\n");
		printk("UP\n");
		break;
	}
	case SPEED_DOWN:
	{
		printk("\n");
		printk("DOWN\n");
		break;
	}
	default:
		return 0;
	}
	return 0;
}

/* 2. file_operations 구조체 정의 (static const 필수) */
static const struct file_operations sk_fops = {
	.owner = THIS_MODULE,
	.open = sk_open,	   // 유저가 open하면 커널안의 sk_open 함수 실행
	.release = sk_release, // 유저가 release하면 커널안의 sk_release 함수 실행
	.read = sk_read,
	.write = sk_write,
	.unlocked_ioctl = sk_ioctl,
};

static char *sk_devnode(const struct device *dev, umode_t *mode)
{
	if (mode)
	{
		*mode = 0666;
	}
	return NULL;
}
/* 1. 모듈이 커널에 로드될 때 호출되는 함수 */
static int __init sk_init(void)
{
	int retval;
	int err;
	// static void *map; // I/O 접근을 위한 면수

	pr_info("SK Module is initializing...\n");

	/* 2. 커널에 빈 MAJOR 번호 등록 */
	retval = alloc_chrdev_region(&dev_num, 0, 1, "SK_Driver");
	if (retval < 0)
	{
		pr_err("Failed to allocate device number\n");
		return retval;
	}

	/* 2. 커널에 cdev 등록하기전 초기화 */
	cdev_init(&sk_cdev, &sk_fops);
	sk_cdev.owner = THIS_MODULE;

	/* 2. 할당받은 번호와 cdev 구조체를 커널 시스템에 최종 등록 */
	retval = cdev_add(&sk_cdev, dev_num, 1);
	if (retval < 0)
		goto err_unregister_region;

	/* 2. class를 생성하여 디렉터리를 생성하여 device_create가 이 class아래에
	장치를 생성할 수 있게 함 */
	sk_class = class_create("led_class");
	if (IS_ERR(sk_class))
	{ // 커널 포인터 에러 검사 매크로
		retval = PTR_ERR(sk_class);
		goto err_del_cdev;
	}
	// 권한 추가 ++ -> 라즈베리파이에서 유저가 사용할 수 있게해줌 sudo ./sk_app 안해도됨
	sk_class->devnode = sk_devnode;

	/* 2. /dev/SK 생성해주기 = 실제 장치 파일 자동 생성 */
	sk_device = device_create(sk_class, NULL, dev_num, NULL, "buttondevice");
	if (IS_ERR(sk_device))
	{
		retval = PTR_ERR(sk_device);
		goto err_destroy_class;
	}

	gpio_request(GPIO_LED, "led");
	gpio_direction_output(GPIO_LED, 0);

	/* GPIO 인터럽트 번호 획득, 핸들러 등록 */
	gpio_request(GPIO_SW, "SWITCH");
	switch_irq = gpio_to_irq(GPIO_SW);
	pr_info("switch_irq = %d\n", switch_irq);
	err = request_irq(switch_irq, isr_func, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "switch", NULL);


	// map = ioremap(GPIO_BASE, GPIO_SIZE); // 사용할 메모리 할당
	// if (!map)
	// {
	// 	printk("ERROR: mapping GPIO memory\n");
	// 	iounmap(map);
	// 	return -EBUSY;
	// }
	// gpio = (volatile unsigned int *)map;

	pr_info("SK Module & /dev/SK setup successfully completed! Major : %d\n", MAJOR(dev_num));
	return 0;


	err_destroy_device:
		device_destroy(sk_class, dev_num);
	err_destroy_class:
		class_destroy(sk_class);
	err_del_cdev:
		cdev_del(&sk_cdev);
	err_unregister_region:
		unregister_chrdev_region(dev_num, 1);

	return retval;
}

/* 1. 모듈이 커널에서 제거될 때 호출되는 함수 */
/* 등록했던 순서의 정반대로 자원을 해제 */
static void __exit sk_exit(void)
{
	pr_info("SK Module is exiting....\n");

	device_destroy(sk_class, dev_num); // 2. 장치 파일 삭제
	class_destroy(sk_class);		   // 2. sk_class 클래스 삭제

	/* 커널시스템에서 cdev 제거*/
	cdev_del(&sk_cdev); // 2. 문자 디바이스 기능 제거

	gpio_free(GPIO_LED);
	gpio_direction_output(GPIO_LED, 0);

	/* 사용이 끝난 GPIO_SW 해제 */
	free_irq(switch_irq, NULL);
	gpio_free(GPIO_SW);

	// if (gpio)
	// {
	// 	iounmap(gpio);
	// }
	/* 모듈이 내려갈 때 해제 */
	unregister_chrdev_region(dev_num, MY_DEV_COUNT);
}

/* 1. 모듈이 커널에 로드될 때 호출되는 함수 */
module_init(sk_init);
module_exit(sk_exit);

MODULE_LICENSE("GPL");
