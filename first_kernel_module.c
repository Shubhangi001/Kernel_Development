#include <linux/init.h> 
#include <linux/module.h> //module_init and module_exit macros
MODULE_LICENSE("Dual BSD/GPL"); //license
static int __init hello(void) //invoked when module is loaded
{
 pr_info("Hello, world\n");
 return 0;
}
static void hello_exit(void) //invoked when module is unloaded
{
 pr_info("Goodbye, cruel world\n"); //pr_info is a macro defined in linux/kernel.h
}
module_init(hello);  //macro to register hello function as init function
module_exit(hello_exit); //macro to register hello_exit as exit function

/**
#define pr_info(fmt,arg...) \
    printk(KERN_INFO fmt,##arg)
**/