#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"
#include "USART.h"
#include "AS1108.h"
#include "MIDI.h"

#include "organ.h"
#include "scale16.h"
#include "USART.h"

#include <stdio.h>
#include <stdlib.h>

#define NOTE_DURATION     0xF000        /* determines long note length */

int main(void) {
  // HACK for flickering display on power up :/ investigate why
  _delay_ms(2000);
  initSPI();
  initUSART();

  DISPLAY_defaultConfig();
  DISPLAY_defaultTest();
  DISPLAY_writeChars("HOLA");

  while(1) {
    uint8_t message = receiveByte(); // assuming note off 8x or on 9x
    DISPLAY_writeByte(DIGIT_3_ADDRESS, 0);
    if (MIDI_isNoteOn(message) ) {
       uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
       uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
       struct MIDI_note note = MIDI_note(message2);
       DISPLAY_writeChar(DIGIT_0_ADDRESS, note.noteChars[0]);
       if (note.noteChars[1] == '-') {
         DISPLAY_writeChar(DIGIT_1_ADDRESS, note.octaveChar);
         DISPLAY_writeChar(DIGIT_2_ADDRESS, 0);
       } else {
         DISPLAY_writeChar(DIGIT_1_ADDRESS, note.noteChars[1]);
         DISPLAY_writeChar(DIGIT_2_ADDRESS, note.octaveChar);
       }
     } else if (MIDI_isNoteOff(message)) {
      uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
      DISPLAY_writeByte(DIGIT_0_ADDRESS, 0);
    }
  }


//   while(1) {
  //DISPLAY_setExternalClock();

  /* Intializes random number generator */
  // while(1) {
  //   DISPLAY_writeChar(DIGIT_0_ADDRESS, '3');
  //   // DISPLAY_writeChar(DIGIT_1_ADDRESS, '4');
  //   // DISPLAY_writeChar(DIGIT_2_ADDRESS, '5');
  //   // DISPLAY_writeChar(DIGIT_3_ADDRESS, '6');
  //   // _delay_ms(1000);
  // // //_delay_ms(700);
  // // DISPLAY_writeByte(DIGIT_0_ADDRESS, 0b01111001);
  // //DISPLAY_writeByte(DIGIT_1_ADDRESS, 0x01);
  // //DISPLAY_writeByte(DIGIT_2_ADDRESS, 0x02);
  // //DISPLAY_writeByte(DIGIT_3_ADDRESS, 0x03);
  //   _delay_ms(30000);
  // }

  // while(1) {
  //   // _delay_ms(2000);
  //   //DISPLAY_defaultTest();
  //   _delay_ms(2000);
  // }

 //  while(1) {
 //    uint8_t message = receiveByte(); // assuming note off 8x or on 9x
 //   if (MIDI_isNoteOn(message) ) {
 //      uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
 //      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
 //      struct MIDI_note note = MIDI_note(message2);
 //      DISPLAY_writeChar(DIGIT_0_ADDRESS, note.noteChars[0]);
 //      DISPLAY_writeChar(DIGIT_1_ADDRESS, note.noteChars[1]);
 //      DISPLAY_writeChar(DIGIT_2_ADDRESS, note.octaveChar);
 //    } else if (MIDI_isNoteOff(message)) {
 //     uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
 //     uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
 //     DISPLAY_writeByte(DIGIT_0_ADDRESS, 0);
 //   } else {
 //      DISPLAY_writeByte(DIGIT_3_ADDRESS, 1 << message);
 //    }
 // }

 // // -------- Inits --------- //
 // SPEAKER_DDR |= (1 << SPEAKER);                 /* speaker for output */
 // initUSART();
 // printString("----- Serial Organ ------\r\n");
 //
 // char fromCompy;                        /* used to store serial input */
 // uint16_t currentNoteLength = NOTE_DURATION / 2;
 // const uint8_t keys[] = { 'a', 'w', 's', 'e', 'd', 'f', 't',
 //   'g', 'y', 'h', 'j', 'i', 'k', 'o',
 //   'l', 'p', ';', '\''
 // };
 // const uint16_t notes[] = { G4, Gx4, A4, Ax4, B4, C5, Cx5,
 //   D5, Dx5, E5, F5, Fx5, G5, Gx5,
 //   A5, Ax5, B5, C6
 // };
 // uint8_t isNote;
 // uint8_t i;
 //
 // // ------ Event loop ------ //
 // while (1) {
 //
 //   //    uint8_t message = receiveByte(); // assuming note off 8x or on 9x
 //   //   if (MIDI_isNoteOn(message)) {
 //   //     uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
 //   //      uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
 //   //      struct MIDI_note note = MIDI_note(message2);
 //   //      DISPLAY_writeChar(DIGIT_0_ADDRESS, note.noteChars[0]);
 //   //      DISPLAY_writeChar(DIGIT_1_ADDRESS, note.noteChars[1]);
 //   //      DISPLAY_writeChar(DIGIT_2_ADDRESS, note.octaveChar);
 //   //    } else if (MIDI_isNoteOff(message)) {
 //   //     uint8_t message2 = receiveByte(); // assuming note off 8x or on 9x
 //   //     uint8_t message3 = receiveByte(); // assuming note off 8x or on 9x
 //   //     DISPLAY_writeByte(DIGIT_0_ADDRESS, 0);
 //   //   } else {
 //
 //
 //   uint8_t message = receiveByte(); // assuming note off 8x or on 9x
 //
 //                              /* Play Notes */
 //   isNote = 0;
 //   if (MIDI_isNoteOn(message)) {
 //     playNote(notes[i], currentNoteLength);
 //     isNote = 1;
 //   }
 //   // for (i = 0; i < sizeof(keys); i++) {
 //   //   if (fromCompy == keys[i]) {       /* found match in lookup table */
 //   //     playNote(notes[i], currentNoteLength);
 //   //     isNote = 1;                  /* record that we've found a note */
 //   //     break;                               /* drop out of for() loop */
 //   //   }
 //   // }
 //
 //                     /* Handle non-note keys: tempo changes and rests */
 //   if (!isNote) {
 //     if (fromCompy == '[') {                   /* code for short note */
 //       currentNoteLength = NOTE_DURATION / 2;
 //     }
 //     else if (fromCompy == ']') {               /* code for long note */
 //       currentNoteLength = NOTE_DURATION;
 //     }
 //     else {                                /* unrecognized, just rest */
 //       rest(currentNoteLength);
 //     }
 //   }
 //
 // }
  return 0;
}
