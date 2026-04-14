/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
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
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */
static uint32_t QSPI_ReadJedecID(void);
static uint8_t QSPI_WaitBusy(uint32_t Timeout);
static uint8_t QSPI_ResetChip(void);
static uint8_t QSPI_WriteEnable(void);
static uint8_t QSPI_ReadStatusReg1(uint8_t *value);
static uint8_t QSPI_ReadStatusReg2(uint8_t *value);
static uint8_t QSPI_ReadStatusReg3(uint8_t *value);
static uint8_t QSPI_AutoPollingMemReady(uint32_t Timeout);
static uint8_t QSPI_WriteStatusReg2(uint8_t value);
static uint8_t QSPI_EnableQuadMode(void);
/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 32;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 23;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_2_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.PLL2.PLL2M = 5;
    PeriphClkInitStruct.PLL2.PLL2N = 80;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 8;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    PB6     ------> QUADSPI_BK1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PB2     ------> QUADSPI_CLK
    PB6     ------> QUADSPI_BK1_NCS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint8_t CSP_QUADSPI_Init(void)
{
	  HAL_QSPI_Abort(&hqspi);
	  uint8_t status = QSPI_ResetChip();
	  HAL_Delay(100);
	  uint32_t jedec_id = QSPI_ReadJedecID();

	  if (!((jedec_id == 0xef4018) || (jedec_id == 0xef7018)))
	  {
		  return HAL_ERROR;
	  }

	  if (QSPI_EnableQuadMode() != HAL_OK)
	  {
	      return HAL_ERROR;
	  }

	  return HAL_OK;
}



static uint32_t QSPI_ReadJedecID(void)
{
	QSPI_CommandTypeDef sCommand = {0};
	uint8_t id[3] = {0};

	HAL_QSPI_Abort(&hqspi);

	sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction       = 0x9F; /* JEDEC ID */
	sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
	sCommand.Address 		   = 0U;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode          = QSPI_DATA_1_LINE;
	sCommand.NbData            = 3U;
	sCommand.DummyCycles       = 0U;
	sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	HAL_StatusTypeDef status;
	status = HAL_QSPI_Command(&hqspi, &sCommand, 1000);
	if (status != HAL_OK)
	{
		return 0;
	}

	status = HAL_QSPI_Receive(&hqspi, id, 1000);
	if (status != HAL_OK)
	{
		return 0;
	}

	return ((uint32_t)id[0] << 16) |
	           ((uint32_t)id[1] << 8)  |
	           ((uint32_t)id[2]);
}


static uint8_t QSPI_ResetChip(void)
{
    QSPI_CommandTypeDef sCommand = {0};

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode = QSPI_ADDRESS_NONE;
    sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode = QSPI_DATA_NONE;
    sCommand.NbData = 0U;
    sCommand.DummyCycles = 0U;
    sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.Instruction = 0x66; // Reset Enable
    if (HAL_QSPI_Command(&hqspi, &sCommand, 1000) != HAL_OK)
    {
    	return HAL_ERROR;
    }

    sCommand.Instruction = 0x99; // Reset
    if (HAL_QSPI_Command(&hqspi, &sCommand, 1000) != HAL_OK)
    {
    	return HAL_ERROR;
    }

    HAL_Delay(1);

    return HAL_OK;
}

static uint8_t QSPI_WriteEnable(void)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_AutoPollingTypeDef sConfig = {0};

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Send Write Enable command (0x06) */
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = WRITE_ENABLE_CMD;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Wait until WEL bit is set (SR1 bit1) */
    sCommand.Instruction = READ_STATUS_REG1_CMD;  /* 0x05 */
    sCommand.DataMode    = QSPI_DATA_1_LINE;
    sCommand.NbData      = 1U;

    sConfig.Match           = 0x02U;   /* WEL = 1 */
    sConfig.Mask            = 0x02U;
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1U;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_ReadStatusReg1(uint8_t *value)
{
    QSPI_CommandTypeDef sCommand = {0};

    if (value == NULL)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = READ_STATUS_REG1_CMD;   /* 0x05 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, value, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_ReadStatusReg2(uint8_t *value)
{
    QSPI_CommandTypeDef sCommand = {0};

    if (value == NULL)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = READ_STATUS_REG2_CMD;   /* 0x35 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, value, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_ReadStatusReg3(uint8_t *value)
{
    QSPI_CommandTypeDef sCommand = {0};

    if (value == NULL)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = READ_STATUS_REG3_CMD;   /* 0x15 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, value, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_AutoPollingMemReady(uint32_t Timeout)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_AutoPollingTypeDef sConfig = {0};

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    /* Read Status Register-1 (0x05) */
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = READ_STATUS_REG1_CMD; /* 0x05 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    /* Wait until BUSY = 0 */
    sConfig.Match           = 0x00U;
    sConfig.Mask            = 0x01U;  /* BUSY bit */
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1U;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, Timeout) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_WaitBusy(uint32_t Timeout)
{
    uint8_t sr1 = 0;
    uint32_t tickstart = HAL_GetTick();

    do
    {
        if (QSPI_ReadStatusReg1(&sr1) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if ((sr1 & 0x01U) == 0U)   /* BUSY = 0 */
        {
            return HAL_OK;
        }

    } while ((HAL_GetTick() - tickstart) < Timeout);

    return HAL_TIMEOUT;
}

static uint8_t QSPI_WriteStatusReg2(uint8_t value)
{
    QSPI_CommandTypeDef sCommand = {0};

    if (QSPI_WriteEnable() != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = WRITE_STATUS_REG2_CMD;   /* 0x31 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Transmit(&hqspi, &value, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (QSPI_AutoPollingMemReady(QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_EnableQuadMode(void)
{
    uint8_t sr2 = 0U;

    if (QSPI_ReadStatusReg2(&sr2) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if ((sr2 & 0x02U) == 0U)
    {
        sr2 |= 0x02U;

        if (QSPI_WriteStatusReg2(sr2) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (QSPI_ReadStatusReg2(&sr2) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if ((sr2 & 0x02U) == 0U)
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_ReadMemory(uint8_t *buffer, uint32_t address, uint32_t size)
{
    QSPI_CommandTypeDef sCommand = {0};

    if ((buffer == NULL) || (size == 0U))
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = QUAD_OUT_FAST_READ_CMD;   /* 0x6B */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = address;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.NbData            = size;
    sCommand.DummyCycles       = DUMMY_CLOCK_CYCLES_READ_QUAD; /* 8 */
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, buffer, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_WriteMemory(uint8_t *buffer, uint32_t address, uint32_t buffer_size)
{
    QSPI_CommandTypeDef sCommand = {0};
    uint32_t current_addr;
    uint32_t current_size;
    uint32_t end_addr;

    if ((buffer == NULL) || (buffer_size == 0U))
    {
        return HAL_ERROR;
    }

    current_addr = address;
    current_size = MEMORY_PAGE_SIZE - (address % MEMORY_PAGE_SIZE);
    if (current_size > buffer_size)
    {
        current_size = buffer_size;
    }

    end_addr = address + buffer_size;

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = QUAD_IN_FAST_PROG_CMD;   /* 0x32 */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_ONLY_FIRST_CMD;

    do
    {
        sCommand.Address = current_addr;
        sCommand.NbData  = current_size;

        if (QSPI_WriteEnable() != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Transmit(&hqspi, buffer, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (QSPI_WaitBusy(QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        current_addr += current_size;
        buffer       += current_size;

        if (current_addr >= end_addr)
        {
            break;
        }

        current_size = ((current_addr + MEMORY_PAGE_SIZE) > end_addr)
                     ? (end_addr - current_addr)
                     : MEMORY_PAGE_SIZE;

    } while (current_addr < end_addr);

    return HAL_OK;
}

uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress, uint32_t EraseEndAddress)
{
    QSPI_CommandTypeDef sCommand = {0};

    EraseStartAddress = EraseStartAddress - (EraseStartAddress % MEMORY_SECTOR_SIZE);

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = SECTOR_ERASE_CMD;      /* 0x20 */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.NbData            = 0U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    while (EraseStartAddress <= EraseEndAddress)
    {
        sCommand.Address = EraseStartAddress;

        if (QSPI_WriteEnable() != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (QSPI_WaitBusy(QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        EraseStartAddress += MEMORY_SECTOR_SIZE;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_Erase_Chip(void)
{
    QSPI_CommandTypeDef sCommand = {0};

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = CHIP_ERASE_CMD;        /* 0xC7 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.NbData            = 0U;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (QSPI_WriteEnable() != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Command(&hqspi, &sCommand, QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (QSPI_WaitBusy(QUADSPI_MAX_ERASE_TIMEOUT) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};

    if (HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = QUAD_OUT_FAST_READ_CMD;   /* 0x6B */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = 0U;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.NbData            = 0U;
    sCommand.DummyCycles       = DUMMY_CLOCK_CYCLES_READ_QUAD; /* 8 */
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    sMemMappedCfg.TimeOutPeriod     = 0U;

    if (HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}
/* USER CODE END 1 */
