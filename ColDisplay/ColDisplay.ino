
const static int MAX_WIDTH = 16;  //BYTES
const static int MAX_HEIGHT = 8; //LEDS
const static int MAX_LETTERS = 5;  //BYTES

#include "ColDisplay.h"
#include "ColEngine.h"
#include "ColWord.h"
#include "ColWave.h"
#include "ColWaveWord.h"

#include <arduino-timer.h>

Timer<10, micros> timer;

ColDisplay colDisplay;
ColWord colWord;
ColWave colWave;
ColEngine colEngine;
ColWaveWord colWaveWord;

float rotFreq = 15.5; //hz

void setup() {
  Serial.begin(115200);
  colEngine.setColDisplay(&colDisplay);
  colEngine.setDisplayCallback (&pushDisplay);
  
  //colEngine.addDisplayObject(&colWord);
  
  //colWord.setWord((char*)"HLBC\0");
  //colWord.printDisplay();

  colWaveWord.setWord((char*)"HLBC\0");
  colEngine.addDisplayObject(&colWaveWord);

  //colEngine.addDisplayObject (&colWave);


  
  //configureTimer();
  
  pinMode (13, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);

  float pixelTimeStep = ((1/rotFreq)*1000000)/colDisplay.getPixelWidth();
  //Serial.print("pixelTimeStep: ");
  //Serial.println(pixelTimeStep);
  
  timer.every(pixelTimeStep,updateCol);
}

void pushDisplay (){

  byte* values = colDisplay.getNextCol();
  
  digitalWrite(9, values[0]);
  digitalWrite(8, values[1]);
  digitalWrite(7, values[2]);
  digitalWrite(6, values[3]);
  digitalWrite(5, values[4]);
  digitalWrite(4, values[5]);
  digitalWrite(3, values[6]);
  digitalWrite(2, values[7]);

  
  //colDisplay.printDisplay();
}

bool updateCol (void*){
  colEngine.tick();
  return true;
}

void loop() {
  timer.tick();
  //colEngine.tick();
  //colDisplay.printDisplay();
  //delay(500);

}
