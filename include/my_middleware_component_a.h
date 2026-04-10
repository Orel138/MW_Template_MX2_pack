/**
  ******************************************************************************
  * @file    my_middleware_component_a.h
  * @brief   Public API for My Middleware Component A
  *
  * Component A is a normal OpenCMSIS-Pack component. It is always required by
  * the CubeMX2 configuration component in this template, so it demonstrates how
  * a generated configuration can pull an additional library component into the
  * final project.
  ******************************************************************************
  */

#ifndef MY_MIDDLEWARE_COMPONENT_A_H
#define MY_MIDDLEWARE_COMPONENT_A_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t MyMW_ComponentA_GetVersion(void);
uint32_t MyMW_ComponentA_Accumulate(const uint8_t *pData, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* MY_MIDDLEWARE_COMPONENT_A_H */
