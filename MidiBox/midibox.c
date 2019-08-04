// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"

int main(void) {
  uint16_t i = 0xFF;

  // -------- Inits --------- //
  initSPI();
  initUSART();
  _delay_ms(3000);
  DISPLAY_writeWord(i);
  return 0;
}
