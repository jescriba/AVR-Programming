#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"

int main(void) {
  initSPI();
  initUSART();
  DISPLAY_writeByte(SHUTDOWN_ADDRESS, 0xFF);
  //DISPLAY_setSPIEnable();
  DISPLAY_setScanLimit(3);
  DISPLAY_setBrightness(0x33);
  DISPLAY_setDecodeAllMode();
  DISPLAY_setHexDecodeMode();

  DISPLAY_enableBlinking();
  DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b00001000); // should be a 6 in hex mode
  DISPLAY_writeByte(DIGIT_1_ADDRESS, 0b00000000);
  DISPLAY_writeByte(DIGIT_2_ADDRESS, 0b00000000);
  DISPLAY_writeByte(DIGIT_3_ADDRESS, 0b00001000);

  //DISPLAY_reset();
  return 0;
}
