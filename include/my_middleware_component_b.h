/**
  ******************************************************************************
  * @file    my_middleware_component_b.h
  * @brief   Public API for My Middleware Component B
  *
  * Component B is optional. The generated GPDSC requires this component only
  * when the CubeMX2 configuration enables it.
  ******************************************************************************
  */

#ifndef MY_MIDDLEWARE_COMPONENT_B_H
#define MY_MIDDLEWARE_COMPONENT_B_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void MyMW_ComponentB_XorTransform(uint8_t *pData, uint32_t size, uint8_t key);

#ifdef __cplusplus
}
#endif

#endif /* MY_MIDDLEWARE_COMPONENT_B_H */
