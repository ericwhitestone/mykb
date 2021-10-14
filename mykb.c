
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL v2");

static dev_t my_device;
static struct
{
    int i;
} device_info;

static irqreturn_t mykb_isr(int irq, void *device_info)
{
    printk(KERN_ALERT "Playing with fire\n");
    return IRQ_HANDLED;
}

static int mykb_init(void)
{
    char buffer[256];
    int retval;
    int irq;

    printk(KERN_INFO "Initializing mykb\n");
    retval = alloc_chrdev_region(&my_device, 0, 1, "mykb");
    if (retval == 0)
    {
        printk(KERN_INFO "Successfully registered char dev device\n");
        print_dev_t(buffer, my_device);
        printk(KERN_INFO "mykb device: %s\n", buffer);
        irq = request_irq(0x01, mykb_isr, IRQF_SHARED, "mykb", &device_info);
        if (irq != 0)
        {
            goto irq_fail;
        }
    }
    else
    {
        goto register_failed;
    }
    return 0;
register_failed:
    printk(KERN_ALERT "Failed registering char device for mykb\n");
    return -ENOMEM;
irq_fail:
    printk(KERN_ALERT "failed registering the irq");
    return -EBUSY;
}

static void mykb_exit(void)
{
    printk(KERN_ALERT "mykb exiting\n");
    unregister_chrdev_region(my_device, 1);
    free_irq(0x01, &device_info);
}

module_init(mykb_init);
module_exit(mykb_exit);