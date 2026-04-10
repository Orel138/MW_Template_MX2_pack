/**
  ******************************************************************************
  * @file    my_middleware.c
  * @brief   My Middleware implementation
  *
  * This file contains the core logic of My Middleware.  It is compiled into
  * the application project when the user selects the "MyMiddleware::Core"
  * CMSIS component in their IDE or build system.
  *
  * The ring-buffer implementation below is intentionally simple so that the
  * template remains easy to understand and adapt.
  ******************************************************************************
  */

/* Includes ----------------------------------------------------------------- */
#include "my_middleware.h"

/* Private defines ---------------------------------------------------------- */
/* (none beyond those inherited from my_middleware_config.h via the header) */

/* Private types ------------------------------------------------------------ */
/* (none) */

/* Private variables -------------------------------------------------------- */
/* (none — state lives inside the caller-owned MyMW_HandleTypeDef) */

/* Private function prototypes ---------------------------------------------- */
static uint32_t MyMW_FreeSpace(const MyMW_HandleTypeDef *hmw);

/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Initialize the middleware handle.
 */
MyMW_StatusTypeDef MyMW_Init(MyMW_HandleTypeDef *hmw)
{
  if (hmw == NULL)
  {
    return MY_MW_ERROR;
  }

  hmw->head  = 0U;
  hmw->tail  = 0U;
  hmw->count = 0U;

  return MY_MW_OK;
}

/**
 * @brief  Write data into the ring buffer.
 */
MyMW_StatusTypeDef MyMW_Write(MyMW_HandleTypeDef *hmw,
                               const uint8_t      *pData,
                               uint32_t            size)
{
  if ((hmw == NULL) || (pData == NULL) || (size == 0U))
  {
    return MY_MW_ERROR;
  }

  if (MyMW_FreeSpace(hmw) < size)
  {
    return MY_MW_BUSY;
  }

  for (uint32_t i = 0U; i < size; i++)
  {
    hmw->buffer[hmw->head] = pData[i];
    hmw->head = (hmw->head + 1U) % MY_MIDDLEWARE_BUFFER_SIZE;
    hmw->count++;
  }

  return MY_MW_OK;
}

/**
 * @brief  Read data from the ring buffer.
 */
MyMW_StatusTypeDef MyMW_Read(MyMW_HandleTypeDef *hmw,
                              uint8_t            *pData,
                              uint32_t            size)
{
  if ((hmw == NULL) || (pData == NULL) || (size == 0U))
  {
    return MY_MW_ERROR;
  }

  if (hmw->count < size)
  {
    return MY_MW_BUSY;
  }

  for (uint32_t i = 0U; i < size; i++)
  {
    pData[i]   = hmw->buffer[hmw->tail];
    hmw->tail  = (hmw->tail + 1U) % MY_MIDDLEWARE_BUFFER_SIZE;
    hmw->count--;
  }

  return MY_MW_OK;
}

/* Private functions -------------------------------------------------------- */

/**
 * @brief  Return the number of free bytes in the ring buffer.
 */
static uint32_t MyMW_FreeSpace(const MyMW_HandleTypeDef *hmw)
{
  return MY_MIDDLEWARE_BUFFER_SIZE - hmw->count;
}
