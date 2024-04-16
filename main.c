#include "pico/stdlib.h"

#include <stdio.h>
#include "pico/stdlib.h"
// 74HC595 PINS
#define SER      (18)
#define SRCLK     (19) //PIN_CLK 
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

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val){

  uint8_t i;

  for (i = 0; i < 8; i++)  {
    gpio_put(dataPin, val & 1);
    val >>= 1;
    gpio_put(clockPin, 1);
    gpio_put(clockPin, 0);
  }
}

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

    while (1) {


    
        for(uint8_t i=0; i < sizeof(patterns)/sizeof(uint8_t); i++){

          gpio_put(RCLK, 0);
          shiftOut(SER, SRCLK, patterns[i]);
          gpio_put(RCLK, 1);

          sleep_ms(1000);
     
        }

    }
}