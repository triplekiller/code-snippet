/*
 * =====================================================================================
 *
 *       Filename:  tasklist.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01/31/2015 04:01:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * =====================================================================================
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

/* List all the tasks in kernel */
static int init_tl(void)
{
	struct task_struct *task = &init_task;

	do {
		printk(KERN_INFO "#### %s(%d) parent %s\n", task->comm, task->pid,
			task->parent->comm);
	} while ((task = next_task(task)) != &init_task);

	printk(KERN_INFO "#### Current task is %s(%d)\n", current->comm, current->pid);

	return 0;
}

void exit_tl(void)
{
	return;
}

MODULE_AUTHOR("sanhust");
MODULE_LICENSE("GPL");
module_init(init_tl);
module_exit(exit_tl);
