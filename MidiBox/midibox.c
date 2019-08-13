#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"

int isNoteOn(uint8_t message) {
  // bit math to check if message is 0x9n
  return (((message >> 4) & 0x0F) == 0x09);
}

int isNoteOff(uint8_t message) {
  return (((message >> 4) & 0x0F) == 0x08);
}

int main(void) {
  // HACK for flickering display on power up :/ investigate why
  _delay_ms(2000);
  initSPI();
  initUSART();
  DISPLAY_defaultConfig();
  DISPLAY_defaultTest();

  int counter = 0;
  while(1) {
    uint8_t message = receiveByte(); // assuming note off 8x or on 9x
    if (isNoteOn(message)) {
      uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
      DISPLAY_writeByte(DIGIT_0_ADDRESS, message2);
    } else if (isNoteOff(message)) {
      uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
      DISPLAY_writeByte(DIGIT_0_ADDRESS, 0);
    } else {
      // counter += 1;
      // counter %= 7;
      // DISPLAY_writeByte(DIGIT_0_ADDRESS, 1 << counter);
    }
    // uint8_t message2 = receiveByte();
    // DISPLAY_writeByte(DIGIT_1_ADDRESS, message2);
    // uint8_t message3 = receiveByte();
    // DISPLAY_writeByte(DIGIT_2_ADDRESS, message3);
  }
  return 0;
}
