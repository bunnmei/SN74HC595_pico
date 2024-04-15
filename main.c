#include "pico/stdlib.h"

#include <stdio.h>
#include "pico/stdlib.h"
// 74HC595 PINS
#define SER      (18)
#define SRCLK     (19) //PIN_CLK 
#define RCLK     (20) //PIN_LATCH

const uint8_t PATTERNS[] = {
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00100000,
  0b01000000,
  0b10000000,
};

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t val){

  uint8_t i;
  for (i = 0; i < 8; i++)  {
    gpio_put(dataPin, val & 1);
    val >>= 1;
  }

  gpio_put(clockPin, 1);
  gpio_put(clockPin, 0);
}

int main()
{
    stdio_init_all();

    int max_pattern = sizeof(PATTERNS)/sizeof(PATTERNS[0]);

    while (1) {
    
        for(uint8_t i=0; i < max_pattern; i++){
          shiftOut(SER, SRCLK, PATTERNS[i]);

          gpio_put(RCLK, 0);
          gpio_put(RCLK, 1);

          sleep_ms(200);
        }

    }
}