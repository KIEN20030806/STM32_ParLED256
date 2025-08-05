#include "matrixLED.h"
#include "main.h"
#include <string.h>

uint32_t gpioa_moder[16]; 
uint32_t gpiof_moder[16];

uint32_t gpioa_odr[16]; 
uint32_t gpiof_odr[16];

void matrixLED_init(void) {
}

void matrixLED_clear(void) {
  memset(gpioa_odr, 0, sizeof(gpioa_odr));
  memset(gpiof_odr, 0, sizeof(gpiof_odr));
}

void matrixLED_update(matrixLED_HandleTypeDef* hmatrix, const uint16_t data_buffer[16]) {
  for (uint8_t col = 0; col < 16; col++) {
    for (uint8_t row = 0; row < 16 ; row++) {
      uint8_t bit_index = (row < col) ? row : row - 1;
      GPIO_TypeDef* port = hmatrix->gpio[row].port;
      uint16_t pin = hmatrix->gpio[row].pin;

      if (port == GPIOA){
        if (row == col){
          gpioa_moder[col] &= ~(0x3 << (2 * pin));
          gpioa_moder[col] |=  (0x1 << (2 * pin));
          gpioa_odr[col] |= (1 << (pin + 16));
        }
        else if (data_buffer[col] & (1 << bit_index)){
          gpioa_odr[col] |= (1 << pin);
          gpioa_moder[col] &= ~(0x3 << (2 * pin));
          gpioa_moder[col] |=  (0x1 << (2 * pin));
        }
        else{
          gpioa_moder[col] &= ~(0x3 << (2 * pin));
        }
      } 
      else {
        if (row == col){
          gpiof_moder[col] &= ~(0x3 << (2 * pin));
          gpiof_moder[col] |=  (0x1 << (2 * pin));
          gpiof_odr[col] |= (1 << (pin + 16));
        }
        else if (data_buffer[col] & (1 << bit_index)){
          gpiof_odr[col] |= (1 << pin);
          gpiof_moder[col] &= ~(0x3 << (2 * pin));
          gpiof_moder[col] |=  (0x1 << (2 * pin));
        }
        else{
          gpiof_moder[col] &= ~(0x3 << (2 * pin));
        }
      }
    } 
  }
}

void matrixLED_write(void) {

}
