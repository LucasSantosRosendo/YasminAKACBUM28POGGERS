/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7735\st7735.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define QUADRADO_0 matriz[1][1]
#define QUADRADO_1 matriz[1][2]
#define QUADRADO_2 matriz[1][3]
#define QUADRADO_3 matriz[2][1]
#define QUADRADO_4 matriz[2][2]
#define QUADRADO_5 matriz[2][3]
#define QUADRADO_6 matriz[3][1]
#define QUADRADO_7 matriz[3][2]
#define QUADRADO_8 matriz[3][3]
#define LIGA_LED1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,1)
#define LIGA_LED2 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,1)
#define LIGA_LED3 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1)
#define LIGA_LED4 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1)
#define DESLIGA_LED1 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,0)
#define DESLIGA_LED2 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,0)
#define DESLIGA_LED3 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,0)
#define DESLIGA_LED4 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0)
#define BOTAO_ESQUERDO HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)
#define BOTAO_SELECT HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)
#define BOTAO_DIREITO HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)
#define BOTAO_SELECT2 HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12)
#define CASA0 50,5
#define CASA_0_VAZIA ST7735_WriteString(CASA0," ", Font_11x18, WHITE, BLACK)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void tabela (int XIX,int BOLINHA){
if(XIX == 0){
	ST7735_WriteString(10,30,"0", Font_7x10, WHITE, BLACK);
}
else if(XIX == 1){
	ST7735_WriteString(10,30,"1", Font_7x10, WHITE, BLACK);
}
else if(XIX == 2){
	ST7735_WriteString(10,30,"2", Font_7x10, WHITE, BLACK);
}
if(BOLINHA == 0){
    ST7735_WriteString(10,65,"0", Font_7x10, WHITE, BLACK);
}
else if(BOLINHA == 1){
    ST7735_WriteString(10,65,"1", Font_7x10, WHITE, BLACK);
}
else if(BOLINHA == 2){
	ST7735_WriteString(10,65,"2", Font_7x10, WHITE, BLACK);
}
return 0;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int matriz [3][3], XIX = 0, BOLINHA = 0, opcao = 0, cont = 0;;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

      //zerando o placar
      XIX = 0, BOLINHA = 0;

      ST7735_FillScreen(BLACK);
              ST7735_Test();
              tabela(XIX, BOLINHA);

      //INICIO JOGO (sendo uma melhor de 3)
      while (BOLINHA != 2 || XIX != 2){

        //LIMPANDO O JOGO/ ZERANDO A TABELA

    	  QUADRADO_0 =0, QUADRADO_1 = 0,  QUADRADO_2 = 0, QUADRADO_3 = 0, QUADRADO_4 = 0, QUADRADO_5 = 0, QUADRADO_6 = 0, QUADRADO_7  = 0, QUADRADO_8 = 0;

    	  while (true){

          //jogada XIX
        while (cont == 0){

        	if (BOTAO_ESQUERDO == 0){
        	opcao --;
        	DESLIGA_LED1;
        	}
        	if (BOTAO_DIREITO == 0){
        	opcao ++;
        	DESLIGA_LED2;
        	}
        	if (opcao < 0){
        	opcao = 8;
        	}
        	if (opcao > 8){
        	opcao = 0;
        	}

        	 if (QUADRADO_0 == 1){
        	       	ST7735_WriteString(CASA0,"x", Font_11x18, WHITE, BLACK);
        	       	opcao ++;
        	         }
        	        else if (QUADRADO_0 == 2){
        	        ST7735_WriteString(CASA0,"o", Font_11x18, WHITE, BLACK);
        	        opcao ++;
        	        }
        	        else if(BOTAO_SELECT == 1 &&  opcao == 0){
        	        ST7735_WriteString(CASA0,"x", Font_11x18, RED, BLACK);
        	        }
        	        else if (BOTAO_SELECT == 0 && opcao == 0){
        	          ST7735_WriteString(CASA0,"x", Font_11x18, WHITE, BLACK);
        	          HAL_Delay(1000);
        	        cont ++;
        	        QUADRADO_0 = 1;
        	        opcao = 0;
        	        }
        	        else if ((QUADRADO_0 != 1)&&(QUADRADO_0 != 2)&&(opcao != 0)){
        	        	ST7735_WriteString(CASA0," ", Font_11x18, WHITE, BLACK);
        	        }


        	if (QUADRADO_3 == 1){
        	       	ST7735_WriteString(50,32,"x", Font_11x18, WHITE, BLACK);
        	       	opcao ++;
        	         }
        	        else if (QUADRADO_3 == 2){
        	        ST7735_WriteString(50,32,"o", Font_11x18, WHITE, BLACK);
        	        opcao ++;
        	        }
        	        else if(BOTAO_SELECT == 1 &&  opcao == 3){
        	        ST7735_WriteString(50,32,"x", Font_11x18, RED, BLACK);
        	        }
        	        else if (BOTAO_SELECT == 0 && opcao == 3){
        	          ST7735_WriteString(50,32,"x", Font_11x18, WHITE, BLACK);
        	          HAL_Delay(1000);
        	        cont ++;
        	        QUADRADO_3 = 1;
        	        opcao = 0;
        	        }




        	if (QUADRADO_4 == 1){
        	        	       	ST7735_WriteString(95,32,"x", Font_11x18, WHITE, BLACK);
        	        	       	opcao ++;
        	        	         }
        	        	        else if (QUADRADO_4 == 2){
        	        	        ST7735_WriteString(95,32,"o", Font_11x18, WHITE, BLACK);
        	        	        opcao ++;
        	        	        }
        	        	        else if(BOTAO_SELECT == 1 &&  opcao == 4){
        	        	        ST7735_WriteString(95,32,"x", Font_11x18, RED, BLACK);
        	        	        }
        	        	        else if (BOTAO_SELECT == 0 && opcao == 4){
        	        	          ST7735_WriteString(95,32,"x", Font_11x18, WHITE, BLACK);
        	        	          HAL_Delay(1000);
        	        	        cont ++;
        	        	        QUADRADO_4 = 1;
        	        	        opcao = 0;
        	        	        }



        	if (QUADRADO_5 == 1){
        	        	       	ST7735_WriteString(140,32,"x", Font_11x18, WHITE, BLACK);
        	        	       	opcao ++;
        	        	         }
        	        	        else if (QUADRADO_5 == 2){
        	        	        ST7735_WriteString(140,32,"o", Font_11x18, WHITE, BLACK);
        	        	        opcao ++;
        	        	        }
        	        	        else if(BOTAO_SELECT == 1 &&  opcao == 5){
        	        	        ST7735_WriteString(140,32,"x", Font_11x18, RED, BLACK);
        	        	        }
        	        	        else if (BOTAO_SELECT == 0 && opcao == 5){
        	        	          ST7735_WriteString(140,32,"x", Font_11x18, WHITE, BLACK);
        	        	          HAL_Delay(1000);
        	        	        cont ++;
        	        	        QUADRADO_5 = 1;
        	        	        opcao = 0;
        	        	        }



        	if (QUADRADO_6 == 1){
        	        	       	ST7735_WriteString(50,60,"x", Font_11x18, WHITE, BLACK);
        	        	       	opcao ++;
        	        	         }
        	        	        else if (QUADRADO_6 == 2){
        	        	        ST7735_WriteString(50,60,"o", Font_11x18, WHITE, BLACK);
        	        	        opcao ++;
        	        	        }
        	        	        else if(BOTAO_SELECT == 1 &&  opcao == 6){
        	        	        ST7735_WriteString(50,60,"x", Font_11x18, RED, BLACK);
        	        	        }
        	        	        else if (BOTAO_SELECT == 0 && opcao == 6){
        	        	          ST7735_WriteString(50,60,"x", Font_11x18, WHITE, BLACK);
        	        	          HAL_Delay(1000);
        	        	        cont ++;
        	        	        QUADRADO_6 = 1;
        	        	        opcao = 0;
        	        	        }


        	if (QUADRADO_7 == 1){
        	        	       	ST7735_WriteString(95,60,"x", Font_11x18, WHITE, BLACK);
        	        	       	opcao ++;
        	        	         }
        	        	        else if (QUADRADO_7 == 2){
        	        	        ST7735_WriteString(95,60,"o", Font_11x18, WHITE, BLACK);
        	        	        opcao ++;
        	        	        }
        	        	        else if(BOTAO_SELECT == 1 &&  opcao == 7){
        	        	        ST7735_WriteString(95,60,"x", Font_11x18, RED, BLACK);
        	        	        }
        	        	        else if (BOTAO_SELECT == 0 && opcao == 7){
        	        	          ST7735_WriteString(95,60,"x", Font_11x18, WHITE, BLACK);
        	        	          HAL_Delay(1000);
        	        	        cont ++;
        	        	        QUADRADO_7 = 1;
        	        	        opcao = 0;
        	        	        }


        	if (QUADRADO_8 == 1){
        	        	       	ST7735_WriteString(140,60,"x", Font_11x18, WHITE, BLACK);
        	        	       	opcao ++;
        	        	         }
        	        	        else if (QUADRADO_8 == 2){
        	        	        ST7735_WriteString(140,60,"o", Font_11x18, WHITE, BLACK);
        	        	        opcao ++;
        	        	        }
        	        	        else if(BOTAO_SELECT == 1 &&  opcao == 8){
        	        	        ST7735_WriteString(140,60,"x", Font_11x18, RED, BLACK);
        	        	        }
        	        	        else if (BOTAO_SELECT == 0 && opcao == 8){
        	        	          ST7735_WriteString(140,60,"x", Font_11x18, WHITE, BLACK);
        	        	          HAL_Delay(1000);
        	        	        cont ++;
        	        	        QUADRADO_8 = 1;
        	        	        opcao = 0;
        	        	        }

        if (QUADRADO_1 == 1){
        ST7735_WriteString(95,5,"x", Font_11x18, WHITE, BLACK);
        opcao ++;
        }
        else if (QUADRADO_1 == 2){
        ST7735_WriteString(95,5,"o", Font_11x18, WHITE, BLACK);
        opcao ++;
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 1){
        ST7735_WriteString(95,5,"x", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 1){
        ST7735_WriteString(95,5,"x", Font_11x18, WHITE, BLACK);
         HAL_Delay(1000);
         cont ++;
         QUADRADO_1 = 1;
         opcao = 0;
         }




        if (QUADRADO_2 == 1){
        ST7735_WriteString(135,5,"x", Font_11x18, WHITE, BLACK);
        opcao ++;
        }
        else if (QUADRADO_2 == 2){
        ST7735_WriteString(135,5,"o", Font_11x18, WHITE, BLACK);
        opcao ++;
        }
        else if(BOTAO_SELECT == 1 &&  opcao == 2){
        ST7735_WriteString(135,5,"x", Font_11x18, RED, BLACK);
        }
        else if (BOTAO_SELECT == 0 && opcao == 2){
        ST7735_WriteString(135,5,"x", Font_11x18, WHITE, BLACK);
        HAL_Delay(1000);
        cont ++;
        QUADRADO_2 = 1;
        opcao = 0;
        }



        if((QUADRADO_0 == 1 && QUADRADO_1 == 1 && QUADRADO_2 == 1)||(QUADRADO_3 == 1 && QUADRADO_4 == 1 && QUADRADO_5 == 1)||(QUADRADO_6 == 1 && QUADRADO_7 == 1 && QUADRADO_8 == 1)){
        	XIX++;
        	false;
        }
        else if((QUADRADO_0 == 1 && QUADRADO_5 == 1 && QUADRADO_8 == 1) || (QUADRADO_2 == 1 && QUADRADO_4 == 1 && QUADRADO_6 == 1)){
         XIX++;
         false;
                }



        }
        //jogada bolinha
        while (cont == 1){

cont --;

        }
     }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_1LINE;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
