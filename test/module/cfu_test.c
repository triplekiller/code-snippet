/*
 * =====================================================================================
 *
 *       Filename:  cfu-test.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/23/2014 02:47:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */
#include <linux/module.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

MODULE_AUTHOR("Ethan Xia");
MODULE_DESCRIPTION("test copy_from_usr memory leak");
MODULE_LICENSE("GPL v2");

#define CFU_DEV_NAME "cfu_test"

static int cfu_major = 0;

static int cfu_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
	unsigned long arg)
{
	int ret;

	switch (cmd) {
	case :
	}

}

static int cfu_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int cfu_release(struct inode *inode, struct file *file)
{
	return 0;
}

struct file_operations cfu_ops = {
	.ioctl = cfu_ioctl,
	.open = cfu_open,
	.release = cfu_release
};

int __init cfu_init(void)
{
	int ret;

	ret = register_chrdev(cfu_major, CFU_DEV_NAME, &cfu_ops);
	if (ret < 0) {
		printk("register_chrdev failed\n");
		return ret;
	}

	return 0;
}

void __exit cfu_exit(void)
{
	unregister_chrdev(cfu_major, CFU_DEV_NAME);

	return;
}

module_init(cfu_init);
module_exit(cfu_exit);
