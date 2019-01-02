#ifndef _LETTEROIDFIELD_H_
#define _LETTEROIDFIELD_H_

#include <string>

class LetteroidField
{
 public:
  void start();            /// start up the screen for letteroids
  bool waitForKeyPress();  /// wait for any key to be pressed (return false on 'x'
  void end();              /// shut down the screen and return it to normal
  void setTitle(std::string);   /// diplay the title

};

#endif
