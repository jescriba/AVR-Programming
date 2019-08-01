// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include "organ.h"
#include "scale16.h"
#include "pinDefines.h"
#include "USART.h"
#include "25LC256.h"

int main(void) {
  uint8_t i;
  uint8_t address;

  // -------- Inits --------- //
  initSPI();
  initUSART();
  EEPROM_writeByte(address, i);
  return 0;
}
