#include "pico/stdlib.h"

#include <stdio.h>
#include "pico/stdlib.h"
// 74HC595 PINS
#define SER      (18)
#define SRCLK    (19) //PIN_CLK 
#define RCLK     (20) //PIN_LATCH

uint8_t patterns[] = {
  0b01100000, //1
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110, //5
  0b10111110,
  0b11100000,
  0b11111110,
  0b11110110,
};

uint8_t patterns2[] = {
  0b11000000, //1
  0b01100000,
  0b00110000,
  0b00011000,
  0b00001000, //5
  0b00000100,
  0b00000010,
  0b00000001,
  0b00000000,
};

uint8_t patterns3[] = {
  0b00110000,
  0b01010000,
  0b01100000, //1
  0b01100000, //1
  0b00110000,
  0b01010000,
  0b01100000, //1
  0b00110000,
  0b01010000,
 
 
};

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val){

  uint8_t i;

  for (i = 0; i < 8; i++)  {
    gpio_put(dataPin, val & 1);
    sleep_us(1);
    val >>= 1;
    gpio_put(clockPin, 1);
    sleep_us(1);
    gpio_put(clockPin, 0);
    sleep_us(1);
  }
}

uint16_t* sel(int16_t* arr ,int32_t num){
  
  arr[0] = (int16_t)(num / 100);

  arr[1] = (int16_t)((num % 100) / 10);

  arr[2] = (int16_t)(num % 10);

  return arr;
};

int main()
{
    stdio_init_all();
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    gpio_init(SER);
    gpio_init(RCLK);
    gpio_init(SRCLK);
    gpio_set_dir(SER, GPIO_OUT);
    gpio_set_dir(RCLK, GPIO_OUT);
    gpio_set_dir(SRCLK, GPIO_OUT);

    int temp = 299;

    int16_t arr[3] = {0};
    while (1) {
        
        sel(arr,temp);

        for(uint8_t i=0; i < 3; i++){

          gpio_put(RCLK, 0);
          
          shiftOut(SER, SRCLK, patterns3[i]);
          shiftOut(SER, SRCLK, patterns2[i]);
          if(arr[i] < 0){
            arr[i] = arr[i] * -1;
            shiftOut(SER, SRCLK, patterns[arr[i] - 1]);
          } else {
            shiftOut(SER, SRCLK, patterns[arr[i] - 1]);
          }
        

          gpio_put(RCLK, 1);

          sleep_us(16);
     
        }

    }
}