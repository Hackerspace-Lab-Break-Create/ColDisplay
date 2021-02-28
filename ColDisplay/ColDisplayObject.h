#ifndef __COL_DISPLAY_OBJECT_H__
#define __COL_DISPLAY_OBJECT_H__
#include "ColDisplay.h"

class ColDisplayObject {
  public:
    virtual void draw (ColDisplay* cdObject, unsigned long tickCount) = 0;
    
    
    int xpos;
    int ypos;
};

#endif
