
#define speakerPin 13

// Scale in the key of 25000
// Automatically generated by scaleGenerator.py

#include "scale8.h"
#define SPEAKER_DDR       DDRD
#define SPEAKER           PD6           /* OC0A */

#define NOTE_DURATION     0xF000        /* determines long note length */


char fromCompy;                        /* used to store serial input */
uint16_t currentNoteLength = NOTE_DURATION / 2;
const uint8_t keys[] = { 'A', 'W', 'S', 'E', 'D', 'F', 'T',
  'G', 'Y', 'H', 'J', 'I', 'K', 'O',
  'L', 'P', ';', '\''
};
uint8_t isNote;

volatile uint8_t note = 0;
const uint8_t notes[] = {C2, E2, G2, C3};
const uint8_t duration[] = {200, 200, 200, 400};
 
static inline void playNote(uint8_t wavelength, uint16_t duration) {

  OCR0A = wavelength;                                     /* set pitch */
  SPEAKER_DDR |= (1 << SPEAKER);           /* enable output on speaker */

  SPEAKER_DDR &= ~(1 << SPEAKER);                  /* turn speaker off */
}

static inline void initTimer(void) {
  // reset timer 0 control registers
  
  TCCR0B = 0;  
  TCCR0A = 0;
  
  TCCR0A |= (1 << WGM01);                                  /* CTC mode */
  TCCR0A |= (1 << COM0A0);           /* Toggles pin each cycle through */
  TCCR0B |= (1 << CS00) | (1 << CS01);               /* CPU clock / 64 */

  TCCR1B = 0;  
  TCCR1A = 0;
  TCNT1 = 0;
  TCCR1A |= (1 << WGM01);                                  /* CTC mode */
  TCCR1A |= (1 << COM0A0);           /* Toggles pin each cycle through */
  // TCCR1B |= (1 << CS00) | (1 << CS01);               /* CPU clock / 64 */
  TCCR1B |= (1 << CS02);               /* CPU clock / 64 */
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  
}

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if(note == 3) note = 0;
  OCR0A = notes[note];                                     /* set pitch */
  //digitalWrite(speakerPin, digitalRead(speakerPin) ^ 1);   // toggle LED pin
  //if (digitalRead(speakerPin) == LOW)
  ++note;
}

void setup() {
  noInterrupts();
  initTimer();

  // pinMode(13, OUTPUT); // OC0A as output
  pinMode(speakerPin, OUTPUT);
  digitalWrite(speakerPin, HIGH);
  interrupts();
}

void loop() {

  unsigned char colloc, rowloc;

  DDRD = 0xFF;
  KEY_DDR = 0xF0;
  KEY_PRT = 

}
