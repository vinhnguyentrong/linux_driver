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
#include <linux/fs.h>         // for allocate and unallocate device number
#include <linux/device.h>     // for create device file
#include <linux/slab.h>       // for kmalloc and kfree function

#include "virtual_driver.h"
#include "kdb_log.h"


/*****************************************************************************/
/** 
 * @brief Defines struct of a virtual device
 * 
 *****************************************************************************/
typedef struct 
{
  dev_t mDevNum;      // device number
  struct class *mpDevClass;
  struct device *mpDev;
  DEVICE_REGS_t *mpRegs;
  
} DriverInfo_t;

DriverInfo_t gDriverInfo;

/*****************************************************************************/

uint32_t vir_drv_init(DriverInfo_t *apDriverInfo)
{
  uint16_t *lpBuffer = NULL;
  lpBuffer = kzalloc(sizeof(DEVICE_REGS_t), GFP_KERNEL);
  if(lpBuffer == NULL)
  {
    return -ENOMEM;
  }
  apDriverInfo->mpRegs = (DEVICE_REGS_t*)lpBuffer;

  /* init registers */
  // allow read/write from/to data register
  apDriverInfo->mpRegs->mCTRL_RW.R = 0x03U;
  // ready for read/write
  apDriverInfo->mpRegs->mSTS_RW.R = 0x03U;

  return 0;
}

uint32_t vir_drv_exit(DriverInfo_t *apDriverInfo)
{
  kfree(apDriverInfo->mpRegs);
  return 0;
}

static int __init virtual_driver_init(void)
{
  /* Register device number */
  uint32_t ret = 0;
  gDriverInfo.mDevNum =MKDEV(235, 0);
  // ret = register_chrdev_region(gDriverInfo.mDevNum, 1, "virtual_char_device");
  ret = alloc_chrdev_region(&gDriverInfo.mDevNum, 0, 1, "virtual_char_device");
  if (ret < 0)
  {
    KDB_LOG_NOTE1("Failed to register device number.\n");
    goto failed_register_devnum;
  }

  /* Create device file */
  gDriverInfo.mpDevClass = class_create(THIS_MODULE, "virtul_device_class");
  if(gDriverInfo.mpDevClass == NULL)
  {
    KDB_LOG_ERR1("Failed to create a device class.\n");
    goto failed_create_class;
  }
  gDriverInfo.mpDev = device_create(gDriverInfo.mpDevClass, 
        NULL, gDriverInfo.mDevNum, NULL, "virtual_device");
  if(gDriverInfo.mpDev == NULL)
  {
    KDB_LOG_ERR1("Failed to create a device.\n");
    goto failed_create_device;
  }

  /* Init device hardware */
  ret = vir_drv_init(&gDriverInfo);
  if(ret != 0)
  {
    KDB_LOG_ERR1("Failed to initialize a virtual device.\n");
    goto failed_init_hw;
  }

  KDB_LOG_NOTE1("Initialize virtual driver successfully.\n");

  return 0;
failed_init_hw:
  vir_drv_exit(&gDriverInfo);
failed_create_device:
  device_destroy(gDriverInfo.mpDevClass, gDriverInfo.mDevNum);
failed_create_class:
  class_destroy(gDriverInfo.mpDevClass);
failed_register_devnum:
  return ret; 
}

static void __exit virtual_driver_exit(void)
{
  vir_drv_exit(&gDriverInfo);
  /* delete device file */
  device_destroy(gDriverInfo.mpDevClass, gDriverInfo.mDevNum);
  class_destroy(gDriverInfo.mpDevClass);
  /* unregister device number */
  unregister_chrdev_region(gDriverInfo.mDevNum, 1);

  KDB_LOG_NOTE1("Exit virtual driver successfully.\n");

}

module_init(virtual_driver_init);
module_exit(virtual_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinhnt2410@gmail.com");
MODULE_VERSION("1.0");
