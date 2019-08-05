#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"

int main(void) {
  initSPI();
  initUSART();

 DISPLAY_reset();
 // DISPLAY_setSPIEnable();
 // DISPLAY_setScanLimit(3);
 // //DISPLAY_setBrightness(0x2);
 // DISPLAY_setDecodeAllMode();
 // DISPLAY_setHexDecodeMode();

 for (int j = 0; j < 2000; j++) {
   _delay_ms(5);
   //DISPLAY_test();
   DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b1000); // should be a 6 in hex mode
   DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b0000);
   DISPLAY_writeByte(DIGIT_2_ADDRESS, 0b0000);
   DISPLAY_writeByte(DIGIT_3_ADDRESS, 0b1000);
 }

  // DISPLAY_enableBlinking();
  // DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b1000); // should be a 6 in hex mode
  // DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b0000);
  // DISPLAY_writeByte(DIGIT_2_ADDRESS, 0b0000);
  // DISPLAY_writeByte(DIGIT_3_ADDRESS, 0b1000);

  return 0;
}
