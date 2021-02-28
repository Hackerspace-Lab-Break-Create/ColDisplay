#ifndef _COL_WORD_
#define _COL_WORD_
#include "ColDisplayObject.h"
#include "PovAlphabet8x8.h"



class ColWord: public ColDisplayObject {
  private:
    const static int MAX_LETTERS = 5;  //BYTES
    const static int MAX_HEIGHT = 8; //LEDS
    
    byte letterBuffer[MAX_HEIGHT][MAX_LETTERS];  
    int numOfLetters=0;
    
  public:
  
    //Inherited
    void draw (ColDisplay* cdObject, unsigned long tickCount);
    
    void setWord(char *newWord);
    void setLetter (int letterIndex, char letter);
    void printDisplay ();
};

void ColWord::draw(ColDisplay* cdObject, unsigned long tickCount){
  int countVal = tickCount%cdObject->getPixelWidth();
  cdObject->setBytes(countVal,0,*letterBuffer,8,MAX_LETTERS);
}


void ColWord::printDisplay (){
  Serial.println("PRINTING ColWord");
  for (int i = 0; i < 8; i++){
    Serial.println("");
    for (int j = 0; j < numOfLetters; j++){
    //  Serial.println(*letterBuffer[i][j],BIN);
      for(int k =1; k <= 8; k++){
        Serial.print(bitRead(letterBuffer[i][j],8-k));
      } 
    }
  }
}
void ColWord::setLetter (int letterIndex, char letter) {
  char index = letter;

  // Force uppercase
  if (letter >= 97 && letter <= 122) {
    index = letter - 32;
  } else {
    index = letter;
  }

  //Check for special characters
  switch (letter) {
    case '$':
      index = 27 + 65;
      break;

    case ' ':
      index = 26 + 65;
      break;
  }

//Serial.println("A");
//  for (int i = 0; i < 8; i ++){
//    Serial.println(ALPHABET[(index - 65)][i],BIN);
//  }
//
//Serial.println("ABCD");
//Serial.println(letterIndex);


  for (int y = 0; y < MAX_HEIGHT; y++){
      letterBuffer[y][letterIndex] = ALPHABET[(index - 65)][y];
      //Serial.println(letterBuffer[y][letterIndex],BIN);
  }

}

void ColWord::setWord (char *newWord) {
  int i = 0;
  while (*newWord != '\0') {
    setLetter(i++, *newWord);
    newWord++;
  }

  numOfLetters = i;
}
#endif
