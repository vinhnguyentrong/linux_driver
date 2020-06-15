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
#include <linux/cdev.h>       // for function related to cdev struct
#include <linux/uaccess.h>    // comm func between userspace and kernel space

#include "virtual_driver.h"
#include "kdb_log.h"
#include "vird_func.h"


/*****************************************************************************/
/** 
 * @brief Defines struct of a virtual device
 * 
 *****************************************************************************/
DriverInfo_t gDriverInfo;
static uint8_t gsOpenCnt = 0;

/*****************************************************************************/

static int virt_open(struct inode *inode, struct file  *file);
static int virt_release(struct inode *inode, struct file *file);
static ssize_t write_callback(struct file *apFile, const uint8_t *apcData,
          size_t aSize, loff_t *apOff);
static struct file_operations fops = {
  .owner    = THIS_MODULE,
  .write    = write_callback,
  .open     = virt_open,
  .release  = virt_release,
};

uint32_t vir_drv_init(DriverInfo_t *apDriverInfo)
{
  uint16_t *lpBuffer = NULL;
  /* allocate memory for device */
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

static int virt_open(struct inode *inode, struct file *file)
{
  gsOpenCnt++;
  KDB_LOG_NOTE1("Virtual device open successfully."\);
  return 0;
}

static int virt_release(struct inode *inode, struct file *file)
{
  gsOpenCnt--;
  KDB_LOG_NOTE1("Virtual device close successfully.");
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
  // gDriverInfo.mDevNum =MKDEV(235, 0);
  // ret = register_chrdev_region(gDriverInfo.mDevNum, 1, "virtual_char_device");
  ret = alloc_chrdev_region(&gDriverInfo.mDevNum, 0, 1, "virtual_char_device");
  if (ret < 0)
  {
    KDB_LOG_NOTE1("Failed to register device number.");
    goto failed_register_devnum;
  }

  /* Create device file */
  gDriverInfo.mpDevClass = class_create(THIS_MODULE, "virtul_device_class");
  if(gDriverInfo.mpDevClass == NULL)
  {
    KDB_LOG_ERR1("Failed to create a device class.");
    goto failed_create_class;
  }
  gDriverInfo.mpDev = device_create(gDriverInfo.mpDevClass, 
        NULL, gDriverInfo.mDevNum, NULL, "virtual_device");
  if(gDriverInfo.mpDev == NULL)
  {
    KDB_LOG_ERR1("Failed to create a device.");
    goto failed_create_device;
  }

  /* Init device hardware */
  ret = vir_drv_init(&gDriverInfo);
  if(ret != 0)
  {
    KDB_LOG_ERR1("Failed to initialize a virtual device.");
    goto failed_init_hw;
  }

  /* Register entry points to kernel */
  gDriverInfo.mpDrvCdev = cdev_alloc();
  if(gDriverInfo.mpDrvCdev == NULL)
  {
    KDB_LOG_ERR1("Failed to allocate cdev structure.");
    goto failed_allocate_cdev;
  }
  cdev_init(gDriverInfo.mpDrvCdev, &fops);
  ret = cdev_add(gDriverInfo.mpDrvCdev, gDriverInfo.mDevNum, 1);
  if(ret < 0)
  {
    KDB_LOG_ERR1("Failed to add a char device to the system.");
    goto failed_allocate_cdev;
  }

  KDB_LOG_NOTE1("Initialize virtual driver successfully.");

  return 0;

failed_allocate_cdev:
  cdev_del(gDriverInfo.mpDrvCdev);
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
  /* release entry points */
  cdev_del(gDriverInfo.mpDrvCdev);
  /* free memory of hardware */
  vir_drv_exit(&gDriverInfo);
  /* delete device file */
  device_destroy(gDriverInfo.mpDevClass, gDriverInfo.mDevNum);
  class_destroy(gDriverInfo.mpDevClass);
  /* unregister device number */
  unregister_chrdev_region(gDriverInfo.mDevNum, 1);

  KDB_LOG_NOTE1("Exit virtual driver successfully.");

}

module_init(virtual_driver_init);
module_exit(virtual_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("vinhnt2410@gmail.com");
MODULE_VERSION("1.0");
