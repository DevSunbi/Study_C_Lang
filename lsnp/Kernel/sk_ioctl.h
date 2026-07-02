#ifndef SK_IOCTL_H
#define SK_IOCTL_H

#define IOCTL_MAGIC 'A'
#define SPEED_UP _IO(IOCTL_MAGIC, 1)
#define SPEED_DOWN _IO(IOCTL_MAGIC, 2)

#endif