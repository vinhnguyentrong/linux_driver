/*****************************************************************************/
/** Copyright-2020
 * 
 * @brief communicate between userspace and kernel space
 * @name virt_comm.h
 * 
 * 
 * 
 *****************************************************************************/
#include <linux/types.h>

typedef enum COMM_ID
{
  CMD_READ    = 0,
  CMD_WRITE   = 1,
  CMD_SIZE    = 0x7fffffffUL,
} CommId_t;

typedef struct COMM_ARG
{
  void *mpData;
  uint32_t mSize;
} CommArg_t;

typedef struct COMM_DISPATCHER
{
  CommId_t    mCommID;
  CommArg_t   mArgs2Kernel;
  uint32_t    mArg2KernelSize;
  CommArg_t   mArgs2User;
  uint32_t    mArgs2UserSize;
} CommDispatcher_t;

