
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>

MODULE_LICENSE("GPL v2");

static int mykb_init(void)
{
    dev_t my_device;
    char buffer[256];
    int retval;

    printk(KERN_INFO "Initializing mykb\n");
    retval = alloc_chrdev_region(&my_device, 0, 1, "mykb");
    if (retval == 0)
    {
        printk(KERN_INFO "Successfully registered char dev device\n");
        print_dev_t(buffer, my_device);
        printk(KERN_INFO "mykb device: %s\n", buffer);
    }
    else
    {
        goto register_failed;
    }
    return 0;

register_failed:
    printk(KERN_ALERT "Failed registering char device for mykb\n");
    return -1;
}

static void mykb_exit(void)
{
    printk(KERN_ALERT "mykb exiting\n");
}

module_init(mykb_init);
module_exit(mykb_exit);