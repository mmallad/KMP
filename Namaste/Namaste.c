//First Kernel Module Showing The Basic Structure the 
//Kernel Module Programming
//Dpak Malla
//mmallad

//First Define __KERNEL__ and MODULE (Its not really necessary)
//__KERNEL__ and MODULE will help us to access kernel level code
#undef __KERNEL__
#define __KERNEL__

#undef MODULE
#define MODULE

//Let us include some necessary headers :)
#include <linux/module.h> //For all kernel modules
#include <linux/kernel.h> //Necessary for KERN_INFO Macro
#include <linux/init.h> //Necessary for __init and __exit macros

static int __init namaste_init(void)
{
	printk(KERN_INFO "Namaste World!\n");
	return 0;
}
static void __exit namaste_exit(void)
{
	printk(KERN_INFO "Dhanyabad!\n");
}

module_init(namaste_init); //Tells that namaste_init is the entry point
module_exit(namaste_exit); //Tells that namaste_exit should be called when module is removed
