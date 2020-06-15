/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief virtual device driver
 * @name virtual_device.h
 * 
 * 
 *
 *****************************************************************************/

#ifndef VIRTUAL_DRIVER_H
#define VIRTUAL_DRIVER_H

#include <linux/types.h>

typedef volatile uint8_t vuint8_t;
typedef volatile uint16_t vuint16_t;
typedef volatile uint32_t vuint32_t;

#define NUM_DATA_REGS   256 // Number of data registers
#define STAS_READ_ACCESS_BIT        (1 << 0)
#define STAS_WRITE_ACCESS_BIT       (1 << 2)
#define STAS_DATA_REGS_OVERFLOW_BIT (1 << 2)
#define READY         1
#define NOT_READY     0
#define OVERFLOW      1
#define NOT_OVERFLOW  0
#define CTRL_READ_DATA_BIT    (1 << 0)
#define CTRL_WRITE_DATA_BIT   (1 << 1)

#define ENABLE  1
#define DISALBE 0
 
/*****************************************************************************/
/**
 * @brief Discribe the status registers
 * @details init value: 0x0000
 *    - Increase 1 each read from data registers
 * 
 *****************************************************************************/
typedef union
{
  vuint16_t R;
  struct {
    vuint16_t mREAD_H_CNT : 8;
    vuint16_t mREAD_L_CNT : 8;
  } B;
} READ_CNT_REG_t;

typedef union
{
  vuint16_t R;
  struct {
    vuint16_t mWRITE_H_CNT : 8;
    vuint16_t mWRITE_L_CNT : 8;
  } B;
} WRITE_CNT_REG_t;

typedef struct DATA_REG
{
  vuint8_t mDATA[NUM_DATA_REGS];
} DATA_REG_t;

typedef union
{
  vuint8_t R;
  struct {
    vuint8_t mSTATUS_READ : 1;
    vuint8_t mSTATUS_WRITE : 1;
    vuint8_t mREVERSE : 1;
  } B;
} STS_REG_t;

/*****************************************************************************/
/**
 * @brief Discribe the control registers
 * @details Control read/write data from data registers 
 *  - Init value: 0x03
 *  - bit 0:
 *      0: Disable read from data registers
 *      1: Enable read from data registers
 *  - bit 1:
 *      0: Disable write to data registers
 *      1: Enable write to data registers
 *  - bit 2-7:
 *      reverse
 *****************************************************************************/
typedef union
{
  vuint8_t R;
  struct {
    vuint8_t mCTRL_READ : 1;
    vuint8_t mCTRL_WRITE : 1;
    vuint8_t mREVERSE : 6;
  } B;
} CTRL_REG_t;

/*****************************************************************************/
/**
 * @brief Discribe the registers of device
 * @details the struct of device registers 
 * 
 *****************************************************************************/
typedef struct DEVICE_REGS
{
  DATA_REG_t            mDATA;         // 0x0000 + BASE
  CTRL_REG_t            mCTRL_RW;      // 0x0100 - Control register
  uint8_t               mREVERSE1;     // 0x0101 - reverse
  STS_REG_t             mSTS_RW;       // 0x0102 - Status read/write register
  uint8_t               mREVERSE2;     // 0x0103 - reverse
  READ_CNT_REG_t        mREAD_CNT;     // 0x0102 - read counter register
  WRITE_CNT_REG_t       mWRITE_CNT;    // 0x0104 - write counter register
} DEVICE_REGS_t;

typedef struct 
{
  dev_t mDevNum;      // device number
  struct class *mpDevClass;
  struct device *mpDev;
  struct cdev   *mpDrvCdev;
  DEVICE_REGS_t *mpRegs;
  
} DriverInfo_t;

typedef enum
{
  VIR_DRV_SUCCESS = 0,
  VIR_DRV_FAILURE = 1,
  VIR_DRV_SIZE = 0x7fffffffUL,
}VIR_DRV_RESULT;

#endif /* VIRTUAL_DRIVER_H */