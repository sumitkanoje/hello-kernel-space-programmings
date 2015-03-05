#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Sumit Knoje");
MODULE_DESCRIPTION("A Simple Hello World module");

static int hello_init(void)
{
    printk(KERN_INFO "Hello World!\n");
    return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
