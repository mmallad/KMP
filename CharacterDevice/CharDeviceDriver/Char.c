#include "Char.h"


//Define some global varaibles

static int major;
//Will be used to check if device is already opened.
static int isDeviceOpen = 0;

static int return_value  = -1;

static struct cdev *my_dev;
dev_t device_num;

//Tell Kernel which function should be invoked when the processor start operations on device.
static struct file_operations fops  = {
    .owner = THIS_MODULE,
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_close
};
struct dev_info
{
    char msg[100];
} myDev;

static int __init start(void)
{
    //First Register the device.
    return_value = alloc_chrdev_region(&device_num,0,1,DEVICE_NAME);
    //major = register_chrdev(0,DEVICE_NAME,&fops);
    if(return_value < 0)
    {
        printk(KERN_ALERT "Major Number Allocation Failed\n");
        return return_value;
    }
    //Now We can use device creating device file in /dev with mknod command
    major = MAJOR(device_num);
    printk(KERN_INFO "Now You can create device file inside /dev with name %s and with major %d\n",DEVICE_NAME,major);
    printk(KERN_INFO "Example: (mknod /dev/%s c %d 0)\n",DEVICE_NAME,major);

    my_dev = cdev_alloc();
    my_dev->ops = &fops;
    my_dev->owner = THIS_MODULE;
    return_value = cdev_add(my_dev,device_num,1);
    if(return_value < 0)
    {
        printk(KERN_ALERT "Oops could not add cdev to kernel.");
        return return_value;
    }
    return 0;
}
//Clean Up Module
static void __exit end(void)
{
    cdev_del(my_dev);
    unregister_chrdev_region(device_num,1);
    printk(KERN_ALERT "Device unregister %s with Major Number %d",DEVICE_NAME,major);
}
//Will be called when process tries to open the device.
static int device_open(struct inode *inode, struct file *file)
{
    if(isDeviceOpen)
        return -EBUSY;
    isDeviceOpen++;
    printk(KERN_INFO "Okie I am open now. I am device with name %s. You can read and write to me :)\n",DEVICE_NAME);
    return 0;
}
//Will be called when  process tries to close the device
static int device_close(struct inode *inode, struct file *file)
{
    isDeviceOpen--;
    printk("Okie I am closed now.\n");
    return 0;
}
//Will be called when process try to write to the device.
static ssize_t device_write(struct file *fil_p, const char* buffData, size_t buuferLen, loff_t *off)
{
    printk(KERN_INFO "I am writing to device %s now.\n",DEVICE_NAME);
    return_value =  copy_from_user(myDev.msg,buffData,buuferLen);
    return return_value;
}
//Will be called when process try to read from the device
static ssize_t device_read(struct file *fil_p, char* buff, size_t len, loff_t *off)
{
    printk(KERN_INFO "I am reading from device %s now.\n",DEVICE_NAME);
    return_value =  copy_to_user(buff,myDev.msg,len);
    return return_value;
}

MODULE_LICENSE(LICENSE_TYPE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_SUPPORTED_DEVICE(DEVICE_NAME);

//Now let use tell the kernel about start and end of module.
module_init(start);
module_exit(end);
