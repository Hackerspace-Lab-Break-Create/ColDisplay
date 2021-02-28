#ifndef __COL_ENGINE_H__
#define __COL_ENGINE_H__

#include <Vector.h>

#include "ColDisplay.h"
#include "ColDisplayObject.h"




class ColEngine {
  private:
    static const int ELEMENT_COUNT_MAX = 50;
    ColDisplayObject* storage_array[ELEMENT_COUNT_MAX];

     Vector<ColDisplayObject*> dObjects;
    
    ColDisplay* colDisplay;

    unsigned long tickCount = 0;
    
  public:

    ColEngine (){
      dObjects.setStorage(storage_array);
    }
    
    void addDisplayObject (ColDisplayObject* cdObject){
      dObjects.push_back(cdObject);
    }

    ColDisplay* getColDisplay (){return colDisplay;}
    void setColDisplay (ColDisplay* rDisplay){colDisplay = rDisplay;}
    void tick ();
    

};


void ColEngine::tick (){
  colDisplay->clearBuffer();
  for (int i = 0; i < dObjects.size(); i++){
    dObjects[i]->draw(colDisplay, tickCount);
  }
  
  //colDisplay->displayNextCol();


  tickCount++;
}
#endif
