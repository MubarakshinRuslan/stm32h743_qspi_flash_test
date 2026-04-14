/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */
#define WRITE_ENABLE_CMD   0x06U
#define READ_STATUS_REG1_CMD   0x05U
#define READ_STATUS_REG2_CMD   0x35U
#define READ_STATUS_REG3_CMD   0x15U
#define WRITE_STATUS_REG2_CMD 	0x31U
#define QSPI_TIMEOUT_DEFAULT_VALUE 1000U
#define QUAD_OUT_FAST_READ_CMD       0x6BU
#define DUMMY_CLOCK_CYCLES_READ_QUAD 8U
#define QUAD_IN_FAST_PROG_CMD 0x32U
#define MEMORY_FLASH_SIZE		0x1000000U
#define MEMORY_PAGE_SIZE 		256U
#define SECTOR_ERASE_CMD        0x20U
#define CHIP_ERASE_CMD          0xC7U
#define MEMORY_SECTOR_SIZE      0x1000U   /* 4KB */
#define QUADSPI_MAX_ERASE_TIMEOUT 300000U

uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_ReadMemory(uint8_t *buffer, uint32_t address, uint32_t size);
uint8_t CSP_QSPI_WriteMemory(uint8_t *buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress, uint32_t EraseEndAddress);
uint8_t CSP_QSPI_Erase_Chip(void);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

