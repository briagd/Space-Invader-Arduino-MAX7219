#include "LedControl.h" //  need the library

//LedControl(int dataPin, int clkPin, int csPin, int numDevices);
LedControl lc = LedControl(7, 5, 6, 1); //


// * Pin 7 is connected to the DATA IN-pin of the first MAX7221
// * Pin 6 is connected to the CLK-pin of the first MAX7221
// * Pin 5 is connected to the LOAD(/CS)-pin of the first MAX7221
// 1 as we are only using 1 MAX7219

//number of rows and column in the led matrix
const int MAXROW = 8;
//boolean array to store the positions of the led to be turned on
//The pattern is symmetrical so only half of the columns are needed
bool spaceInv[MAXROW][MAXROW/2];

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 1); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  newSpaceInv(); //creates a new space invader patter
}



void loop()
{
  //loop to turn on the led horizontally
  for (int col = 0; col < MAXROW; col++)
  {
    for (int row = 0; row < MAXROW / 2; row++)
    {
      if (spaceInv[col][row] == true) {
        lc.setLed(0, col, row, true); // turns on LED at col, row
        lc.setLed(0, col, MAXROW - row - 1, true); // turns on LED on the opposite side of the matrix
        delay(100);
      }
    }
  }
  delay(1000);
  
  
  //turns off the leds vertically
  for (int row = 0; row < MAXROW / 2; row++)
  {
    for (int col = 0; col < MAXROW; col++)
    {
      if (spaceInv[col][row] == true) {
        lc.setLed(0, col, row, false); // turns off LED at col, row
        lc.setLed(0, col, MAXROW - row - 1, false); // turns off LED on the opposite side of the matrix
        delay(150);
      }
    }
  }
  
  //creates a new pattern
  newSpaceInv();

}


//creates a new pattern with a probability of 0.5 to have a led turned on
void newSpaceInv() {
  for (int i = 0; i < MAXROW; i++) {
    for (int j = 0; j < MAXROW / 2 + 1; j++) {
      float r = random(2);
      if (r < 1) {
        spaceInv[i][j] = true;    
      } else {
        spaceInv[i][j] = false;
      }
    }
  }
}



