#ifndef __COL_DISPLAY_H__
#define __COL_DISPLAY_H__

#include <Vector.h>

const static int MAX_WIDTH = 16;  //BYTES
const static int MAX_HEIGHT = 8; //LEDS


class ColDisplay{
  private:
    byte displayBuffer[MAX_HEIGHT][MAX_WIDTH];
    int pixelHeight = MAX_HEIGHT; //Number of leds verticaly
    int pixelWidth = MAX_WIDTH * 8;
    int viewWidthNumBytes = MAX_WIDTH; //Number of bytes in view
    int currentCol = 0;
    byte retCol[(MAX_HEIGHT/8)+1];
    int* leds;
      
  public:

    ColDisplay (){
      fillBuffer(0b00000000);
    }

    byte* getCol (int x);
    bool getPixel (int x, int y);
    void updateLoop ();
    void printDisplay();
    void setPixel (int x, int y, bool val);
    void fillBuffer (byte val);
    void fillView ();
    void setBytes (int x, int y, byte* val, int height, int width);
    void displayNextCol ();

    int getPixelHeight (){return pixelHeight;}
    int getPixelWidth() {return pixelWidth;}

    void setPixelWidth (int width) {pixelWidth = width;}
    void setPixelHeight (int height) {pixelWidth = height;}
    void setLeds (int* leds){this->leds = leds;}
};

void ColDisplay::displayNextCol (){
  for (int y = 0; y <pixelHeight;y++){
    digitalWrite (leds[y],getPixel(currentCol,y));
  }

  //Serial.println(currentCol);
  if (currentCol++ >= ((MAX_WIDTH)*8)-1){
    currentCol = 0;
  }
}


void ColDisplay::setBytes (int x, int y, byte* val, int height, int width){
  if (x < 0 || (x/8) > MAX_WIDTH || y < 0 || y > MAX_HEIGHT-1){
    return;
  }
//  Serial.println(*val,BIN);
//  Serial.println("===");
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
     
      byte current = *((val+i*width)+j);
      
      //Serial.print(current,BIN);
      
      for (int m = 0; m < 8; m++){
        int xa = ((x+j)+m +j*8)+x;
        if ( (xa/8) > MAX_WIDTH-1){
          break;
        }
        int ya = y+i;
        
//        Serial.print ("\n\nX,Y, v: ");
//        Serial.print(xa);
//        Serial.print(",");
//        Serial.print(ya);
//        Serial.print(",");
//        Serial.println((7-m));
        setPixel (xa,ya,bitRead(current,7-m));
      }
      //Serial.print (",");
    }
    //Serial.println(" ");
  }


  
}

void ColDisplay::fillBuffer (byte val){
  for (int i = 0; i < MAX_HEIGHT; i++){
        for (int j = 0; j < MAX_WIDTH; j++){
          displayBuffer[i][j] = val;  
        }
      }

}

bool ColDisplay::getPixel (int x, int y){
  if( x < 0 || (x/8) > MAX_WIDTH || y < 0 || y > MAX_HEIGHT-1){
    return false;
  }
  return bitRead(displayBuffer[y][(x/8)],(8-(x%8))-1);
  
}

byte* ColDisplay::getCol (int x){
  if( x < 0 || (x/8) > MAX_WIDTH ){
    return NULL;
  }

  for (int y = 0; y < pixelHeight; y++){
    retCol[y] = getPixel(x,y);
  }

  return retCol;
   
}
void ColDisplay::setPixel (int x, int y, bool val){
  if( x < 0 || (x/8) > MAX_WIDTH || y < 0 || y > MAX_HEIGHT-1){
    return;
  }
//  Serial.print("\nSetting pixel x,y,val: ");
//  Serial.print(x);
//  Serial.print(",");
//  Serial.print(y);
//  Serial.print(",");
//  Serial.print(val);
//  Serial.print("\n");
  bitWrite(displayBuffer[y][(x/8)],(8-(x%8))-1,val);
}


void ColDisplay::printDisplay (){
  Serial.println("");
  for (int i = 0; i < pixelHeight; i++){
    Serial.println("");
    for (int j = 0; j < viewWidthNumBytes; j++){
      for(int k =1; k <= 8; k++){
        Serial.print(bitRead(displayBuffer[i][j],8-k));
      } 
    }
  }
}


void ColDisplay::updateLoop(){
  digitalWrite(13,LOW);
   //delay (500);

   digitalWrite(13,HIGH);
   //delay(500);

}

#endif
