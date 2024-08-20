/*
 * base.h
 *
 *  Created on: Aug 19, 2024
 *      Author: han
 */

#ifndef INC_BASE_H_
#define INC_BASE_H_


#include "stm32f1xx_hal.h"
#include <stdbool.h>



#define RESET_1_Pin GPIO_PIN_13
#define RESET_1_GPIO_Port GPIOC
#define SIREN_EN_Pin GPIO_PIN_0
#define SIREN_EN_GPIO_Port GPIOD
#define BUZZER_EN_Pin GPIO_PIN_1
#define BUZZER_EN_GPIO_Port GPIOD
#define BLUECONFIG_Pin GPIO_PIN_0
#define BLUECONFIG_GPIO_Port GPIOC
#define DIPSW3_Pin GPIO_PIN_1
#define DIPSW3_GPIO_Port GPIOC
#define DIPSW4_Pin GPIO_PIN_2
#define DIPSW4_GPIO_Port GPIOC
#define RSEN_Pin GPIO_PIN_1
#define RSEN_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define P5_PWR_Pin GPIO_PIN_4
#define P5_PWR_GPIO_Port GPIOC
#define RL1_EN_Pin GPIO_PIN_12
#define RL1_EN_GPIO_Port GPIOB
#define LAT_Pin GPIO_PIN_13
#define LAT_GPIO_Port GPIOB
#define CLK_Pin GPIO_PIN_14
#define CLK_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_6
#define OE_GPIO_Port GPIOC
#define D_Pin GPIO_PIN_7
#define D_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_8
#define C_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_9
#define B_GPIO_Port GPIOC
#define A_Pin GPIO_PIN_8
#define A_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOA
#define BUTON_LED_Pin GPIO_PIN_12
#define BUTON_LED_GPIO_Port GPIOA
#define RESET_2_Pin GPIO_PIN_10
#define RESET_2_GPIO_Port GPIOC
#define B2_Pin GPIO_PIN_11
#define B2_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_12
#define B1_GPIO_Port GPIOC
#define G2_Pin GPIO_PIN_2
#define G2_GPIO_Port GPIOD
#define G1_Pin GPIO_PIN_3
#define G1_GPIO_Port GPIOB
#define R2_Pin GPIO_PIN_4
#define R2_GPIO_Port GPIOB
#define R1_Pin GPIO_PIN_5
#define R1_GPIO_Port GPIOB
#define PWMHOPEN_Pin GPIO_PIN_7
#define PWMHOPEN_GPIO_Port GPIOB

#define REAL_BUZZER GPIO_PIN_15
#define REAL_BUZZER_Port GPIOA


#define CLK_H HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
#define CLK_L HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);

#define OE_H HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_SET);
#define OE_L HAL_GPIO_WritePin(OE_GPIO_Port, OE_Pin, GPIO_PIN_RESET);

#define LAT_H HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_SET);
#define LAT_L HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_RESET);

#define R1_H HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
#define R1_L HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);

#define R2_H HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
#define R2_L HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);

#define G1_H HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_SET);
#define G1_L HAL_GPIO_WritePin(G1_GPIO_Port, G1_Pin, GPIO_PIN_RESET);

#define G2_H HAL_GPIO_WritePin(G2_GPIO_Port, G2_Pin, GPIO_PIN_SET);
#define G2_L HAL_GPIO_WritePin(G2_GPIO_Port, G2_Pin, GPIO_PIN_RESET);

#define B1_H HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_SET);
#define B1_L HAL_GPIO_WritePin(B1_GPIO_Port, B1_Pin, GPIO_PIN_RESET);

#define B2_H HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_SET);
#define B2_L HAL_GPIO_WritePin(B2_GPIO_Port, B2_Pin, GPIO_PIN_RESET);

#define R1(X)		(X) ? (R1_GPIO_Port->BSRR = R1_Pin) : (R1_GPIO_Port->BRR = R1_Pin);
#define R2(X)		(X) ? (R2_GPIO_Port->BSRR = R2_Pin) : (R2_GPIO_Port->BRR = R2_Pin);
#define G1(X)		(X) ? (G1_GPIO_Port->BSRR = G1_Pin) : (G1_GPIO_Port->BRR = G1_Pin);
#define G2(X)		(X) ? (G2_GPIO_Port->BSRR = G2_Pin) : (G2_GPIO_Port->BRR = G2_Pin);
#define B1(X)		(X) ? (B1_GPIO_Port->BSRR = B1_Pin) : (B1_GPIO_Port->BRR = B1_Pin);
#define B2(X)		(X) ? (B2_GPIO_Port->BSRR = B2_Pin) : (B2_GPIO_Port->BRR = B2_Pin);


#define ROW(X)		(X & 0x1) ? (A_GPIO_Port->BSRR = A_Pin) : (A_GPIO_Port->BRR = A_Pin); \
					(X & 0x2) ? (B_GPIO_Port->BSRR = B_Pin) : (B_GPIO_Port->BRR = B_Pin); \
					(X & 0x4) ? (C_GPIO_Port->BSRR = C_Pin) : (C_GPIO_Port->BRR = C_Pin); \
					(X & 0x8) ? (D_GPIO_Port->BSRR = D_Pin) : (D_GPIO_Port->BRR = D_Pin);  // (X and 0xX) 0 ise ilgili pin 0 değilse 1


// make gpio_output control c6 (output enable pin)
#define OE_TIMER_DISABLE GPIOC->CRL &= 0xF3FFFFFF
// make the timer3 control c6 (output enable pin)
#define OE_TIMER_ENABLE  GPIOC->CRL |= 0x08000000


#define BUTTON_Pin GPIO_PIN_10
#define BUTTON_GPIO_Port GPIOC

#define WIDTH 64
#define HEIGHT 32

#define TEARING_FIX 1

#define dino_game 0
#define display_string 1


#endif /* INC_BASE_H_ */
