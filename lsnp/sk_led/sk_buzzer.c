#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define MY_MAJOR 200
#define MY_MINOR_BASE 0
#define MY_DEV_COUNT 1
#define MY_DEV_NAME "my_skeleton_dev"
#define BUFFER_SIZE 1024

#define GPIO_BZ 539			// Buzzer

static char kernel_buffer[BUFFER_SIZE];
static dev_t dev_num;			 // 디바이스 번호를 담을 변수
static struct cdev sk_cdev;		 // 문자 디바이스 관리 구조체
static struct class *sk_class;	 // 클래스 구조체 포인터 저장 변수
static struct device *sk_device; // 디바이스 구조체 포인터 저장 변수

#include <linux/delay.h>

static void buzzer_beep(int freq, int duration_ms)
{
    int i;
    int period_us;
    int half_period_us;
    int cycles;

    if (freq <= 0)
        return;

    period_us = 1000000 / freq;
    half_period_us = period_us / 2;
    cycles = duration_ms * 1000 / period_us;

    for (i = 0; i < cycles; i++) {
        gpio_set_value(GPIO_BZ, 1);
        udelay(half_period_us);
        gpio_set_value(GPIO_BZ, 0);
        udelay(half_period_us);
    }
}

static int sk_open(struct inode *inode, struct file *file)
{
	pr_info("BZ Device opened!\n");
	return 0;
}

static int sk_release(struct inode *inode, struct file *file)
{
	pr_info("BZ Device closed!\n");
	return 0;
}

static ssize_t sk_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int retval;

	if (*ppos > 0)
		return 0;

	kernel_buffer[0] = gpio_get_value(GPIO_BZ) ? '1' : '0';
	kernel_buffer[1] = '\0'; 

	if (count > BUFFER_SIZE)
		count = BUFFER_SIZE;

	retval = copy_to_user(buf, kernel_buffer, count);
	if (retval != 0)
	{
		pr_err("Failed to send data to user\n");
		return -EFAULT;
	}
	*ppos += count;
	return count;
}

static ssize_t sk_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int retval;

	if (count > BUFFER_SIZE - 1)
		count = BUFFER_SIZE - 1;
	retval = copy_from_user(kernel_buffer, buf, count);
	if (retval != 0)
	{
		pr_err("Failed to receive data from user \n");
		return -EFAULT;
	}
	kernel_buffer[count] = '\0';

	if (kernel_buffer[0] == '0') {
		gpio_set_value(GPIO_BZ, 0);
		pr_info("BUZZER OFF\n");
	} else if (kernel_buffer[0] == '1') {
		buzzer_beep(1000, 300);
		pr_info("BUZZER ON\n");
	}

	return count;
}

static const struct file_operations sk_fops = {
	.owner = THIS_MODULE,
	.open = sk_open,
	.release = sk_release,
	.read = sk_read,
	.write = sk_write,
};

static char *sk_devnode(const struct device *dev, umode_t *mode)
{
	if (mode)
	{
		*mode = 0666;
	}
	return NULL;
}

static int __init sk_init(void)
{
	int retval;

	pr_info("BZ Module is initializing...\n");

	retval = alloc_chrdev_region(&dev_num, 0, 1, "BZ_Driver");
	if (retval < 0)
	{
		pr_err("Failed to allocate device number\n");
		return retval;
	}

	cdev_init(&sk_cdev, &sk_fops);
	sk_cdev.owner = THIS_MODULE;

	retval = cdev_add(&sk_cdev, dev_num, 1);
	if (retval < 0)
		goto err_unregister_region;

	sk_class = class_create("buzz_class");
	if (IS_ERR(sk_class))
	{
		retval = PTR_ERR(sk_class);
		goto err_del_cdev;
	}
	sk_class->devnode = sk_devnode;

	sk_device = device_create(sk_class, NULL, dev_num, NULL, "BZdevice");
	if (IS_ERR(sk_device))
	{
		retval = PTR_ERR(sk_device);
		goto err_destroy_class;
	}

	retval = gpio_request(GPIO_BZ, "BUZZ");
	if (retval) {
		pr_err("gpio_request failed: GPIO=%d retval=%d\n", GPIO_BZ, retval);
		goto err_destroy_device;
	}
	gpio_direction_output(GPIO_BZ, 0);

	pr_info("BZ Module & /dev/BZdevice setup successfully completed! Major : %d\n", MAJOR(dev_num));
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

static void __exit sk_exit(void)
{
	pr_info("BZ Module is exiting....\n");

	device_destroy(sk_class, dev_num);
	class_destroy(sk_class);
	cdev_del(&sk_cdev);

	gpio_free(GPIO_BZ);

	unregister_chrdev_region(dev_num, MY_DEV_COUNT);
}

module_init(sk_init);
module_exit(sk_exit);

MODULE_LICENSE("GPL");