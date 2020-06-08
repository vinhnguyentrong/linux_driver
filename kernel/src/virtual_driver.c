/*****************************************************************************/
#include <linux/module.h>



#define DRIVER_AUTHOR "Vinh Nguyen Trong <vinhnt2410@gmail.com>"
#define DRIVER_VERSION "1.0"

/*****************************************************************************/

static int __init virtual_driver_init(void)
{
  printk("Initialize virtual driver successfully.\n");
  return 0; 
}

static void __exit virtual_driver_exit(void)
{
  printk("Exit virtual driver.\n");
}


module_init(virtual_driver_init);
module_exit(virtual_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_VERSION(DRIVER_VERSION);
