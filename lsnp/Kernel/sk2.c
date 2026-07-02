#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include "sk_ioctl.h"

#define MY_MAJOR 200
#define MY_MINOR_BASE 0
#define MY_DEV_COUNT 1
#define MY_DEV_NAME "my_skeleton_dev"
#define BUFFER_SIZE 1024

static dev_t dev_num;
static struct cdev sk_cdev;
static struct class *sk_class;
static struct device *sk_device;
static char kernel_buffer[BUFFER_SIZE];

static int sk_open(struct inode *inode, struct file *file)
{
    pr_info("SK Device opened!\n");
    return 0;
}

static int sk_release(struct inode *inode, struct file *file)
{
    pr_info("SK Device released!\n");
    return 0;
}

static ssize_t sk_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    int retval;
    if (count > BUFFER_SIZE - 1) count = BUFFER_SIZE - 1;
    retval = copy_from_user(kernel_buffer, buf, count);
    if (retval != 0) {
        pr_err("Failed to receive data from user\n");
        return -EFAULT;
    }
    kernel_buffer[count] = '\0'; /* 문자열의 끝 표시 */
    pr_info("Received from user: %s", kernel_buffer);
    return count;
}

static ssize_t sk_read(struct file *file, char __user* buf, size_t count, loff_t* ppos) {
    int retval;

    if(*ppos > 0) return 0;

    if(count > BUFFER_SIZE) count = BUFFER_SIZE;

    retval = copy_to_user(buf, kernel_buffer, count);
    if(retval != 0) {
        pr_err("Failed to send data to user\n");
        return -EFAULT;
    }
    *ppos += count;
    pr_info("Sent %zu bytes to user\n", count);

    return count;
}


static char *my_devnode(const struct device *dev, umode_t *mode) {
    if(mode) {
        *mode=0666;
    }
    return NULL;
}

long sk_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    switch(cmd) {
        case SPEED_UP:{
            printk("\n");printk("UP\n");break;
        }
        case SPEED_DOWN:{
            printk("\n");printk("DOWN\n");break;
        }
        default:
            return 0;
    }
    return 0;
}

static const struct file_operations sk_fops = {
    .owner = THIS_MODULE, // owner means struct module value address
    .open = sk_open,
    .release = sk_release,
    .read = sk_read,
    .write = sk_write,
    .unlocked_ioctl = sk_ioctl,
};

static int __init sk_init(void)
{
    int retval;
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

    sk_device = device_create(sk_class, NULL, dev_num, NULL, "SK");
    if(IS_ERR(sk_device)) {
        retval = PTR_ERR(sk_device);
        goto err_destroy_class;
    }

    pr_info("SK Module & /dev/SK setup successfully completed! Major:%d\n", MAJOR(dev_num));
    return 0;


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