#include "AS1108.h"
#include <util/delay.h>

void initSPI(void) {
  SPI_SS_DDR |= (1 << SPI_SS);                        /* set SS output */
  SPI_SS_PORT |= (1 << SPI_SS);       /* start off not selected (high) */

  SPI_MOSI_DDR |= (1 << SPI_MOSI);                   /* output on MOSI */
  SPI_MISO_PORT |= (1 << SPI_MISO);                  /* pullup on MISO */
  SPI_SCK_DDR |= (1 << SPI_SCK);                      /* output on SCK */

  /* Don't have to set phase, polarity b/c
   * default works with 25LCxxx chips */
  // SPCR |= (1 << CPOL); // clock rising edge but idle high
  // SPCR |= (1 << CPHA);
  SPCR |= (1 << SPR0);                /* div 16, safer for breadboards */
  SPCR |= (1 << MSTR);                                  /* clockmaster */
  SPCR |= (1 << SPE);                                        /* enable */
}

void SPI_tradeByte(uint8_t byte) {
  SPDR = byte;                       /* SPI starts sending immediately */
  loop_until_bit_is_set(SPSR, SPIF);                /* wait until done */
                                /* SPDR now contains the received byte */
}

void DISPLAY_writeByte(uint8_t address, uint8_t byte) {
  SLAVE_SELECT;
  SPI_tradeByte(address);
  SPI_tradeByte(byte);
  SLAVE_DESELECT;
  SPI_tradeByte(byte);

}

void DISPLAY_test() {
  // Note: these data byte values just come straight from the AS1108 datasheet.
  DISPLAY_writeByte(DISPLAY_TEST_ADDRESS, 0xF);
}

void DISPLAY_setNoDecodeMode() {
  DISPLAY_writeByte(DECODE_MODE_ADDRESS, 0x0);
}

void DISPLAY_setDecodeAllMode() {
  DISPLAY_writeByte(DECODE_MODE_ADDRESS, 0xF);
}

void DISPLAY_setScanLimit(uint8_t byte) {
  DISPLAY_writeByte(SCAN_LIMIT_ADDRESS, byte);
}

// MARK: Intensity control register
void DISPLAY_setBrightness(uint8_t byte) {
  DISPLAY_writeByte(INTENSITY_CONTROL_ADDRESS, byte);
}

// MARK: Feature Register controls

/* Note: The feature register is byte initialized to 0 on power
 up so I have a global to prevent overwriting existing values
 when using the functions below */
uint8_t featureData = 0x00;

void DISPLAY_setCodeBMode() {
  // bit-wise trick to set 0 at feature decode select bit without changing other bites
  featureData &= ~(1 << FEATURE_DECODE_SELECT);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_setHexDecodeMode() {
  featureData |= (1 << FEATURE_DECODE_SELECT);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_setSPIEnable() {
  featureData |= (1 << FEATURE_SPI_ENABLE);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_enableBlinking() {
  featureData |= (1 << FEATURE_BLINK_ENABLE);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_disableBlinking() {
  featureData &= ~(1 << FEATURE_BLINK_ENABLE);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_setLowBlinkFrequency() {
  featureData |= (1 << FEATURE_BLINK_FREQ_SELECT);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_setHighBlinkFrequency() {
  featureData &= ~(1 << FEATURE_BLINK_FREQ_SELECT);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}

void DISPLAY_reset() {
  featureData |= (1 << FEATURE_CONTROL_REGISTER_RESET);
  DISPLAY_writeByte(FEATURE_ADDRESS, featureData);
}
