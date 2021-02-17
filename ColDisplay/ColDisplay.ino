#include "ColDisplay.h"


ColDisplay colDisplay;

float wav1[3];//0 frequency, 1 unscaled amplitude, 2 is final amplitude
int average;
const int Pin = 9;
float time;
float percentage;
float templitude;
float offset = 4; // default value 2.5 volt as operating range voltage is 0~5V
float minOutputScale = 0.0;
float maxOutputScale = 8.0;
const int resolution = 1; //this determines the update speed. A lower number means a higher refresh rate.
const float pi = 3.14159;

int vals[32];

void setup() {
  
  //configureTimer();
  Serial.begin(115200);
  colDisplay.printDisplay();

  wav1[0] = 150; //frequency of the sine wave
  wav1[1] = 2.5; // 0V - 2.5V amplitude (Max amplitude + offset) value must not exceed the "maxOutputScale"
  

//  // A
//  byte letter[][2] = 
//    {
//      {0b01110000,0b11111111},
//      {0b10001000,0b11110001},
//      {0b10001000,0b11110001},
//      {0b11111000,0b11110001},
//      {0b10001000,0b11110001},
//      {0b10001000,0b11110001},
//      {0b10001000,0b11110001},
//      {0b00000000,0b11111111}
//    };
//
//    for(int i = 0; i < 8;i++){
//      colDisplay.fillBuffer(0b00000000);
//      colDisplay.setBytes (i,0,(byte*)letter,8,2);
//      colDisplay.printDisplay ();  
//    }
// 
//
//    colDisplay.setPixel (0,0,true);
//    colDisplay.printDisplay();
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

int counter=0;
void loop() {
  
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
  average = mapf(wav1[2],minOutputScale,maxOutputScale,0,8);

  vals[counter++] = average;
  
  
  
  if (counter > 32){
    counter =0;
    colDisplay.fillBuffer(0b00000000);
    for (int i =0;i<32;i++){
      
      colDisplay.setPixel (i,vals[i],HIGH);
    }
    colDisplay.printDisplay();
  }
 
   colDisplay.updateLoop();
}
long mapf(float x, float in_min, float in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
