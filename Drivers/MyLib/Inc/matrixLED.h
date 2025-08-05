#ifndef __MATRIX_LED_H__
#define __MATRIX_LED_H__

#include "stm32f0xx_hal.h" 

#define MATRIX_ROWS 16

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} matrixLED_gpio;

typedef struct {
    matrixLED_gpio gpio[MATRIX_ROWS];
} matrixLED_HandleTypeDef;

extern uint32_t gpioa_moder[16];
extern uint32_t gpiof_moder[16];

extern uint32_t gpioa_odr[16];
extern uint32_t gpiof_odr[16];

void DMA_Init_All(void);
void matrixLED_init(void);
void matrixLED_clear(void);
void matrixLED_update(matrixLED_HandleTypeDef* hmatrix, const uint16_t data_buffer[16]);
void matrixLED_write(void);

#endif
