#ifndef _LETTEROID_H_
#define _LETTEROID_H_

#include <curses.h>

class Letteroid
{

 public:

  void setCoords(int, int);// set the position(down, across) 
  void setLetter(char);    // set the character
  int getX();              // get the position down
  int getY();              // get the position across
  void erase();            // erase the letteroid from the screen
  void draw();             // draw the letteroid to the screen  
  
 private:
  int myX;
  int myY;
  char myLetter;

};

#endif
