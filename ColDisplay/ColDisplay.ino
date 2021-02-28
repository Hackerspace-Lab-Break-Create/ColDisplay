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
  
  //colEngine.addDisplayObject(&colWord);
  
  //colWord.setWord((char*)"HLBC\0");
  //colWord.printDisplay();

  colWaveWord.setWord((char*)"HLBC\0");
  colEngine.addDisplayObject(&colWaveWord);

  //colEngine.addDisplayObject (&colWave);
  
  int leds[8] = {9,8,7,6,5,4,3,2};
  colDisplay.setLeds((int*)leds);

  
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
