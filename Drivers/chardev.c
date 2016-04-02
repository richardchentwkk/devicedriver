//=======Include Header File=======//
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include "opcode.h"
//=======License Announcement=======//
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Richard Chen");
MODULE_DESCRIPTION("Char IO Control Driver!");
//=======Define==========//
#define DEVICE_NAME  "char_device_test"
#define MAJORNUM 	60
//=======Structure=======//
struct platform_device *gpdev;
//=======Platform_Device_Structure=====================//
struct platform_device chardevice1 = 
{
	.name= "char_dev",
	.id=-1,
};
static struct platform_device __initdata *chardevice[]=
{
&chardevice1,
};
//=======Char IO Control Functions=====================//
static int char_ioctl(struct inode *inode,struct file *filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case IOCTL_WRITE:
		printk("IO Control\n");
		break;
	}
	return 0;
};
//=======File Operations Structure=====================//
static struct file_operations fops =
{
	.owner	= THIS_MODULE,
	.ioctl	= char_ioctl,
};
//=======Char_Probe_Function===========================//
static int char_probe(struct platform_device *pdev)
{
	int ret	=0;
	printk("Start Char_Probe\n");
	ret = register_chrdev(MAJORNUM,DEVICE_NAME,&fops);
	if (ret<0)
		{
				printk("Register Error!\n");
		}
		gpdev=pdev;
	return 0 ;
}
//=======Platform_Driver_Structure=====================//
static struct platform_driver chrdev_driver=
{
	.driver ={
	 .name  = "char_dev",
	 .owner = THIS_MODULE,
	},
	.probe	= char_probe,
};
//=======Initial Function========//
static int __init ioctltest_init(void)
{
	printk("Begin Driver Init_Richard\n");
	printk("Start Platform Device Add!_Richard\n");
//======Add Devices==============//
	platform_add_devices(chardevice,1);
//===================================================	
	printk("Finished to add device_Richard\n");
	printk("Start to register driver_Richard\n");
//======Platform_Register_Device_Driver==============
	platform_driver_register(&chrdev_driver);
//===================================================
	printk("Driver Register Successful!\n");
	return 0;
}
//=======Release Driver Function=====//
static void ioctltest_exit(void)
{		
	printk("Start Release Driver\n");
	platform_device_unregister(gpdev);
	platform_driver_unregister(&chrdev_driver);
	unregister_chrdev(MAJORNUM,DEVICE_NAME);
	printk("Test finished,exit!_Richard\n");
}
//=======Load and unload Module======//
module_init(ioctltest_init);	//==Load====Module======//
module_exit(ioctltest_exit);	//==Release=Module=======//


