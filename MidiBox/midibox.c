#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"

int main(void) {
  initSPI();
  initUSART();
  DISPLAY_setupNormalOperation();
  //DISPLAY_setSPIEnable();
  DISPLAY_setScanLimit(3);
  DISPLAY_setBrightness(0x33);
  DISPLAY_setDecodeAllMode();
  DISPLAY_setHexDecodeMode();

  DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b00000011); // should be a 6 in hex mode
  DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b00000011);
  DISPLAY_writeByte(DIGIT_2_ADDRESS, 0b00000011);
  DISPLAY_writeByte(DIGIT_3_ADDRESS, 0b00000011);

  // TODO: Clean up the SPI and USART setup to be interrupt based instead
  while(1) {
    uint8_t message = receiveByte(); // assuming note off 8x or on 9x
    uint8_t previous = 0;
    // if ((message >> 4) != 0x08 && (message >> 4) != 0x09 && previous != message) {
    //   DISPLAY_writeByte(DIGIT_0_ADDRESS, message); // should be a 6 in hex mode
    //   DISPLAY_writeByte(DIGIT_1_ADDRESS, message);
    //   DISPLAY_writeByte(DIGIT_2_ADDRESS, message);
    //   DISPLAY_writeByte(DIGIT_3_ADDRESS, message);
    //   previous = message;
    //   continue;
    // }
    //uint8_t data1 = receiveByte(); // usually note num
    //uint8_t data2 = receiveByte(); // usually velocity
    if ((message >> 4) == 0x08) {
      DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b00000000); // should be a 6 in hex mode
      DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b00000000);
      //DISPLAY_writeByte(DIGIT_2_ADDRESS, data1);
      //DISPLAY_writeByte(DIGIT_3_ADDRESS, data2);
    } else if((message >> 4) == 0x09) {
      DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b00000001); // should be a 6 in hex mode
      DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b00000001);
      //DISPLAY_writeByte(DIGIT_2_ADDRESS, data1);
      //DISPLAY_writeByte(DIGIT_3_ADDRESS, data2);
    }
  }

  //DISPLAY_enableBlinking();
  //DISPLAY_reset();
  return 0;
}
