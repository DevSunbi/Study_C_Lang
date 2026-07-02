#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MY_MAJOR 200
#define MY_MINOR_BASE 0
#define MY_DEV_COUNT 1
#define MY_DEV_NAME "my_skeleton_dev"

static const struct file_operations sk_fops = {
    .owner = THIS_MODULE, // owner means struct module value address
};

static dev_t dev_num;
static struct cdev sk_cdev;


static int __init sk_init(void) {
    int retval;

    pr_info("SK Module is up\n");

    retval = alloc_chrdev_region(&dev_num, 0, 1, "SK_Driver"); // device num, minor start num, minor require num, device name
    // dynamically allocate character device numbers
    if(retval < 0) {
        pr_err("Failed to allocate device number\n");
        return retval;
    }

    cdev_init(&sk_cdev, &sk_fops); // device struct value address, file operations struct address
    sk_cdev.owner = THIS_MODULE;

    retval = cdev_add(&sk_cdev, dev_num, 1); // device struct value address, device number, minor count
    if(retval < 0) {
        pr_err("Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1); // device number, minor count
        return retval;
    }

    pr_info("Successfully registered major %d, minor %d\n", MY_MAJOR, MY_MINOR_BASE);
    return 0;
}

static void __exit sk_exit(void) {
    cdev_del(&sk_cdev);
    unregister_chrdev_region(dev_num, MY_DEV_COUNT);
    pr_info("Unregistered device number\n");
}

module_init(sk_init);
module_exit(sk_exit);
MODULE_LICENSE("GPL");