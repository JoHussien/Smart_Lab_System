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
TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOA
#define RW_Pin GPIO_PIN_0
#define RW_GPIO_Port GPIOA
#define EN_Pin GPIO_PIN_3
#define EN_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define timer htim1
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern TIM_HandleTypeDef timer;
void delay (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&timer, 0);
	while (__HAL_TIM_GET_COUNTER(&timer) < us);
}


void send_to_lcd (char data, int rs)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, rs);  // rs = 1 for data, rs=0 for command

	/* write the data to the respective pin */
	HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, ((data>>3)&0x01));
	HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, ((data>>2)&0x01));
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, ((data>>1)&0x01));
	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, ((data>>0)&0x01));

	/* Toggle EN PIN to send the data
	 * if the HCLK > 100 MHz, use the  20 us delay
	 * if the LCD still doesn't work, increase the delay to 50, 80 or 100..
	 */
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	delay (20);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	delay (20);
}

void lcd_send_cmd (char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0f);
    send_to_lcd(datatosend,0);  // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0f);
	send_to_lcd(datatosend, 0);
}

void lcd_send_data (char data)
{
	char datatosend;

	/* send higher nibble */
	datatosend = ((data>>4)&0x0f);
	send_to_lcd(datatosend, 1);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data)&0x0f);
	send_to_lcd(datatosend, 1);
}

void lcd_clear (void)
{
	lcd_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_put_cur(int row, int col)
{
    switch (row)
    {
        case 0:
            col |= 0x80;
            break;
        case 1:
            col |= 0xC0;
            break;
    }

    lcd_send_cmd (col);
}


void lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0D); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

char read_char(){
	 
	 
	 //____________________________Col1________________________________//
	 uint8_t a='_';
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){ //row1
		 a='1';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){
			a='4';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
			a='7';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){//row4
			a='0';
			
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
	 }
			 //____________________________Col2________________________________//
	
	  a='_';
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){ //row1
		 a='2';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){
			a='5';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
			a='8';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){//row4
			a='F';
			
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
	 }
					 //____________________________Col3________________________________//
	
	  a='_';
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET); //col4
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){ //row1
		 a='3';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){
			a='6';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
			a='9';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){//row4
			a='E';
			
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
				 return a;
	 }
			 //____________________________Col4________________________________//
	
	  a='_';
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET); //col4
HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);//col1
	 

	 if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){ //row1
		 a='A';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
		 
	 }
	 
	  else if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){
			a='B';
		 while(!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)){};
			//HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){
			a='C';
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)){};
			//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
		 return a;
	 }
		
	  else if (!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){//row4
			a='D';
			
		 while(!HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)){};
		//	HAL_UART_Transmit(&huart2,&a,sizeof(a),100);
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
int search_pass(char arr1[],char*arr2,int size,int user_size ,int index){
	


			for(int i=0;i<size;i++){
				if (arr1[i]!=arr2[index*size+i]) 
							return 0;
			
			}
		
	
	return 1;
}
int search(char id[],char*arr2,int size,int user_size ,char pass[],char *passwords){
	

	for (int user=0;user<user_size;user++){
			for(int i=0;i<size;i++){
				if (id[i]!=arr2[user*size+i]) 
							break;
			else if(i==size-1 && id[i]==arr2[user*size+i]){
				if (search_pass(pass,passwords,4,4,user)==1)
					return 1;
			
			}}
		
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
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim1);
  lcd_init ();
  lcd_put_cur(0, 0);
	  lcd_clear();
	lcd_send_string("Userid");
	lcd_send_string("");
	lcd_put_cur(1, 0);

	char IDs[4][9]={"900184042","900183162","900183874","900180000"};
	char Passwords[4][4]={"1234","2000","3456","0000"};
	
	char a='_';
	

	char empty[9]="_________";
	char empty2[4]="____";
	
	char user_id[9]="_________";
	char user_pass[4]="____";
	
	char user_pass_appear[9]="____    ";
	char user_appear[9]="_________";
	
	char Succ[9]="Correct:o";
	char Failed[9]="Wrong!!!!";
	
	int counter=0,counter2=0;
	int buzzer_counter=0;
	uint8_t str[9];
		uint8_t str2[9];
	uint8_t send=' ';
	int passflag=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		a=read_char();
	
		if(counter<9 && a!='_'){
			user_id[counter]=a;
			user_appear[counter]=a;
			counter++;
			sprintf((char*)str, "%s", user_appear);
			
			lcd_put_cur(1, 0);
			lcd_send_string((char*)str);
			lcd_put_cur(1, counter);
		
		}else if(passflag==0 && counter==9){
		lcd_put_cur(0, 0);
						lcd_clear();
						lcd_send_string("Pass");
	
						sprintf((char*)str2, "%s", user_pass_appear);	// this should be LCD
						lcd_put_cur(1, 0);
						lcd_send_string((char*)str2);
						lcd_put_cur(1, 0);
						passflag=1;
		}else if(counter==9){
		
					if(counter2<4)
						{
	
	
						if ( a!='_')
							{
									user_pass[counter2]=a;
									user_pass_appear[counter2]='*';
									counter2++;
									sprintf((char*)str2, "%s", user_pass_appear);	// this should be LCD
									
									lcd_put_cur(1, 0);
									lcd_send_string((char*)str2);
									lcd_put_cur(1, counter2);
						
							}
						}
					else if(counter2==4  && search(user_id,(char*)IDs,9,4,user_pass,(char*)Passwords)==1){
						sprintf((char*)str, "%s", Succ);
						lcd_put_cur(1, 0);
						lcd_send_string((char*)str);
						//clearing
						memcpy(user_appear, empty, sizeof (empty));
						memcpy(user_pass_appear, empty2, sizeof (empty2));
						HAL_Delay(1000);
						
						lcd_put_cur(1, 0);
						sprintf((char*)str, "%s", user_appear);
						lcd_send_string((char*)str);
					
						//relay enable
						send='R';
						HAL_UART_Transmit(&huart2, &send, sizeof(send), 100);// this should be LCD
						send=' ';
						buzzer_counter=0;
						
						counter=0;
						counter2=0;
						passflag=0;
						lcd_put_cur(0, 0);
						lcd_clear();
						
					
					lcd_send_string("Userid");
					lcd_send_string("");
					lcd_put_cur(1, 0);
					
					}
					else 
							{
										buzzer_counter++;
										
										sprintf((char*)str, "%s", Failed);
										lcd_put_cur(1, 0);
										lcd_send_string((char*)str);
										//clearing
										memcpy(user_appear, empty, sizeof (empty));
								
										memcpy(user_pass_appear, empty2, sizeof (empty2));
										HAL_Delay(1000);
										
										lcd_put_cur(1, 0);
										sprintf((char*)str, "%s", user_appear);	
										lcd_send_string((char*)str);
										
										if (buzzer_counter==3){
											//buzzer_enable
											send='B';
											HAL_UART_Transmit(&huart2, &send, sizeof(send), 100);// this should be LCD
											send=' ';
											buzzer_counter=0;
											
										}
										counter=0;
										counter2=0;
										passflag=0;
										
									lcd_put_cur(0, 0);
									lcd_clear();
									
								
								lcd_send_string("Userid");
								lcd_send_string("");
								lcd_put_cur(1, 0);
									}					
					
					
			
		
			
			//memcpy(user_pass, empty, sizeof (empty));
		}

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
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA3 PA4
                           PA5 PA6 PA7 PA8
                           PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
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
