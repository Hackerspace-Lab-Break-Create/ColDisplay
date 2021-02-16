#include "ColDisplay.h"


ColDisplay colDisplay;
float roundTripTime = 15;//1.8*4; //// Time (Hz) for 1 cycle. 1 complete buffer push + remaining space (total steps in view size)

const int VIEW_SIZE = 8;
const int TOTAL_STEPS = VIEW_SIZE * 8;

void configureTimer () {
  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  // Divide by the size of buffer length to get calls each time step
  //OCR1A = 15624/BUFFER_LENGTH
  // = (16*10^6) / (1*1024) - 1 (must be <65536)

  OCR1A = (16000000 / ((roundTripTime) * 1024) - 1) / TOTAL_STEPS;
  //OCR1A = (16000000 / ((roundTripTime) * 1024) - 1);

  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();

}

void setup() {

  //configureTimer();
  Serial.begin(115200);
  colDisplay.printDisplay();

  // A
  byte letter[][2] = 
      {
        {0b01110000,0b11110000},
        {0b10001000,0b11110000},
        {0b10001000,0b11110000},
        {0b11111000,0b11110000},
        {0b10001000,0b11110000},
        {0b10001000,0b11110000},
        {0b10001000,0b11110000},
        {0b00000000,0b11110000}
      };

    for(int i = 0; i < 40;i++){
      colDisplay.fillBuffer(0b00000000);
      colDisplay.setBytes (i,0,(byte*)letter,8,2);
      colDisplay.printDisplay ();  
    }
 

    colDisplay.setPixel (0,0,true);
    colDisplay.printDisplay();
  // "clock" led so we can see each pulse of the time step
  pinMode (13, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);

}

void loop() {
  
  
 
   colDisplay.updateLoop();
}
