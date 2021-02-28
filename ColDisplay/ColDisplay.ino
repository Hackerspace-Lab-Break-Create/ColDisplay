#include "ColDisplay.h"
#include "ColEngine.h"
#include "ColWord.h"

#include <arduino-timer.h>

Timer<10, micros> timer;

ColDisplay colDisplay;
ColWord colWord;
ColEngine colEngine;

float wav1[3];//0 frequency, 1 unscaled amplitude, 2 is final amplitude
int average;
const int Pin = 9;
float time;
float percentage;
float templitude;
float offset = 3; // default value 2.5 volt as operating range voltage is 0~5V
float minOutputScale = -1.0;
float maxOutputScale = 7.0;
const int resolution = 1; //this determines the update speed. A lower number means a higher refresh rate.
const float pi = 3.14159;

int vals[32];

float rotFreq = 15; //hz
int counter = 0;
int freqSet = -5;
bool updateCol (void* argument){
  colDisplay.displayNextCol();

  if (counter++ > (colDisplay.getPixelWidth()-1)*2){
    counter =0;
    wav1[0] += freqSet;
    
    if (wav1[0] < 1){
      freqSet = 5;
    }

    if (wav1[0] > 250){
      freqSet = -5;
    }
    //Serial.println (wav1[0]);
    makeWave(NULL);
  }

  
  //colDisplay.printDisplay();
  return true;
}
void setup() {
  Serial.begin(115200);
  colEngine.setColDisplay(&colDisplay);
  colEngine.addDisplayObject(&colWord);
  
  colWord.setWord((char*)"ABC$\0");
  colWord.printDisplay();

  
  int leds[8] = {9,8,7,6,5,4,3,2};
  colDisplay.setLeds((int*)leds);

  
  //configureTimer();
  
  colDisplay.printDisplay();

  wav1[0] = 200; //frequency of the sine wave
  wav1[1] =2.5; // 0V - 2.5V amplitude (Max amplitude + offset) value must not exceed the "maxOutputScale"
  
  pinMode (13, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
//  int leds[8] = {9,8,7,6,5,4,3,2};
//  colDisplay.setLeds((int*)leds);
//  //colDisplay.setPixelWidth(32);
//
//  float pixelTimeStep = ((1/rotFreq)*1000000)/colDisplay.getPixelWidth();
//  Serial.print("pixelTimeStep: ");
//  Serial.println(pixelTimeStep);
//  
//  timer.every(pixelTimeStep,updateCol);
//  makeWave(NULL);
//
//  colDisplay.setPixel(5,2,true);
//  for (int y = 0; y < 4; y ++){
//    for (int x = 0; x < 32; x++){
//      Serial.print(colDisplay.getPixel(x,y));
//    }
//    Serial.println(" ");
//  }
//
//  Serial.println("===");
//
//  for (int x = 0; x < 32;x++){
//    
//  }
  
  // A
  byte letter[][2] = 
    {
      {0b01110000,0b11111111},
      {0b10001000,0b11110001},
      {0b10001000,0b11110001},
      {0b11111000,0b11110001},
      {0b10001000,0b11110001},
      {0b10001000,0b11110001},
      {0b10001000,0b11110001},
      {0b00000000,0b11111111}
    };
//byte letter[][2] = 
//    {
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000},
//      {0b11111111,0b00000000}
//    };
   colDisplay.setBytes(0,0,(byte*)letter,8,2);
//
//    for(int i = 0; i < 8;i++){
//      colDisplay.fillBuffer(0b00000000);
//      colDisplay.setBytes (i,0,(byte*)letter,8,2);
//      colDisplay.printDisplay ();  
//    }
// 
//
//    colDisplay.setPixel (0,0,true);
    colDisplay.printDisplay();



}

boolean makeWave (void* arugment){
  colDisplay.fillBuffer(0b00000000);

  int numberOfBytesToFill = 15;
  for (int i = 0; i < numberOfBytesToFill *8; i++){
    time = micros()% 1000000;
    percentage = time / 1000000;
    templitude = sin(((percentage) * wav1[0]) * 2 * pi);
    wav1[2] = (templitude * wav1[1]) + offset; //shift the origin of sinewave with offset.
  
    // clip the max and min output
    if (wav1[2]>maxOutputScale){
      wav1[2] = maxOutputScale;
    }
    else if (wav1[2]<minOutputScale){
      wav1[2] = minOutputScale;
    }
    else{
      //do nothing
    }
    average = mapf(wav1[2],minOutputScale,maxOutputScale,-1,9);
  
    colDisplay.setPixel(i,average,HIGH);

    
  }
//colDisplay.printDisplay();
  return true;
  
}
void loop() {
  //timer.tick();
  colEngine.tick();
  colDisplay.printDisplay();
  //delay(500);



//  
//  
//  
//  if (counter > 32){
//    counter =0;
//    colDisplay.fillBuffer(0b00000000);
//    for (int i =0;i<32;i++){
//      
//      colDisplay.setPixel (i,vals[i],HIGH);
//    }
//    colDisplay.printDisplay();
//  }
// 
//   colDisplay.updateLoop();
}
long mapf(float x, float in_min, float in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
