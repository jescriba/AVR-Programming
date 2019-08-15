#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"
#include "MIDI.h"

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
   if (MIDI_isNoteOn(message)) {
     uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
      struct MIDI_note note = MIDI_note(message2);
      DISPLAY_writeChar(DIGIT_0_ADDRESS, note.noteChars[0]);
      DISPLAY_writeChar(DIGIT_1_ADDRESS, note.noteChars[1]);
      DISPLAY_writeChar(DIGIT_2_ADDRESS, note.octaveChar);
    } else if (MIDI_isNoteOff(message)) {
     uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
     uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
     DISPLAY_writeByte(DIGIT_0_ADDRESS, 0);
   } else {
      DISPLAY_writeByte(DIGIT_3_ADDRESS, 1 << message);
    }
 }
  return 0;
}
