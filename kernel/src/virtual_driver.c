/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief virtual device driver
 * @name virtual_driver.hpp
 * 
 * 
 * /
/*****************************************************************************/


#include <linux/module.h>
#include <linux/fs.h>


typedef struct DriverInfo {
  dev_t dev_num;
} DriverInfo_t;

DriverInfo_t gDriverInfo;

/*****************************************************************************/

static int __init virtual_driver_init(void)
{
  /* Register device number */
  uint32_t ret = 0;
  gDriverInfo.dev_num =MKDEV(235, 0);
  ret = register_chrdev_region(gDriverInfo.dev_num, 1, "virtual_char_device");
  if (ret < 0)
  {
    printk("Failed to register device number.\n");
    goto failed_register_devnum;
  }
  printk("Initialize virtual driver successfully.\n");

  return 0;

failed_register_devnum:
  return ret; 
}

static void __exit virtual_driver_exit(void)
{
  /* unregister device number */
  unregister_chrdev_region(gDriverInfo.dev_num, 1);

  printk("Exit virtual driver.\n");
}


module_init(virtual_driver_init);
module_exit(virtual_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinhnt2410@gmail.com");
MODULE_VERSION("1.0");
