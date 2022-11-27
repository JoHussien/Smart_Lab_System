/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include<stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
 char read_char();
 void LCD();
 int strcmparr( volatile char arr1[],char arr2[],int size);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void LCD(){
	//delay
	HAL_Delay(20);
	//Set Function
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);//data 0 
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET); //data 3
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);//data 4
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET); //data 7
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);  //RS
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET); //RW
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); //E
	
	
	HAL_Delay(20);
	// Display control
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);//data 0 
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET); //data 3
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);//data 4
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET); //data 7
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);  //RS
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET); //RW
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); //E
	
	HAL_Delay(20);
	
	//Clear
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);//data 0 
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET); //data 3
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);//data 4
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET); //data 7
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);  //RS
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET); //RW
	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); //E
	HAL_Delay(20);
	
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); //E
	
	//display
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);//data 0 
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET); //data 3
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);//data 4
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET); //data 7

		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);  //RS
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET); //RW
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);//data 0 
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET); //data 3
//	
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);//data 4
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET); //data 7

//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET); //RW
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);  //RS
	
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET); //E
	}
 char read_char(){
	 
	 
	 //____________________________Col1________________________________//
	 uint8_t a='_';
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){ //row1
		 a='1';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){
			a='4';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){
			a='7';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){//row4
			a='0';
			
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
	 }
			 //____________________________Col2________________________________//
	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){ //row1
		  a='2';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){
			a='5';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){
			a='8';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){//row4
			a='F';
			
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
		}
		
					 //____________________________Col3________________________________//
	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){ //row1
		  a='3';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){
			a='6';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){};
		//		HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){
			a='9';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){//row4
			a='E';
			
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
		}
			 //____________________________Col4________________________________//
	
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET); //col4
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){ //row1
		  a='A';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
		//		HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){
			a='B';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)){};
				//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){
			a='C';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)){//row4
			a='D';
			
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5));
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
		}
return a;
 
 }
 int strcmparr( volatile char arr1[],char arr2[],int size){
	for(int i=0;i<size;i++){
		if (arr1[i]!=arr2[i]) 
					return 0;
		}
return 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	char a='_';
	char pass[4]="1234";
	char empty[4]={'_','_','_','_'};
	char user_pass[4]={'_','_','_','_'};
	char Succ[24]="Password is Correct\r\n";
	char Failed[24]="Password is Wrong\r\n";
	int counter=0;
	int buzzer_counter=0;
	uint8_t str[16];
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);
  while (1)
  {
		a=read_char();
	
		if(counter<4 && a!='_'){
		user_pass[counter]=a;
		counter++;
		sprintf((char*)str, "%c,%c,%c,%c\r\r\r\n", user_pass[0],user_pass[1],user_pass[2],user_pass[3]);	// this should be LCD
		HAL_UART_Transmit(&huart2, (uint8_t*)&str, sizeof(str), 100);
		}else if(counter==4){
			if(strcmparr(user_pass,pass,4)==1)
				{
					HAL_UART_Transmit(&huart2, (uint8_t*)&Succ, sizeof(Succ), 100);// this should be LCD
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET); 
					HAL_Delay(3000);
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);
					//relay enable
				}
			else 
				{
					buzzer_counter++;
					HAL_UART_Transmit(&huart2, (uint8_t*)&Failed, sizeof(Failed), 100);// this should be LCD
					if (buzzer_counter==3){
						//buzzer_enable
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET); 
						HAL_Delay(3000);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET); 
						buzzer_counter=0;
					}
					
				}
			
			counter=0;
			memcpy(user_pass, empty, sizeof (empty));
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA3 PA4
                           PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
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
