/**
  ******************************************************************************
  * @file    my_middleware_component_a.c
  * @brief   My Middleware Component A implementation
  ******************************************************************************
  */

#include "my_middleware_component_a.h"

uint32_t MyMW_ComponentA_GetVersion(void)
{
  return 0x00010000U;
}

uint32_t MyMW_ComponentA_Accumulate(const uint8_t *pData, uint32_t size)
{
  uint32_t sum = 0U;

  if (pData == 0)
  {
    return 0U;
  }

  for (uint32_t index = 0U; index < size; index++)
  {
    sum += pData[index];
  }

  return sum;
}
