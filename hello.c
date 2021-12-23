#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <asm/io.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/cacheflush.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/sched.h>

struct hello
{
    dev_t devt;
    struct cdev cdev;

    struct class *hello_class;
    struct device *hello_device;

}hello_obj;

static int hello_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int hello_close(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t hello_write(struct file *filp, const char __user *buf, size_t count, loff_t *fops)
{

    return 0;
}

static ssize_t hello_read(struct file *filp, char __user *buf, size_t count, loff_t *fops)
{
    return 0;
}

static long hello_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    return 0;
}

static struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open = hello_open,
    .write = hello_write,
    .read = hello_read,
    .release = hello_close,
    .unlocked_ioctl = hello_ioctl,
};


static int atoi(const char *str)
{
	int value = 0;

	while (*str >= '0' && *str <= '9') {
		value *= 10;
		value += *str - '0';
		str++;
	}
	return value;
}

static ssize_t hello_test_show(struct class *class, struct class_attribute *attr,
    char *buf)
{
    printk("hello_test_show\n");
    return 0;
}


static ssize_t hello_test_store(struct class *class, struct class_attribute *attr,
    const char *buf, size_t count)
{
    int action = 0;
    
    action = atoi(buf);

    if(action == 1)
    {
    }
    else if(action == 2)
    {
    }
    else if(action == 3)
    {
    }
    else if(action == 4)
    {
    }
 
    return count;
}
CLASS_ATTR_RW(hello_test);
    
static int hello_init(void)
{
    struct hello *pObj = &hello_obj;
	int ret = 0;
    
    ret = alloc_chrdev_region(&pObj->devt, 0, 1, "hello");
    if(ret)
    {
        printk("alloc_chrdev_region fail! ret:%d\n",ret);
        return -1;
    }

    cdev_init(&pObj->cdev, &hello_fops);
    pObj->cdev.owner = THIS_MODULE;
    cdev_add(&pObj->cdev, pObj->devt, 1);

    pObj->hello_class = class_create(THIS_MODULE, "hello");
    pObj->hello_device = device_create(pObj->hello_class, NULL, pObj->devt, NULL, "hello");

    ret = class_create_file(pObj->hello_class, &class_attr_hello_test);

    printk("hello_init ...\n");
	return 0;
}

static void hello_exit(void)
{
    struct hello *pObj = &hello_obj;

    device_destroy(pObj->hello_class, pObj->devt);
    class_remove_file(pObj->hello_class, &class_attr_hello_test);
    class_destroy(pObj->hello_class);
    unregister_chrdev_region(pObj->devt, 1);
    
	printk("hello_exit ...\n");
}


module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");

