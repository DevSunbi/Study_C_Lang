#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

#define GPIO_LED 530
#define GPIO_BZ 539
#define GPIO_BTN1 534
#define GPIO_BTN2 522

#define BLINK_INTERVAL_MS 100

#define DEVICE_NAME "alarm_device"
#define CLASS_NAME  "alarm_class"

static dev_t dev_num;
static struct cdev alarm_cdev;
static struct class *alarm_class;

static int irq_btn1;
static int irq_btn2;

static struct timer_list blink_timer;

static bool alarm_on = false;
static bool led_state = false;


static void buzzer_beep(int freq, int duration_ms) {
    int i;
    int period_us;
    int half_period_us;
    int cycles;
    
    if (freq <=0) return;
    
    period_us = 1000000 / freq;
    half_period_us = period_us / 2;
    cycles = duration_ms * 1000 / period_us;
    
    for (i = 0; i < cycles; i++){
        gpio_set_value(GPIO_BZ, 1);
        udelay(half_period_us);
        gpio_set_value(GPIO_BZ, 0);
        udelay(half_period_us);
    }

}

// static void blink_timer_func(struct timer_list *t) {
//     unsigned long flags;

//     if(alarm_on) {
//         led_state = !led_state;
//         gpio_set_value(GPIO_LED, led_state ? 1 : 0);
//         mod_timer(&blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));
//     }
// }

// static void blink_timer_func(struct timer_list *t) {
//     if (alarm_on) {
//         led_state = !led_state;
//         gpio_set_value(GPIO_LED, led_state ? 1 : 0);
        
//         // LED가 켜질 때 부저를 100ms 동안 1000Hz로 삡- 울려줍니다.
//         if (led_state) {
//             buzzer_beep(500, 20); 
//         }
        
//         // 500ms 마다 타이머 재등록
//         mod_timer(&blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));
//     }
// }

static void blink_timer_func(struct timer_list *t) 
{
    static int pattern = 0;

    if (alarm_on) {
        led_state = !led_state;
        gpio_set_value(GPIO_LED, led_state ? 1 : 0);

        /*
         * 삐비비비빅 느낌:
         * 짧고 높은 소리 여러 개 + 마지막 낮고 긴 소리
         */
        switch (pattern) {
        case 0:
            buzzer_beep(1500, 30);
            break;
        case 1:
            buzzer_beep(2200, 20);
            break;
        case 2:
            buzzer_beep(1800, 20);
            break;
        case 3:
            buzzer_beep(2500, 15);
            break;
        case 4:
            buzzer_beep(900, 80);
            break;
        }

        pattern = (pattern + 1) % 5;

        mod_timer(&blink_timer, jiffies + msecs_to_jiffies(150));
    }
}


static irqreturn_t btn1_irq_handler(int irq, void *dev_id) {
    alarm_on = true;
    led_state = true;
    
    gpio_set_value(GPIO_LED, 1);
    
    // 처음에 즉시 소리가 나도록 한 번 울려줍니다.
    buzzer_beep(1000, 100);
    
    // 타이머 시동
    mod_timer(&blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));

    pr_info("alarm_device : Intrusion Detected, LED/BUZZ Start\n");
    return IRQ_HANDLED;
}



static irqreturn_t btn2_irq_handler(int irq, void *dev_id) {
    alarm_on = false;
    
    gpio_set_value(GPIO_BZ, 0);
    gpio_set_value(GPIO_LED, 0);
    
    // 현재 동작 중인 타이머가 있다면 취소
    del_timer(&blink_timer);
    
    pr_info("alarm_device : Alarm Cleared! BUZZ Off, LED off\n");
    return IRQ_HANDLED;
}


static ssize_t alarm_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    char kbuf[32];
    int len;
    bool state;
    unsigned long flags;

    state = alarm_on;

    if(*ppos > 0) return 0;

    len = scnprintf(kbuf, sizeof(kbuf), "alarm=%d\n", state ? 1 : 0);

    if(copy_to_user(buf, kbuf, len)) {
        return -EFAULT;
    }

    *ppos += len;
    return len;
}

static ssize_t alarm_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    char kbuf[16];
    size_t len = min(count, sizeof(kbuf) - 1);
    unsigned long flags;

    if(copy_from_user(kbuf, buf, len)) return -EFAULT;

    kbuf[len] = '\0';

    if(kbuf[0] == '1') {
        alarm_on = true;
        buzzer_beep(1000, 300);
        led_state = true;
        gpio_set_value(GPIO_LED, 1);
        mod_timer(&blink_timer, jiffies + msecs_to_jiffies(BLINK_INTERVAL_MS));
        pr_info("alarm_device : Alarm Manual ON\n");
    } else if(kbuf[0] == '0') {
        alarm_on = false;
        gpio_set_value(GPIO_BZ, 0);
        gpio_set_value(GPIO_LED, 0);
        del_timer(&blink_timer);
    }

    return count;
}

static int alarm_open(struct inode *inode, struct file *file) {
    return 0;
}

static int alarm_release(struct inode *inode, struct file *file) {
    return 0;
}

static const struct file_operations alarm_fops = {
    .owner = THIS_MODULE,
    .open = alarm_open,
    .release = alarm_release,
    .read = alarm_read,
    .write = alarm_write,
};

static char *alarm_devnode(const struct device *dev, umode_t *mode) {
    if(mode) {
        *mode = 0666;
    }
    return NULL;
}

static int __init alarm_device_init(void)
{ 
    int ret;

    timer_setup(&blink_timer, blink_timer_func, 0);

    gpio_request(GPIO_LED, "alarm_led");
    gpio_direction_output(GPIO_LED, 0);

    gpio_request(GPIO_BZ, "alarm_buzzer");
    gpio_direction_output(GPIO_BZ, 0);
    
    gpio_request(GPIO_BTN1, "alarm_btn_intrude");
    gpio_direction_input(GPIO_BTN1);

    gpio_request(GPIO_BTN2, "alarm_btn_clear");
    gpio_direction_input(GPIO_BTN2);

    irq_btn1 = gpio_to_irq(GPIO_BTN1);
    request_irq(irq_btn1, btn1_irq_handler, IRQF_TRIGGER_RISING, "alarm_intrude_irq", NULL);

    irq_btn2 = gpio_to_irq(GPIO_BTN2);
    request_irq(irq_btn2, btn2_irq_handler, IRQF_TRIGGER_RISING, "alarm_clear_irq", NULL);

    alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    cdev_init(&alarm_cdev, &alarm_fops);
    cdev_add(&alarm_cdev, dev_num, 1);

    alarm_class = class_create(CLASS_NAME);
    alarm_class -> devnode = alarm_devnode;
    
    device_create(alarm_class, NULL, dev_num, NULL, DEVICE_NAME);

    pr_info("alarm_device : Module Loaded, /dev/%s created\n", DEVICE_NAME);

    return 0;
} 

static void __exit alarm_device_exit(void)
{
    device_destroy(alarm_class, dev_num);
    class_destroy(alarm_class);
    cdev_del(&alarm_cdev);
    unregister_chrdev_region(dev_num, 1);

    free_irq(irq_btn2, NULL);
    free_irq(irq_btn1, NULL);

    del_timer_sync(&blink_timer);

    gpio_free(GPIO_BTN2);
    gpio_free(GPIO_BTN1);
    gpio_free(GPIO_BZ);
    gpio_free(GPIO_LED);

    pr_info("alarm_device : Module unloaded\n");
}

module_init(alarm_device_init);
module_exit(alarm_device_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sunbi");
MODULE_DESCRIPTION("Intrusion Detection System Kernel Driver");