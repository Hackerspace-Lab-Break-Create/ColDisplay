#ifndef __COL_WAVE_WORD_H__
#define __COL_WAVE_WORD_H__
#include "ColDisplayObject.h"
#include "PovAlphabet8x8.h"

class ColWaveWord: public ColDisplayObject {
  private:

    byte letterBuffer[MAX_HEIGHT][MAX_LETTERS];
    int numOfLetters = 0;

    int amplitude = 5; // Redeners as 2X considers postive half + negative half
    int offset = -2;
    float freq = 1;
    float phase = 0.0;
    float timeStep = 0.025;
    float deltaTime = 0.0;
    float width = 64;

    const float double_Pi = 3.14159 * 2;
  public:

    //Inherited
    void draw (ColDisplay* cdObject, unsigned long tickCount);

    void setWord(char *newWord);
    void setLetter (int letterIndex, char letter);
    void printDisplay ();
};

void ColWaveWord::draw(ColDisplay* cdObject, unsigned long tickCount) {
  //cdObject->setBytes(0,0,*letterBuffer,8,MAX_LETTERS);
  int x = 0;
  for (int j = 0; j < numOfLetters; j++) {
    deltaTime += (timeStep) ;
    float yvalue = (amplitude * sin(2 * double_Pi * (freq) * deltaTime + phase)) - offset;
    //cdObject->setPixel(x,yvalue,HIGH);

    x++;
    for (int i = 0; i < 8; i++) {
      //Serial.print(letterBuffer[i][j], BIN);
      for (int k = 1; k <= 8; k++) {
        int xa = ((j * 8) + k);
        //Serial.println(yvalue);
        //cdObject->setPixel(xa,yvalue,HIGH);

        cdObject->setPixel(xa, yvalue+i, bitRead(letterBuffer[i][j], 8 - k));
        //Serial.print(bitRead(letterBuffer[i][j],8-k));
      }
    }
  }

}



void ColWaveWord::printDisplay () {
  Serial.println("PRINTING ColWAVEWord");
  for (int i = 0; i < 8; i++) {
    Serial.println("");
    for (int j = 0; j < numOfLetters; j++) {
      //  Serial.println(*letterBuffer[i][j],BIN);
      for (int k = 1; k <= 8; k++) {
        Serial.print(bitRead(letterBuffer[i][j], 8 - k));
      }
    }
  }
}
void ColWaveWord::setLetter (int letterIndex, char letter) {
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


  for (int y = 0; y < MAX_HEIGHT; y++) {
    letterBuffer[y][letterIndex] = ALPHABET[(index - 65)][y];
    //Serial.println(letterBuffer[y][letterIndex],BIN);
  }

}

void ColWaveWord::setWord (char *newWord) {
  int i = 0;
  while (*newWord != '\0') {
    setLetter(i++, *newWord);
    newWord++;
  }

  numOfLetters = i;
}

#endif
