#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#include <linux/device.h>

#include "data.h"

static dev_t hrtmod_dev;
struct cdev hrtmod_cdev;
static char buffer[64];
int ret;

struct class *myclass = NULL;

ssize_t hrtmod_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{	
	static int i =0;
	int d; 
	
	// index of the sample 
	i = (i+2048)%2048; 
	
	d= ppg[i]; 
	copy_to_user(buf,&d,4);

	i++;
	return ret;
}

struct file_operations hrtmod_fops = {
	.owner = THIS_MODULE,
	.read = hrtmod_read,
};

static int __init hrtmod_module_init(void)
{
	printk(KERN_INFO "Loading hrtmod_module\n");

	alloc_chrdev_region(&hrtmod_dev, 0, 1, "hrtmod_dev");
	printk(KERN_INFO "%s\n", format_dev_t(buffer, hrtmod_dev));

   	 myclass = class_create(THIS_MODULE, "hrtmod_sys");
 	 device_create(myclass, NULL, hrtmod_dev, NULL, "hrtmod_dev");

	cdev_init(&hrtmod_cdev, &hrtmod_fops);
	hrtmod_cdev.owner = THIS_MODULE;
	cdev_add(&hrtmod_cdev, hrtmod_dev, 1);
return 0;
}

static void __exit hrtmod_module_cleanup(void)
{
	printk(KERN_INFO "Cleaning-up hrtmod_dev.\n");
	    device_destroy(myclass, hrtmod_dev );

	cdev_del(&hrtmod_cdev);
	unregister_chrdev_region(hrtmod_dev, 1);
}

module_init(hrtmod_module_init);
module_exit(hrtmod_module_cleanup);
MODULE_AUTHOR("Massimo Violante");
MODULE_LICENSE("GPL");

