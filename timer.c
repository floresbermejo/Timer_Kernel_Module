/************************************************
* Este modulo lee el numero de  Ticks 	        *
* registrados por el sistema  desde que se      *
* inicio el mismo.                              *
************************************************/
/************************************************
* Includes                                      *
************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("FLores Bermejo, Humberto Isaac");
MODULE_DESCRIPTION("Ticks (Jeffies) Transcurridos");

/************************************************
* Variables                                     *
************************************************/
struct timer_list stimer;
/************************************************
* Time Handler                                  *
************************************************/
static void time_handler(unsigned long data)
{
	mod_timer(&stimer, jiffies + HZ);
	printk(KERN_INFO "\t Ticks trancurridos %ld\n", jiffies);
}

/************************************************
* Inicializacion                                *
************************************************/
static int __init timer_init(void)
{
	printk(KERN_ALERT "Timer Modulo agreado a Kernel\n");
	init_timer(&stimer);
	stimer.data = 0;
	stimer.expires = jiffies + HZ;
	stimer.function = time_handler;
	add_timer(&stimer);
	return 0;
}

/************************************************
* Exist                                         *
************************************************/
static void __exit timer_exit(void)
{
	printk(KERN_ALERT "Timer Modulo removido de Kernel\n");
	del_timer(&stimer);
}

module_init(timer_init);
module_exit(timer_exit);

