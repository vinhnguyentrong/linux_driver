/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief virtual device driver
 * @name virtual_driver.hpp
 * 
 * 
 * 
 *****************************************************************************/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>

/*****************************************************************************/
/** 
 * @brief Defines struct of a virtual device
 * 
 *****************************************************************************/
typedef struct 
{
  dev_t dev_num;      // device number
  struct class *dev_class;
  struct device *dev;
} DriverInfo_t;

DriverInfo_t gDriverInfo;

/*****************************************************************************/

static int __init virtual_driver_init(void)
{
  /* Register device number */
  uint32_t ret = 0;
  gDriverInfo.dev_num =MKDEV(235, 0);
  // ret = register_chrdev_region(gDriverInfo.dev_num, 1, "virtual_char_device");
  ret = alloc_chrdev_region(&gDriverInfo.dev_num, 0, 1, "virtual_char_device");
  if (ret < 0)
  {
    printk("Failed to register device number.\n");
    goto failed_register_devnum;
  }

  /* Create device file */
  gDriverInfo.dev_class = class_create(THIS_MODULE, "virtul_device_class");
  if(gDriverInfo.dev_class == NULL)
  {
    printk("Failed to create a device class.\n");
    goto failed_create_class;
  }
  gDriverInfo.dev = device_create(gDriverInfo.dev_class, 
        NULL, gDriverInfo.dev_num, NULL, "virtual_device");
  if(gDriverInfo.dev == NULL)
  {
    printk("Failed to create a device.\n");
    goto failed_create_device;
  }

  printk("Initialize virtual driver successfully.\n");

  return 0;

failed_create_device:
  device_destroy(gDriverInfo.dev_class, gDriverInfo.dev_num);
failed_create_class:
  class_destroy(gDriverInfo.dev_class);
failed_register_devnum:
  return ret; 
}

static void __exit virtual_driver_exit(void)
{
  /* delete device file */
  device_destroy(gDriverInfo.dev_class, gDriverInfo.dev_num);
  class_destroy(gDriverInfo.dev_class);
  /* unregister device number */
  unregister_chrdev_region(gDriverInfo.dev_num, 1);

  printk("Exit virtual driver.\n");
}


module_init(virtual_driver_init);
module_exit(virtual_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinhnt2410@gmail.com");
MODULE_VERSION("1.0");
