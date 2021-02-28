#ifndef __COL_WAVE_H__
#define __COL_WAVE_H__
#include "ColDisplayObject.h"

class ColWave: public ColDisplayObject {

  private:
    int amplitude = 4; // Redeners as 2X considers postive half + negative half
    int offset = -4;
    float freq = 1;
    float phase = 0.0;
    float timeStep = 0.01;
    float deltaTime = 0.0;
    float width = 64;
    
    const float double_Pi = 3.14159 * 2;


  public:
  
    //Inherited
    void draw (ColDisplay* cdObject, unsigned long tickCount);
  
};

void ColWave::draw (ColDisplay* cdObject, unsigned long tickCount){
  float countVal = (tickCount%cdObject->getPixelWidth())/10;
  //Serial.println("");
  for (int i = 0; i < width; i++){
    deltaTime = i * timeStep;
    float value = (amplitude * sin(2 * double_Pi * (freq+countVal) * deltaTime + phase))-offset;
    //Serial.print("\nValue: ");
    //Serial.print(countVal);
    //Serial.print(",");
    cdObject->setPixel (i,value,HIGH);
  }
  
}

#endif
