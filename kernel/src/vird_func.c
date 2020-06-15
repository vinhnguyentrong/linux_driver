/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief virtual driver functions
 * @name vird_func.c
 * 
 * 
 * 
 *****************************************************************************/
#include "virtual_driver.h"
#include "vird_func.h"
#include "kdb_log.h"

uint32_t VIR_HW_Read(DriverInfo_t *apDriverInfo, uint32_t aStartReg, 
  uint32_t aLen, uint8_t *apKernelBuff)
{
  VIR_DRV_RESULT lRet = VIR_DRV_SUCCESS;
  if(apKernelBuff == NULL)
  {
    KDB_LOG_ERR1("Kernel buffer is NULL.\n");
    lRet VIR_DRV_FAILURE;
  }
  else
  {
    if(aStartReg > NUM_DATA_REGS)
    {
      KDB_LOG_ERR1("Wrong access to device memory.\n");
      lRet VIR_DRV_FAILURE;
    }
    else
    {
      if(apDriverInfo->mpRegs->mCTRL_RW.B.mCTRL_READ == ENABLE)
      {
        KDB_LOG_NOTE1("READ from hardware.\n");
        memcpy(apKernelBuff,(uint8_t*)(apDriverInfo->mpRegs->mDATA + aStartReg),
                 aLen);
      }
      else
      {
        KDB_LOG_ERR1("Cannot read from device memory.\n");
      }
      
    }
    
  }
  return lRet
}

uint32_t VIR_HW_Write(DriverInfo_t* apDriverInfo, uint32_t aStartReg,
  uint32_t aLen, uint8_t *apKernelBuff)
{
  VIR_DRV_RESULT lRet = VIR_DRV_SUCCESS;
  if(apKernelBuff == NULL)
  {
    KDB_LOG_ERR1("Data no exits.\n");
    lRet = VIR_DRV_FAILURE;
  }
  else
  {
    if(aStartReg > NUM_DATA_REGS)
    {
      KDB_LOG_ERR1("Data is to big.\n");
      lRet = VIR_DRV_FAILURE;
    }
    else
    {
      if(apDriverInfo->mpRegs->mCTRL_RW.B.mCTRL_WRITE == ENABLE)
      {
        KDB_LOG_NOTE1("Write to hardware.\n");
        memcpy((uint8_t*)(apDriverInfo->mpRegs->mDATA + aStartReg),
                apKernelBuff, aLen);
      }
      else
      {
        KDB_LOG_ERR1("Cannot write to device memory.\n");
        return VIR_DRV_FAILURE;
      }
    }
  }
  return lRet;
}