#ifndef CHAR_H
#define CHAR_H
//Dipak Malla
//mmallad
//Character Device Driver Example with
//Licensing and Module Documentation

//Lets us include necessary header files.
#include <linux/module.h> /* Needed for all modules  */
#include <linux/kernel.h> /* As we are doing kernel work :)  */
#include <linux/init.h> /* For Macros Like __init, __exit  */
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
//Define prototypes

#define AUTHOR "Dipak Malla"
#define DESC  "This is test character device example. :)"
#define LICENSE_TYPE  "GPL"

#define DEVICE_NAME  "mychardevice"
#define BUFFER_LENGTH  88
//Entry Point for the module
static int __init start(void);
//Exit Point for the module
static void __exit end(void);

static int device_open(struct inode *, struct file *);
static int device_close(struct inode *, struct file *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
#endif // CHAR_H
