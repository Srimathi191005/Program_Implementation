#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/string.h>

#define DEVICE_NAME "mychardev"
#define CLASS_NAME "mycharclass"
#define BUFFER_SIZE 1024

static dev_t dev_num;
static struct cdev my_cdev;
static struct class *my_class;
static struct device *my_device;

static char kernel_buffer[BUFFER_SIZE];
static size_t data_size;

static int mychardev_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "mychardev: Device Opened\n");
    return 0;
}

static int mychardev_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "mychardev: Device Closed\n");
    return 0;
}

static ssize_t mychardev_write(struct file *file,
                               const char __user *buffer,
                               size_t len,
                               loff_t *offset)
{
    size_t bytes_to_copy;

    bytes_to_copy = len;

    if (bytes_to_copy >= BUFFER_SIZE)
        bytes_to_copy = BUFFER_SIZE - 1;

    if (copy_from_user(kernel_buffer, buffer, bytes_to_copy))
        return -EFAULT;

    kernel_buffer[bytes_to_copy] = '\0';
    data_size = bytes_to_copy;

    printk(KERN_INFO "mychardev: Data Written\n");

    return bytes_to_copy;
}

static ssize_t mychardev_read(struct file *file,
                              char __user *buffer,
                              size_t len,
                              loff_t *offset)
{
    size_t bytes_to_copy;

    if (*offset >= data_size)
        return 0;

    bytes_to_copy = data_size - *offset;

    if (len < bytes_to_copy)
        bytes_to_copy = len;

    if (copy_to_user(buffer, kernel_buffer + *offset, bytes_to_copy))
        return -EFAULT;

    *offset += bytes_to_copy;

    printk(KERN_INFO "mychardev: Data Read\n");

    return bytes_to_copy;
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = mychardev_open,
    .read = mychardev_read,
    .write = mychardev_write,
    .release = mychardev_release
};

static int __init mychardev_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);

    if (ret < 0)
    {
        printk(KERN_ALERT "mychardev: Device registration failed\n");
        return ret;
    }

    cdev_init(&my_cdev, &fops);

    ret = cdev_add(&my_cdev, dev_num, 1);

    if (ret < 0)
    {
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    my_class = class_create(CLASS_NAME);

    if (IS_ERR(my_class))
    {
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(my_class);
    }

    my_device = device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME);

    if (IS_ERR(my_device))
    {
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(my_device);
    }

    printk(KERN_INFO "mychardev: Module loaded\n");
    printk(KERN_INFO "mychardev: Device created at /dev/%s\n", DEVICE_NAME);

    return 0;
}

static void __exit mychardev_exit(void)
{
    device_destroy(my_class, dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "mychardev: Module unloaded\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Simple Character Device Driver");
