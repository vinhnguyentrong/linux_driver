/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief virtual driver functions header
 * @name vird_func.h
 * 
 * 
 * 
 *****************************************************************************/

#ifndef VIRD_FUNC_H
#define VIRD_FUNC_H

#include "virtual_driver.h"

uint32_t VIR_HW_Read(DriverInfo_t *apDriverInfo, uint32_t aStartReg,
        uint32_t aNumBytes, uint8_t* apKernelBuff);

uint32_t VIR_HW_Write(DriverInfo_t *apDriverInfo, uint32_t aStartReg,
        uint32_t aNumBytes, uint8_t* apKernelBuff);

#endif /* VIRD_FUNC_H */