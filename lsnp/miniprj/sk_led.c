#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/gpio.h>

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

volatile unsigned *gpio; /* I/O 접근을 위한 volatile 변수 */

#define MY_MAJOR 200
#define MY_MINOR_BASE 0
#define MY_DEV_COUNT 1
#define MY_DEV_NAME "my_skeleton_dev"
#define BUFFER_SIZE 1024
#define GPIO_LED 530

static dev_t dev_num;
static struct cdev sk_cdev;
static struct class *sk_class;
static struct device *sk_device;
static char kernel_buffer[BUFFER_SIZE];

static int sk_open(struct inode *inode, struct file *file)
{
    pr_info("SK Device opened!\n");
    //GPIO_OUT(GPIO_LED);
    gpio_direction_output(GPIO_LED, 0);
    return 0;
}

static int sk_release(struct inode *inode, struct file *file)
{
    pr_info("SK Device released!\n");
    return 0;
}

static ssize_t sk_write(struct file *file, const char __user *buf,
                        size_t count, loff_t *ppos)
{
    size_t len;
    unsigned long not_copied;

    len = min(count, (size_t)(BUFFER_SIZE - 1));
    memset(kernel_buffer, 0, BUFFER_SIZE);

    not_copied = copy_from_user(kernel_buffer, buf, len);
    if (not_copied != 0) {
        pr_err("copy_from_user failed\n");
        return -EFAULT;
    }

    kernel_buffer[len] = '\0';

    if (kernel_buffer[0] == '0') {
        gpio_set_value(GPIO_LED, 0);
        pr_info("LED OFF\n");
    } else if (kernel_buffer[0] == '1') {
        gpio_set_value(GPIO_LED, 1);
        pr_info("LED ON\n");
    } else {
        pr_info("Invalid command: %s\n", kernel_buffer);
    }

    pr_info("*GPIO Device(%d) write : %s\n",
            MAJOR(dev_num), kernel_buffer);

    return len;
}

static ssize_t sk_read(struct file *file, char __user *buf,
                       size_t count, loff_t *ppos)
{
    size_t len;
    unsigned long not_copied;

    if (*ppos > 0)
        return 0;

    len = strlen(kernel_buffer);
    len = min(len, count);

    not_copied = copy_to_user(buf, kernel_buffer, len);
    if (not_copied != 0)
        return -EFAULT;

    *ppos += len;

    pr_info("*GPIO Device(%d) read : %s\n",
            MAJOR(dev_num), kernel_buffer);

    return len;
}


static char *my_devnode(const struct device *dev, umode_t *mode) {
    if(mode) {
        *mode=0666;
    }
    return NULL;
}

// long sk_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
//     switch(cmd) {
//         case SPEED_UP:{
//             printk("\n");printk("UP\n");break;
//         }
//         case SPEED_DOWN:{
//             printk("\n");printk("DOWN\n");break;
//         }
//         default:
//             return 0;
//     }
//     return 0;
// }

static const struct file_operations sk_fops = {
    .owner = THIS_MODULE, // owner means struct module value address
    .open = sk_open,
    .release = sk_release,
    .read = sk_read,
    .write = sk_write,
    //.unlocked_ioctl = sk_ioctl,
};

static int __init sk_init(void)
{
    int retval;
    static void *map;
    pr_info("SK Module is initializing\n");

    retval = alloc_chrdev_region(&dev_num, 0, 1, "SK_Driver"); // device num, minor start num, minor require num, device name
    // dynamically allocate character device numbers
    if(retval < 0) {
        pr_err("Failed to allocate device number\n");
        return retval;
    }

    cdev_init(&sk_cdev, &sk_fops); // device struct value address, file operations struct address
    sk_cdev.owner = THIS_MODULE;

    retval = cdev_add(&sk_cdev, dev_num, 1);
    if(retval < 0) goto err_unregister_region;

    sk_class = class_create("sk_class");
    
    if(IS_ERR(sk_class)) {
        retval = PTR_ERR(sk_class);
        goto err_del_cdev;
    }
    sk_class -> devnode = my_devnode;

    sk_device = device_create(sk_class, NULL, dev_num, NULL, "LED");
    if(IS_ERR(sk_device)) {
        retval = PTR_ERR(sk_device);
        goto err_destroy_class;
    }

    pr_info("SK Module & /dev/SK setup successfully completed! Major:%d\n", MAJOR(dev_num));
    
    // map = ioremap(GPIO_BASE, GPIO_SIZE);
    // if(!map) {
    //     printk("Error : mapping GPIO memory\n");
    //     iounmap(map);
    //     return -EBUSY;
    // }

    // gpio = (volatile unsigned int *)map;

    // GPIO_IN(GPIO_LED);
    // GPIO_OUT(GPIO_LED);

    retval = gpio_request(GPIO_LED, "LED");
    if (retval) {
        pr_err("gpio_request failed: GPIO=%d retval=%d\n", GPIO_LED, retval);
        goto err_destroy_device;
    }

    return 0;


err_destroy_device:     
    device_destroy(sk_class, dev_num);

err_destroy_class:
    class_destroy(sk_class);

err_del_cdev:
    cdev_del(&sk_cdev);

err_unregister_region:
    unregister_chrdev_region(dev_num, MY_DEV_COUNT);
    return retval;
}

static void __exit sk_exit(void)
{
    device_destroy(sk_class, dev_num);
    class_destroy(sk_class);
    cdev_del(&sk_cdev);
    unregister_chrdev_region(dev_num, MY_DEV_COUNT);
    pr_info("SK Module unloaded successfully\n");
}

module_init(sk_init);
module_exit(sk_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple character device driver");