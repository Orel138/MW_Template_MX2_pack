/**
  ******************************************************************************
  * @file    my_middleware_component_b.c
  * @brief   My Middleware Component B implementation
  ******************************************************************************
  */

#include "my_middleware_component_b.h"

void MyMW_ComponentB_XorTransform(uint8_t *pData, uint32_t size, uint8_t key)
{
  if (pData == 0)
  {
    return;
  }

  for (uint32_t index = 0U; index < size; index++)
  {
    pData[index] ^= key;
  }
}
