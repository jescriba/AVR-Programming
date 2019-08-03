#include <avr/io.h>
#include "pinDefines.h"

#define SLAVE_SELECT    SPI_SS_PORT &= ~(1 << SPI_SS)
#define SLAVE_DESELECT  SPI_SS_PORT |= (1 << SPI_SS)

// Functions

                  /* Init SPI to run EEPROM with phase, polarity = 0,0 */
void initSPI(void);

                  /* Generic.  Just loads up HW SPI register and waits */
void SPI_tradeByte(uint8_t byte);

                          /* writes two bytes */
void DISPLAY_writeWord(uint16_t word);
