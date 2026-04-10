/**
  ******************************************************************************
  * @file    my_middleware.h
  * @brief   My Middleware public API
  *
 * This header exposes the types, macros, and function prototypes for
 * My Middleware Core. Application code should include only this file for the
 * core service. Optional pack components are exposed through
 * my_middleware_component_a.h and my_middleware_component_b.h.
  *
  * The buffer size used at run-time is provided by the generated file
  * "my_middleware_config.h", which is produced by the STM32CubeMX2
  * code generator.  Include that header before calling any API function.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef MY_MIDDLEWARE_H
#define MY_MIDDLEWARE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>

/* Include the CubeMX2-generated configuration file.
 * MY_MIDDLEWARE_BUFFER_SIZE is defined there. */
#include "my_middleware_config.h"

/* Exported types ----------------------------------------------------------- */

/** Return status codes */
typedef enum
{
  MY_MW_OK    = 0, /**< Operation completed successfully */
  MY_MW_ERROR = 1, /**< Generic error */
  MY_MW_BUSY  = 2  /**< Resource is busy */
} MyMW_StatusTypeDef;

/** Middleware handle — opaque to the application */
typedef struct
{
  uint8_t  buffer[MY_MIDDLEWARE_BUFFER_SIZE]; /**< Internal working buffer */
  uint32_t head;                              /**< Write index */
  uint32_t tail;                              /**< Read index */
  uint32_t count;                             /**< Number of bytes stored */
} MyMW_HandleTypeDef;

/* Exported constants ------------------------------------------------------- */
#define MY_MW_COMPONENT_A_NAME  "Component A"
#define MY_MW_COMPONENT_B_NAME  "Component B"

/* Exported macros ---------------------------------------------------------- */
/* (none) */

/* Exported function prototypes --------------------------------------------- */

/**
 * @brief  Initialize the middleware handle.
 * @param  hmw  Pointer to the handle to initialize.
 * @retval MY_MW_OK on success, MY_MW_ERROR if hmw is NULL.
 */
MyMW_StatusTypeDef MyMW_Init(MyMW_HandleTypeDef *hmw);

/**
 * @brief  Write data into the middleware buffer.
 * @param  hmw   Pointer to the initialized handle.
 * @param  pData Pointer to source data.
 * @param  size  Number of bytes to write.
 * @retval MY_MW_OK on success, MY_MW_ERROR if arguments are invalid,
 *         MY_MW_BUSY if the buffer does not have enough free space.
 */
MyMW_StatusTypeDef MyMW_Write(MyMW_HandleTypeDef *hmw,
                               const uint8_t *pData,
                               uint32_t       size);

/**
 * @brief  Read data from the middleware buffer.
 * @param  hmw   Pointer to the initialized handle.
 * @param  pData Pointer to destination buffer.
 * @param  size  Number of bytes to read.
 * @retval MY_MW_OK on success, MY_MW_ERROR if arguments are invalid,
 *         MY_MW_BUSY if fewer bytes are available than requested.
 */
MyMW_StatusTypeDef MyMW_Read(MyMW_HandleTypeDef *hmw,
                              uint8_t            *pData,
                              uint32_t            size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MY_MIDDLEWARE_H */
